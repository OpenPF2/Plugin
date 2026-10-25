// OpenPF2 Game Framework for Unreal Engine, Copyright 2026, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "PF2MigrateGameplayTagsCommandlet.h"

#include <Dom/JsonObject.h>
#include <EdGraph/EdGraphNode.h>
#include <EdGraph/EdGraphPin.h>
#include <Engine/Blueprint.h>
#include <Engine/DataTable.h>
#include <GameplayTagContainer.h>
#include <GameplayTagsSettings.h>
#include <Kismet2/BlueprintEditorUtils.h>
#include <Kismet2/KismetEditorUtilities.h>
#include <Misc/ConfigCacheIni.h>
#include <Misc/FileHelper.h>
#include <Misc/PackageName.h>
#include <Misc/Paths.h>
#include <Serialization/JsonReader.h>
#include <Serialization/JsonSerializer.h>
#include <Serialization/JsonWriter.h>
#include <UObject/Package.h>
#include <UObject/SavePackage.h>
#include <UObject/UObjectHash.h>
#include <UObject/UnrealType.h>

namespace
{
	FString MigratePinText(FString Text, const TMap<FString, FString>& Redirects);

	/** Collects serialized tag values and potential untyped legacy references from one package. */
	struct FTagSnapshot
	{
		/** Canonical typed values and Blueprint pin defaults, keyed by their owning object and property. */
		TMap<FString, FString> Values;
		/** Exact legacy names still stored in untyped name or string properties. */
		TArray<FString> LegacyReferences;
		/** Legacy names and their canonical replacements from the migration configuration. */
		TMap<FString, FString> Redirects;
		/** Number of invalid, nonempty gameplay tags encountered. */
		int32 InvalidTags = 0;
		/** Compare pre-reconstruction pin literals using the names that the migration will persist. */
		bool bCanonicalizeLiterals = false;
		/** Rewrite serialized tag literals in Blueprint variable descriptions during the save pass. */
		bool bMigrateLiterals = false;

		void ReadProperty(const FProperty* Property, const void* Value, const FString& Path)
		{
			if (const FStructProperty* StructProperty = CastField<FStructProperty>(Property))
			{
				if (StructProperty->Struct == FGameplayTag::StaticStruct())
				{
					const FGameplayTag& Tag = *static_cast<const FGameplayTag*>(Value);
					this->Values.Add(Path, Tag.ToString());
					if (!Tag.GetTagName().IsNone() &&
						!FGameplayTag::RequestGameplayTag(Tag.GetTagName(), false).IsValid())
					{
						++this->InvalidTags;
					}
					return;
				}
				if (StructProperty->Struct == FGameplayTagContainer::StaticStruct())
				{
					TArray<FString> Names;
					for (const FGameplayTag& Tag : *static_cast<const FGameplayTagContainer*>(Value))
					{
						Names.Add(Tag.ToString());
						if (!FGameplayTag::RequestGameplayTag(Tag.GetTagName(), false).IsValid())
						{
							++this->InvalidTags;
						}
					}
					Names.Sort();
					this->Values.Add(Path, FString::Join(Names, TEXT("|")));
					return;
				}
				if (StructProperty->Struct == FGameplayTagQuery::StaticStruct())
				{
					FString Text;
					Property->ExportTextItem_Direct(Text, Value, nullptr, nullptr, PPF_None);
					this->Values.Add(Path, Text);
				}
				this->ReadStruct(StructProperty->Struct, Value, Path);
			}
			else if (const FArrayProperty* ArrayProperty = CastField<FArrayProperty>(Property))
			{
				FScriptArrayHelper Array(ArrayProperty, Value);
				for (int32 Index = 0; Index < Array.Num(); ++Index)
				{
					this->ReadProperty(ArrayProperty->Inner, Array.GetRawPtr(Index), Path + FString::Printf(TEXT("[%d]"), Index));
				}
			}
			else if (const FSetProperty* SetProperty = CastField<FSetProperty>(Property))
			{
				FScriptSetHelper Set(SetProperty, Value);
				for (int32 Index = 0; Index < Set.GetMaxIndex(); ++Index)
				{
					if (Set.IsValidIndex(Index))
					{
						this->ReadProperty(SetProperty->ElementProp, Set.GetElementPtr(Index), Path + ElementKey(SetProperty->ElementProp, Set.GetElementPtr(Index)));
					}
				}
			}
			else if (const FMapProperty* MapProperty = CastField<FMapProperty>(Property))
			{
				FScriptMapHelper Map(MapProperty, Value);
				for (int32 Index = 0; Index < Map.GetMaxIndex(); ++Index)
				{
					if (Map.IsValidIndex(Index))
					{
						const FString EntryPath = Path + ElementKey(MapProperty->KeyProp, Map.GetKeyPtr(Index));
						this->ReadProperty(MapProperty->KeyProp, Map.GetKeyPtr(Index), EntryPath + TEXT(".Key"));
						this->ReadProperty(MapProperty->ValueProp, Map.GetValuePtr(Index), EntryPath + TEXT(".Value"));
					}
				}
			}
			else if (const FNameProperty* NameProperty = CastField<FNameProperty>(Property))
			{
				this->CheckUntyped(NameProperty->GetPropertyValue(Value).ToString(), Path);
			}
			else if (const FStrProperty* StringProperty = CastField<FStrProperty>(Property))
			{
				FString Text = StringProperty->GetPropertyValue(Value);
				if (Text.Contains(TEXT("TagName=")))
				{
					const FString Canonical = MigratePinText(Text, this->Redirects);
					if (this->bMigrateLiterals)
					{
						StringProperty->SetPropertyValue(const_cast<void*>(Value), Canonical);
						Text = Canonical;
					}
					this->Values.Add(Path, this->bCanonicalizeLiterals ? Canonical : Text);
					if (!this->bCanonicalizeLiterals && Text != Canonical)
					{
						this->LegacyReferences.Add(Path + TEXT("=") + Text);
					}
				}
				else
				{
					this->CheckUntyped(Text, Path);
				}
			}
		}

		void ReadStruct(const UStruct* Struct, const void* Value, const FString& Path)
		{
			for (TFieldIterator<FProperty> Iterator(Struct); Iterator; ++Iterator)
			{
				const FProperty* Property = *Iterator;
				if (!Property->HasAnyPropertyFlags(CPF_Transient | CPF_Deprecated | CPF_SkipSerialization))
				{
					for (int32 Index = 0; Index < Property->ArrayDim; ++Index)
					{
						this->ReadProperty(Property, Property->ContainerPtrToValuePtr<void>(Value, Index),
							Path + TEXT(".") + Property->GetName() + FString::Printf(TEXT("[%d]"), Index));
					}
				}
			}
		}

		void CheckUntyped(const FString& Value, const FString& Path)
		{
			if (this->Redirects.Contains(Value))
			{
				this->LegacyReferences.Add(Path + TEXT("=") + Value);
			}
		}

		void ReadObjects(const TArray<UObject*>& Objects)
		{
			for (UObject* Object : Objects)
			{
				if (Object->HasAnyFlags(RF_Transient) || Object->GetName().StartsWith(TEXT("SKEL_")) ||
					Object->GetName().StartsWith(TEXT("REINST_")))
				{
					continue;
				}
				this->ReadStruct(Object->GetClass(), Object, Object->GetPathName());
				if (const UDataTable* Table = Cast<UDataTable>(Object))
				{
					if (Table->GetRowStruct() != nullptr)
					{
						for (const TPair<FName, uint8*>& Row : Table->GetRowMap())
						{
							this->ReadStruct(Table->GetRowStruct(), Row.Value,
								Object->GetPathName() + TEXT(".Row.") + Row.Key.ToString());
						}
					}
				}
				if (const UEdGraphNode* Node = Cast<UEdGraphNode>(Object))
				{
					for (const UEdGraphPin* Pin : Node->Pins)
					{
						if (Pin != nullptr && Pin->PinType.PinSubCategoryObject.IsValid() &&
							Pin->PinType.PinSubCategoryObject->GetName().StartsWith(TEXT("GameplayTag")))
						{
							// Reconstruction can create empty output defaults that Unreal discards on reload.
							// They contain no tag literal; retain all input defaults and nonempty outputs.
							if (Pin->Direction == EGPD_Output && Pin->DefaultValue.IsEmpty())
							{
								continue;
							}
							const FString Text = this->bCanonicalizeLiterals ?
								MigratePinText(Pin->DefaultValue, this->Redirects) : Pin->DefaultValue;
							this->Values.Add(Object->GetPathName() + TEXT(".Pin.") +
								FString::FromInt(Pin->Direction) + TEXT(".") + Pin->PinName.ToString(), Text);
							if (!this->bCanonicalizeLiterals && Text != MigratePinText(Text, this->Redirects))
							{
								this->LegacyReferences.Add(Object->GetPathName() + TEXT("=") + Text);
							}
						}
					}
				}
			}
		}

		static FString ElementKey(const FProperty* Property, const void* Value)
		{
			FString Text;
			Property->ExportTextItem_Direct(Text, Value, nullptr, nullptr, PPF_None);
			return TEXT("[") + Text + TEXT("]");
		}
	};

	/** Converts tag pin literals while preserving the rest of their serialized default text. */
	FString MigratePinText(FString Text, const TMap<FString, FString>& Redirects)
	{
		for (const TPair<FString, FString>& Redirect : Redirects)
		{
			Text.ReplaceInline(*(TEXT("\"") + Redirect.Key + TEXT("\"")),
				*(TEXT("\"") + Redirect.Value + TEXT("\"")), ESearchCase::CaseSensitive);
			if (Text == Redirect.Key)
			{
				Text = Redirect.Value;
			}
		}
		return Text;
	}
}

UPF2MigrateGameplayTagsCommandlet::UPF2MigrateGameplayTagsCommandlet()
{
	this->IsClient = false;
	this->IsServer = false;
	this->IsEditor = true;
	this->LogToConsole = true;
}

int32 UPF2MigrateGameplayTagsCommandlet::Main(const FString& Params)
{
	FString ManifestPath, ReportPath, BaselinePath, RedirectConfig;
	FParse::Value(*Params, TEXT("Manifest="), ManifestPath);
	FParse::Value(*Params, TEXT("Report="), ReportPath);
	FParse::Value(*Params, TEXT("Baseline="), BaselinePath);
	FParse::Value(*Params, TEXT("RedirectConfig="), RedirectConfig);
	const bool bResave = FParse::Param(*Params, TEXT("Resave"));
	const bool bNoRedirects = FParse::Param(*Params, TEXT("NoRedirects"));
	TArray<FString> Filenames;
	if (!FFileHelper::LoadFileToStringArray(Filenames, *ManifestPath) || ReportPath.IsEmpty())
	{
		UE_LOG(LogTemp, Error, TEXT("Manifest and Report are required."));
		return 1;
	}
	if (bNoRedirects && !GetDefault<UGameplayTagsSettings>()->GameplayTagRedirects.IsEmpty())
	{
		UE_LOG(LogTemp, Error, TEXT("Redirect-free audit found active gameplay tag redirects."));
		return 1;
	}
	FTagSnapshot Snapshot;
	FConfigFile RedirectFile;
	TArray<FString> Entries;
	RedirectFile.Combine(RedirectConfig);
	RedirectFile.GetArray(TEXT("/Script/GameplayTags.GameplayTagsSettings"), TEXT("GameplayTagRedirects"), Entries);
	for (const FString& Entry : Entries)
	{
		FString OldName, NewName;
		FParse::Value(*Entry, TEXT("OldTagName="), OldName);
		FParse::Value(*Entry, TEXT("NewTagName="), NewName);
		if (!OldName.IsEmpty() && !NewName.IsEmpty())
		{
			Snapshot.Redirects.Add(OldName, NewName);
		}
	}
	if (bResave)
	{
		if (Snapshot.Redirects.IsEmpty())
		{
			UE_LOG(LogTemp, Error, TEXT("Resave requires a nonempty RedirectConfig migration map."));
			return 1;
		}
		for (const TPair<FString, FString>& Redirect : Snapshot.Redirects)
		{
			const FString Literal = TEXT("(TagName=\"") + Redirect.Key + TEXT("\")");
			const TCHAR* Buffer = *Literal;
			FGameplayTag Imported;
			if (!Imported.ImportTextItem(Buffer, PPF_None, nullptr, GWarn) ||
				!Imported.IsValid() || Imported.ToString() != Redirect.Value)
			{
				UE_LOG(LogTemp, Error, TEXT("Legacy tag import failed: %s -> %s; got %s"),
					*Redirect.Key, *Redirect.Value, *Imported.ToString());
				return 1;
			}
		}
	}
	int32 Failures = 0, Saved = 0, Blueprints = 0;
	TArray<TSharedPtr<FJsonValue>> Packages;
	for (const FString& Filename : Filenames)
	{
		const int32 PreviousFailures = Failures;
		FString PackageName;
		if (!FPackageName::TryConvertFilenameToLongPackageName(Filename, PackageName))
		{
			UE_LOG(LogTemp, Error, TEXT("Cannot resolve package: %s"), *Filename);
			++Failures;
			continue;
		}
		UPackage* Package = LoadPackage(nullptr, *PackageName, LOAD_None);
		if (Package == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("Cannot load package: %s"), *PackageName);
			++Failures;
			continue;
		}
		Package->FullyLoad();
		const int32 PreviousValueCount = Snapshot.Values.Num();
		bool bContainsBlueprint = false;
		TArray<UObject*> Objects;
		Objects.Reset();
		GetObjectsWithPackage(Package, Objects);
		FTagSnapshot Before;
		Before.Redirects = Snapshot.Redirects;
		Before.bCanonicalizeLiterals = bResave;
		Before.ReadObjects(Objects);
		if (bResave)
		{
			FTagSnapshot LiteralMigration;
			LiteralMigration.Redirects = Snapshot.Redirects;
			LiteralMigration.bMigrateLiterals = true;
			LiteralMigration.ReadObjects(Objects);
			for (UObject* Object : Objects)
			{
				if (UEdGraphNode* Node = Cast<UEdGraphNode>(Object))
				{
					for (UEdGraphPin* Pin : Node->Pins)
					{
						if (Pin != nullptr && Pin->PinType.PinSubCategoryObject.IsValid() &&
							Pin->PinType.PinSubCategoryObject->GetName().StartsWith(TEXT("GameplayTag")))
						{
							Pin->DefaultValue = MigratePinText(Pin->DefaultValue, Snapshot.Redirects);
						}
					}
				}
			}
		}
		for (UObject* Object : Objects)
		{
			if (UBlueprint* Blueprint = Cast<UBlueprint>(Object))
			{
				bContainsBlueprint = true;
				++Blueprints;
				if (bResave)
				{
					FBlueprintEditorUtils::RefreshAllNodes(Blueprint);
					FKismetEditorUtilities::CompileBlueprint(Blueprint, EBlueprintCompileOptions::SkipGarbageCollection);
					if (Blueprint->Status == BS_Error)
					{
						++Failures;
					}
				}
			}
		}
		Objects.Reset();
		GetObjectsWithPackage(Package, Objects);
		FTagSnapshot After;
		After.Redirects = Snapshot.Redirects;
		After.ReadObjects(Objects);
		if (bResave)
		{
			for (const TPair<FString, FString>& Value : Before.Values)
			{
				const FString* Actual = After.Values.Find(Value.Key);
				if (Actual == nullptr || *Actual != Value.Value)
				{
					UE_LOG(LogTemp, Error, TEXT("Tag value changed during reconstruction: %s"), *Value.Key);
					++Failures;
				}
			}
		}
		Snapshot.Values.Append(After.Values);
		Snapshot.InvalidTags += Before.InvalidTags + After.InvalidTags;
		Snapshot.LegacyReferences.Append(After.LegacyReferences);
		if (bResave && Failures == PreviousFailures && Before.InvalidTags == 0 && After.InvalidTags == 0 &&
			After.LegacyReferences.IsEmpty() && (bContainsBlueprint || Snapshot.Values.Num() > PreviousValueCount))
		{
			FSavePackageArgs SaveArgs;
			SaveArgs.TopLevelFlags = RF_Public | RF_Standalone;
			SaveArgs.SaveFlags = SAVE_NoError;
			if (!UPackage::SavePackage(Package, nullptr, *Filename, SaveArgs))
			{
				++Failures;
			}
			else
			{
				++Saved;
			}
		}
		Packages.Add(MakeShared<FJsonValueString>(PackageName));
		UE_LOG(LogTemp, Display, TEXT("Tag migration processed %s%s"), *PackageName,
			bContainsBlueprint ? TEXT(" [Blueprint]") : TEXT(""));
		CollectGarbage(RF_NoFlags);
	}
	TSharedRef<FJsonObject> Report = MakeShared<FJsonObject>();
	TSharedRef<FJsonObject> Values = MakeShared<FJsonObject>();
	Snapshot.Values.KeySort(TLess<FString>());
	for (const TPair<FString, FString>& Value : Snapshot.Values)
	{
		Values->SetStringField(Value.Key, Value.Value);
	}
	Report->SetObjectField(TEXT("Values"), Values);
	Report->SetArrayField(TEXT("Packages"), Packages);
	Report->SetNumberField(TEXT("Saved"), Saved);
	Report->SetNumberField(TEXT("Blueprints"), Blueprints);
	Report->SetNumberField(TEXT("InvalidTags"), Snapshot.InvalidTags);
	TArray<TSharedPtr<FJsonValue>> LegacyReferences;
	for (const FString& Reference : Snapshot.LegacyReferences)
	{
		LegacyReferences.Add(MakeShared<FJsonValueString>(Reference));
	}
	Report->SetArrayField(TEXT("LegacyReferences"), LegacyReferences);
	if (!BaselinePath.IsEmpty())
	{
		FString BaselineText;
		TSharedPtr<FJsonObject> Baseline;
		if (!FFileHelper::LoadFileToString(BaselineText, *BaselinePath) ||
			!FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(BaselineText), Baseline))
		{
			++Failures;
		}
		else
		{
			TMap<FString, TSharedPtr<FJsonValue>> Expected;
			for (const auto& Value : Baseline->GetObjectField(TEXT("Values"))->Values)
			{
				Expected.Add(FString(*Value.Key), Value.Value);
			}
			// Older reports also captured empty output defaults. Normalize only those entries.
			const FString OutputPinMarker = TEXT(".Pin.") + FString::FromInt(EGPD_Output) + TEXT(".");
			for (auto Iterator = Expected.CreateIterator(); Iterator; ++Iterator)
			{
				const int32 MarkerIndex = Iterator.Key().Find(OutputPinMarker);
				if (Iterator.Value()->Type == EJson::String && Iterator.Value()->AsString().IsEmpty() &&
					MarkerIndex != INDEX_NONE && MarkerIndex + OutputPinMarker.Len() < Iterator.Key().Len())
				{
					Iterator.RemoveCurrent();
				}
			}
			if (Expected.Num() != Values->Values.Num() ||
				Baseline->GetArrayField(TEXT("Packages")).Num() != Packages.Num())
			{
				++Failures;
			}
			for (const TPair<FString, TSharedPtr<FJsonValue>>& Value : Expected)
			{
				FString Actual;
				if (!Values->TryGetStringField(Value.Key, Actual) || Actual != Value.Value->AsString())
				{
					UE_LOG(LogTemp, Error, TEXT("Tag value changed after reload: %s"), *Value.Key);
					++Failures;
				}
			}
		}
	}
	Failures += Snapshot.InvalidTags + Snapshot.LegacyReferences.Num();
	Report->SetNumberField(TEXT("Failures"), Failures);
	FString ReportText;
	FJsonSerializer::Serialize(Report, TJsonWriterFactory<>::Create(&ReportText));
	if (!FFileHelper::SaveStringToFile(ReportText, *ReportPath))
	{
		return 1;
	}
	UE_LOG(LogTemp, Display, TEXT("Tag migration: %d packages, %d Blueprints, %d saved, %d failures."),
		Packages.Num(), Blueprints, Saved, Failures);
	return Failures == 0 ? 0 : 1;
}

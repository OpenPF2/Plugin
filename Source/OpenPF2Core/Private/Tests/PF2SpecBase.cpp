// OpenPF2 for UE Game Logic, Copyright 2021, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "Tests/PF2SpecBase.h"
#include "Abilities/PF2AttributeSet.h"

template <typename BlueprintType>
TSubclassOf<BlueprintType> FPF2SpecBase::LoadBlueprint(const FString FolderPath, const FString BlueprintName)
{
	const FString ObjectPath =
		FString::Printf(TEXT("BlueprintGeneratedClass'%s/%s.%s_C'"), *FolderPath, *BlueprintName, *BlueprintName);

	const TSoftClassPtr<BlueprintType> ObjectClass =
		TSoftClassPtr<BlueprintType>(FSoftObjectPath(ObjectPath));

	return ObjectClass.LoadSynchronous();
}

FAttributeCapture FPF2SpecBase::CaptureAttributes(const UPF2AttributeSet* AttributeSet)
{
	FAttributeCapture Capture;

	Capture.Add(TEXT("AbCharisma"),     const_cast<FGameplayAttributeData *>(&AttributeSet->AbCharisma));
	Capture.Add(TEXT("AbConstitution"), const_cast<FGameplayAttributeData *>(&AttributeSet->AbConstitution));
	Capture.Add(TEXT("AbDexterity"),    const_cast<FGameplayAttributeData *>(&AttributeSet->AbDexterity));
	Capture.Add(TEXT("AbIntelligence"), const_cast<FGameplayAttributeData *>(&AttributeSet->AbIntelligence));
	Capture.Add(TEXT("AbStrength"),     const_cast<FGameplayAttributeData *>(&AttributeSet->AbStrength));
	Capture.Add(TEXT("AbWisdom"),       const_cast<FGameplayAttributeData *>(&AttributeSet->AbWisdom));

	return Capture;
}

void FPF2SpecBase::SetupWorld()
{
	FWorldContext& WorldContext = GEngine->CreateNewWorldContext(EWorldType::Game);

	this->World = UWorld::CreateWorld(EWorldType::Game, false);

	WorldContext.SetCurrentWorld(this->World);
}

void FPF2SpecBase::BeginPlay() const
{
	const FURL CommandLineURL;

	this->World->InitializeActorsForPlay(CommandLineURL);
	this->World->BeginPlay();
}

void FPF2SpecBase::DestroyWorld() const
{
	GEngine->DestroyWorldContext(this->World);

	this->World->DestroyWorld(false);
}

FActiveGameplayEffectHandle FPF2SpecBase::ApplyGameEffect(FGameplayAttributeData&             Attribute,
                                                          const float                         StartingValue,
                                                          const TSubclassOf<UGameplayEffect>& EffectBP) const
{
	UGameplayEffect* GameplayEffect = EffectBP->GetDefaultObject<UGameplayEffect>();

	Attribute = StartingValue;

	const FActiveGameplayEffectHandle EffectHandle = this->PawnAbilityComponent->ApplyGameplayEffectToTarget(
		GameplayEffect,
		this->PawnAbilityComponent,
		1.0f
	);

	return EffectHandle;
}

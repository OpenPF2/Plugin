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

	Capture.Add(TEXT("Experience"),           const_cast<FGameplayAttributeData *>(&AttributeSet->Experience));
	Capture.Add(TEXT("HitPoints"),            const_cast<FGameplayAttributeData *>(&AttributeSet->HitPoints));
	Capture.Add(TEXT("MaxHitPoints"),         const_cast<FGameplayAttributeData *>(&AttributeSet->MaxHitPoints));
	Capture.Add(TEXT("AbBoostCount"),         const_cast<FGameplayAttributeData *>(&AttributeSet->AbBoostCount));
	Capture.Add(TEXT("AbBoostLimit"),         const_cast<FGameplayAttributeData *>(&AttributeSet->AbBoostLimit));
	Capture.Add(TEXT("ClassDifficultyClass"), const_cast<FGameplayAttributeData *>(&AttributeSet->ClassDifficultyClass));
	Capture.Add(TEXT("Speed"),                const_cast<FGameplayAttributeData *>(&AttributeSet->Speed));
	Capture.Add(TEXT("MaxSpeed"),             const_cast<FGameplayAttributeData *>(&AttributeSet->MaxSpeed));
	Capture.Add(TEXT("ArmorClass"),           const_cast<FGameplayAttributeData *>(&AttributeSet->ArmorClass));
	Capture.Add(TEXT("PerceptionModifier"),   const_cast<FGameplayAttributeData *>(&AttributeSet->PerceptionModifier));
	Capture.Add(TEXT("FeAncestryFeatCount"),  const_cast<FGameplayAttributeData *>(&AttributeSet->FeAncestryFeatCount));
	Capture.Add(TEXT("FeAncestryFeatLimit"),  const_cast<FGameplayAttributeData *>(&AttributeSet->FeAncestryFeatLimit));
	Capture.Add(TEXT("Damage"),               const_cast<FGameplayAttributeData *>(&AttributeSet->Damage));

	Capture.Append(CaptureAbilityAttributes(AttributeSet));
	Capture.Append(CaptureAbilityModifierAttributes(AttributeSet));
	Capture.Append(CaptureSavingThrowAttributes(AttributeSet));
	Capture.Append(CaptureSkillModifierAttributes(AttributeSet));

	return Capture;
}

FAttributeCapture FPF2SpecBase::CaptureAbilityAttributes(const UPF2AttributeSet* AttributeSet)
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

FAttributeCapture FPF2SpecBase::CaptureAbilityModifierAttributes(const UPF2AttributeSet* AttributeSet)
{
	FAttributeCapture Capture;

	Capture.Add(TEXT("AbCharismaModifier"),     const_cast<FGameplayAttributeData *>(&AttributeSet->AbCharismaModifier));
	Capture.Add(TEXT("AbConstitutionModifier"), const_cast<FGameplayAttributeData *>(&AttributeSet->AbConstitutionModifier));
	Capture.Add(TEXT("AbDexterityModifier"),    const_cast<FGameplayAttributeData *>(&AttributeSet->AbDexterityModifier));
	Capture.Add(TEXT("AbIntelligenceModifier"), const_cast<FGameplayAttributeData *>(&AttributeSet->AbIntelligenceModifier));
	Capture.Add(TEXT("AbStrengthModifier"),     const_cast<FGameplayAttributeData *>(&AttributeSet->AbStrengthModifier));
	Capture.Add(TEXT("AbWisdomModifier"),       const_cast<FGameplayAttributeData *>(&AttributeSet->AbWisdomModifier));

	return Capture;
}

FAttributeCapture FPF2SpecBase::CaptureSavingThrowAttributes(const UPF2AttributeSet* AttributeSet)
{
	FAttributeCapture Capture;

	Capture.Add(TEXT("StFortitudeModifier"), const_cast<FGameplayAttributeData *>(&AttributeSet->StFortitudeModifier));
	Capture.Add(TEXT("StReflexModifier"),    const_cast<FGameplayAttributeData *>(&AttributeSet->StReflexModifier));
	Capture.Add(TEXT("StWillModifier"),      const_cast<FGameplayAttributeData *>(&AttributeSet->StWillModifier));

	return Capture;
}

FAttributeCapture FPF2SpecBase::CaptureSkillModifierAttributes(const UPF2AttributeSet* AttributeSet)
{
	FAttributeCapture Capture;

	Capture.Add(TEXT("SkAcrobaticsModifier"),   const_cast<FGameplayAttributeData *>(&AttributeSet->SkAcrobaticsModifier));
	Capture.Add(TEXT("SkArcanaModifier"),       const_cast<FGameplayAttributeData *>(&AttributeSet->SkArcanaModifier));
	Capture.Add(TEXT("SkAthleticsModifier"),    const_cast<FGameplayAttributeData *>(&AttributeSet->SkAthleticsModifier));
	Capture.Add(TEXT("SkCraftingModifier"),     const_cast<FGameplayAttributeData *>(&AttributeSet->SkCraftingModifier));
	Capture.Add(TEXT("SkDeceptionModifier"),    const_cast<FGameplayAttributeData *>(&AttributeSet->SkDeceptionModifier));
	Capture.Add(TEXT("SkDiplomacyModifier"),    const_cast<FGameplayAttributeData *>(&AttributeSet->SkDiplomacyModifier));
	Capture.Add(TEXT("SkIntimidationModifier"), const_cast<FGameplayAttributeData *>(&AttributeSet->SkIntimidationModifier));
	Capture.Add(TEXT("SkLore1Modifier"),        const_cast<FGameplayAttributeData *>(&AttributeSet->SkLore1Modifier));
	Capture.Add(TEXT("SkLore2Modifier"),        const_cast<FGameplayAttributeData *>(&AttributeSet->SkLore2Modifier));
	Capture.Add(TEXT("SkMedicineModifier"),     const_cast<FGameplayAttributeData *>(&AttributeSet->SkMedicineModifier));
	Capture.Add(TEXT("SkNatureModifier"),       const_cast<FGameplayAttributeData *>(&AttributeSet->SkNatureModifier));
	Capture.Add(TEXT("SkOccultismModifier"),    const_cast<FGameplayAttributeData *>(&AttributeSet->SkOccultismModifier));
	Capture.Add(TEXT("SkPerformanceModifier"),  const_cast<FGameplayAttributeData *>(&AttributeSet->SkPerformanceModifier));
	Capture.Add(TEXT("SkReligionModifier"),     const_cast<FGameplayAttributeData *>(&AttributeSet->SkReligionModifier));
	Capture.Add(TEXT("SkSocietyModifier"),      const_cast<FGameplayAttributeData *>(&AttributeSet->SkSocietyModifier));
	Capture.Add(TEXT("SkStealthModifier"),      const_cast<FGameplayAttributeData *>(&AttributeSet->SkStealthModifier));
	Capture.Add(TEXT("SkSurvivalModifier"),     const_cast<FGameplayAttributeData *>(&AttributeSet->SkSurvivalModifier));
	Capture.Add(TEXT("SkThieveryModifier"),     const_cast<FGameplayAttributeData *>(&AttributeSet->SkThieveryModifier));

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

void FPF2SpecBase::SetupPawn()
{
	this->TestPawn             = this->World->SpawnActor<APF2TestPawn>();
	this->PawnAbilityComponent = this->TestPawn->GetAbilitySystemComponent();
}

void FPF2SpecBase::DestroyPawn()
{
	if (this->TestPawn)
	{
		this->World->EditorDestroyActor(this->TestPawn, false);
	}

	this->TestPawn = nullptr;
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

void FPF2SpecBase::ApplyTag(FString TagName) const
{
	this->PawnAbilityComponent->AddLooseGameplayTag(FGameplayTag::RequestGameplayTag(FName(TagName)));
}

void FPF2SpecBase::RemoveTag(FString TagName) const
{
	this->PawnAbilityComponent->RemoveLooseGameplayTag(FGameplayTag::RequestGameplayTag(FName(TagName)));
}

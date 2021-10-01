// OpenPF2 for UE Game Logic, Copyright 2021, Guy Elsmore-Paddock. All Rights Reserved.
//
// Content from Pathfinder 2nd Edition is licensed under the Open Game License (OGL) v1.0a, subject to the following:
//   - Open Game License v 1.0a, Copyright 2000, Wizards of the Coast, Inc.
//   - System Reference Document, Copyright 2000, Wizards of the Coast, Inc.
//   - Pathfinder Core Rulebook (Second Edition), Copyright 2019, Paizo Inc.
// Except for material designated as Product Identity, the game mechanics and logic in this file are Open Game Content,
// as defined in the Open Game License version 1.0a, Section 1(d) (see accompanying LICENSE.TXT). No portion of this
// file other than the material designated as Open Game Content may be reproduced in any form without written
// permission.

#include "Abilities/PF2AttributeSet.h"

#include <Net/UnrealNetwork.h>

UPF2AttributeSet::UPF2AttributeSet() :
	Experience(0.0f),
	HitPoints(1.0f),
	MaxHitPoints(1.0f),
	AbBoostCount(0.0f),
	AbBoostLimit(0.0f),
	AbStrength(10.0f),
	AbStrengthModifier(0.0f),
	AbDexterity(10.0f),
	AbDexterityModifier(0.0f),
	AbConstitution(10.0f),
	AbConstitutionModifier(0.0f),
	AbIntelligence(10.0f),
	AbIntelligenceModifier(0.0f),
	AbWisdom(10.0f),
	AbWisdomModifier(0.0f),
	AbCharisma(10.0f),
	AbCharismaModifier(0.0f),
	ClassDifficultyClass(0.0f),
	Speed(1.0f),
	MaxSpeed(1.0f),
	ArmorClass(10.0f),
	StFortitudeModifier(0.0f),
	StReflexModifier(0.0f),
	StWillModifier(0.0f),
	PerceptionModifier(0.0f),
	SkSkillCount(0.0f),
	SkSkillLimit(0.0f),
	SkAcrobaticsModifier(0.0f),
	SkArcanaModifier(0.0f),
	SkAthleticsModifier(0.0f),
	SkCraftingModifier(0.0f),
	SkDeceptionModifier(0.0f),
	SkDiplomacyModifier(0.0f),
	SkIntimidationModifier(0.0f),
	SkLore1Modifier(0.0f),
	SkLore2Modifier(0.0f),
	SkMedicineModifier(0.0f),
	SkNatureModifier(0.0f),
	SkOccultismModifier(0.0f),
	SkPerformanceModifier(0.0f),
	SkReligionModifier(0.0f),
	SkSocietyModifier(0.0f),
	SkStealthModifier(0.0f),
	SkSurvivalModifier(0.0f),
	SkThieveryModifier(0.0f),
	SpellAttackRoll(0.0f),
	SpellDifficultyClass(0.0f),
	FeAncestryFeatCount(0.0f),
	FeAncestryFeatLimit(0.0f),
	Damage(0.0f)
{
}

void UPF2AttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UPF2AttributeSet, Experience);
	DOREPLIFETIME(UPF2AttributeSet, HitPoints);
	DOREPLIFETIME(UPF2AttributeSet, MaxHitPoints);
	DOREPLIFETIME(UPF2AttributeSet, AbBoostCount);
	DOREPLIFETIME(UPF2AttributeSet, AbBoostLimit);
	DOREPLIFETIME(UPF2AttributeSet, AbStrength);
	DOREPLIFETIME(UPF2AttributeSet, AbStrengthModifier);
	DOREPLIFETIME(UPF2AttributeSet, AbDexterity);
	DOREPLIFETIME(UPF2AttributeSet, AbDexterityModifier);
	DOREPLIFETIME(UPF2AttributeSet, AbConstitution);
	DOREPLIFETIME(UPF2AttributeSet, AbConstitutionModifier);
	DOREPLIFETIME(UPF2AttributeSet, AbIntelligence);
	DOREPLIFETIME(UPF2AttributeSet, AbIntelligenceModifier);
	DOREPLIFETIME(UPF2AttributeSet, AbWisdom);
	DOREPLIFETIME(UPF2AttributeSet, AbWisdomModifier);
	DOREPLIFETIME(UPF2AttributeSet, AbCharisma);
	DOREPLIFETIME(UPF2AttributeSet, AbCharismaModifier);
	DOREPLIFETIME(UPF2AttributeSet, ClassDifficultyClass);
	DOREPLIFETIME(UPF2AttributeSet, Speed);
	DOREPLIFETIME(UPF2AttributeSet, MaxSpeed);
	DOREPLIFETIME(UPF2AttributeSet, ArmorClass);
	DOREPLIFETIME(UPF2AttributeSet, StFortitudeModifier);
	DOREPLIFETIME(UPF2AttributeSet, StReflexModifier);
	DOREPLIFETIME(UPF2AttributeSet, StWillModifier);
	DOREPLIFETIME(UPF2AttributeSet, PerceptionModifier);
	DOREPLIFETIME(UPF2AttributeSet, SkAcrobaticsModifier);
	DOREPLIFETIME(UPF2AttributeSet, SkArcanaModifier);
	DOREPLIFETIME(UPF2AttributeSet, SkAthleticsModifier);
	DOREPLIFETIME(UPF2AttributeSet, SkCraftingModifier);
	DOREPLIFETIME(UPF2AttributeSet, SkDeceptionModifier);
	DOREPLIFETIME(UPF2AttributeSet, SkDiplomacyModifier);
	DOREPLIFETIME(UPF2AttributeSet, SkIntimidationModifier);
	DOREPLIFETIME(UPF2AttributeSet, SkLore1Modifier);
	DOREPLIFETIME(UPF2AttributeSet, SkLore2Modifier);
	DOREPLIFETIME(UPF2AttributeSet, SkMedicineModifier);
	DOREPLIFETIME(UPF2AttributeSet, SkNatureModifier);
	DOREPLIFETIME(UPF2AttributeSet, SkOccultismModifier);
	DOREPLIFETIME(UPF2AttributeSet, SkPerformanceModifier);
	DOREPLIFETIME(UPF2AttributeSet, SkReligionModifier);
	DOREPLIFETIME(UPF2AttributeSet, SkSocietyModifier);
	DOREPLIFETIME(UPF2AttributeSet, SkStealthModifier);
	DOREPLIFETIME(UPF2AttributeSet, SkSurvivalModifier);
	DOREPLIFETIME(UPF2AttributeSet, SkThieveryModifier);
	DOREPLIFETIME(UPF2AttributeSet, SpellAttackRoll);
	DOREPLIFETIME(UPF2AttributeSet, SpellDifficultyClass);
	DOREPLIFETIME(UPF2AttributeSet, FeAncestryFeatCount);
	DOREPLIFETIME(UPF2AttributeSet, FeAncestryFeatLimit);
}

void UPF2AttributeSet::OnRep_Experience(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPF2AttributeSet, Experience, OldValue);
}

void UPF2AttributeSet::OnRep_HitPoints(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPF2AttributeSet, HitPoints, OldValue);
}

void UPF2AttributeSet::OnRep_MaxHitPoints(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPF2AttributeSet, MaxHitPoints, OldValue);
}

void UPF2AttributeSet::OnRep_AbBoostCount(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPF2AttributeSet, AbBoostCount, OldValue);
}

void UPF2AttributeSet::OnRep_AbBoostLimit(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPF2AttributeSet, AbBoostLimit, OldValue);
}

void UPF2AttributeSet::OnRep_AbStrength(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPF2AttributeSet, AbStrength, OldValue);
}

void UPF2AttributeSet::OnRep_AbStrengthModifier(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPF2AttributeSet, AbStrengthModifier, OldValue);
}

void UPF2AttributeSet::OnRep_AbDexterity(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPF2AttributeSet, AbDexterity, OldValue);
}

void UPF2AttributeSet::OnRep_AbDexterityModifier(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPF2AttributeSet, AbDexterityModifier, OldValue);
}

void UPF2AttributeSet::OnRep_AbConstitution(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPF2AttributeSet, AbConstitution, OldValue);
}

void UPF2AttributeSet::OnRep_AbConstitutionModifier(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPF2AttributeSet, AbConstitutionModifier, OldValue);
}

void UPF2AttributeSet::OnRep_AbIntelligence(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPF2AttributeSet, AbIntelligence, OldValue);
}

void UPF2AttributeSet::OnRep_AbIntelligenceModifier(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPF2AttributeSet, AbIntelligenceModifier, OldValue);
}

void UPF2AttributeSet::OnRep_AbWisdom(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPF2AttributeSet, AbWisdom, OldValue);
}

void UPF2AttributeSet::OnRep_AbWisdomModifier(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPF2AttributeSet, AbWisdomModifier, OldValue);
}

void UPF2AttributeSet::OnRep_AbCharisma(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPF2AttributeSet, AbCharisma, OldValue);
}

void UPF2AttributeSet::OnRep_AbCharismaModifier(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPF2AttributeSet, AbCharismaModifier, OldValue);
}

void UPF2AttributeSet::OnRep_ClassDifficultyClass(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPF2AttributeSet, ClassDifficultyClass, OldValue);
}

void UPF2AttributeSet::OnRep_Speed(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPF2AttributeSet, Speed, OldValue);
}

void UPF2AttributeSet::OnRep_MaxSpeed(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPF2AttributeSet, MaxSpeed, OldValue);
}

void UPF2AttributeSet::OnRep_ArmorClass(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPF2AttributeSet, ArmorClass, OldValue);
}

void UPF2AttributeSet::OnRep_StFortitudeModifier(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPF2AttributeSet, StFortitudeModifier, OldValue);
}

void UPF2AttributeSet::OnRep_StReflexModifier(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPF2AttributeSet, StReflexModifier, OldValue);
}

void UPF2AttributeSet::OnRep_StWillModifier(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPF2AttributeSet, StWillModifier, OldValue);
}

void UPF2AttributeSet::OnRep_PerceptionModifier(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPF2AttributeSet, PerceptionModifier, OldValue);
}

void UPF2AttributeSet::OnRep_SkSkillCount(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPF2AttributeSet, SkSkillCount, OldValue);
}

void UPF2AttributeSet::OnRep_SkSkillLimit(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPF2AttributeSet, SkSkillLimit, OldValue);
}

void UPF2AttributeSet::OnRep_SkAcrobaticsModifier(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPF2AttributeSet, SkAcrobaticsModifier, OldValue);
}

void UPF2AttributeSet::OnRep_SkArcanaModifier(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPF2AttributeSet, SkArcanaModifier, OldValue);
}

void UPF2AttributeSet::OnRep_SkAthleticsModifier(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPF2AttributeSet, SkAthleticsModifier, OldValue);
}

void UPF2AttributeSet::OnRep_SkCraftingModifier(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPF2AttributeSet, SkCraftingModifier, OldValue);
}

void UPF2AttributeSet::OnRep_SkDeceptionModifier(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPF2AttributeSet, SkDeceptionModifier, OldValue);
}

void UPF2AttributeSet::OnRep_SkDiplomacyModifier(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPF2AttributeSet, SkDiplomacyModifier, OldValue);
}

void UPF2AttributeSet::OnRep_SkIntimidationModifier(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPF2AttributeSet, SkIntimidationModifier, OldValue);
}

void UPF2AttributeSet::OnRep_SkLore1Modifier(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPF2AttributeSet, SkLore1Modifier, OldValue);
}

void UPF2AttributeSet::OnRep_SkLore2Modifier(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPF2AttributeSet, SkLore2Modifier, OldValue);
}

void UPF2AttributeSet::OnRep_SkMedicineModifier(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPF2AttributeSet, SkMedicineModifier, OldValue);
}

void UPF2AttributeSet::OnRep_SkNatureModifier(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPF2AttributeSet, SkNatureModifier, OldValue);
}

void UPF2AttributeSet::OnRep_SkOccultismModifier(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPF2AttributeSet, SkOccultismModifier, OldValue);
}

void UPF2AttributeSet::OnRep_SkPerformanceModifier(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPF2AttributeSet, SkPerformanceModifier, OldValue);
}

void UPF2AttributeSet::OnRep_SkReligionModifier(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPF2AttributeSet, SkReligionModifier, OldValue);
}

void UPF2AttributeSet::OnRep_SkSocietyModifier(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPF2AttributeSet, SkSocietyModifier, OldValue);
}

void UPF2AttributeSet::OnRep_SkStealthModifier(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPF2AttributeSet, SkStealthModifier, OldValue);
}

void UPF2AttributeSet::OnRep_SkSurvivalModifier(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPF2AttributeSet, SkSurvivalModifier, OldValue);
}

void UPF2AttributeSet::OnRep_SkThieveryModifier(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPF2AttributeSet, SkThieveryModifier, OldValue);
}

void UPF2AttributeSet::OnRep_SpellAttackRoll(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPF2AttributeSet, SpellAttackRoll, OldValue);
}

void UPF2AttributeSet::OnRep_SpellDifficultyClass(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPF2AttributeSet, SpellDifficultyClass, OldValue);
}

void UPF2AttributeSet::OnRep_FeAncestryFeatCount(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPF2AttributeSet, FeAncestryFeatCount, OldValue);
}

void UPF2AttributeSet::OnRep_FeAncestryFeatLimit(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPF2AttributeSet, FeAncestryFeatLimit, OldValue);
}

void UPF2AttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
}

void UPF2AttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
}

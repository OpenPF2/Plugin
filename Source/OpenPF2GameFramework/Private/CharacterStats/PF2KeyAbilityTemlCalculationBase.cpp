// OpenPF2 Game Framework for Unreal Engine, Copyright 2021-2024, Guy Elsmore-Paddock. All Rights Reserved.
//
// Content from Pathfinder 2nd Edition is licensed under the Open Game License (OGL) v1.0a, subject to the following:
//   - Open Game License v 1.0a, Copyright 2000, Wizards of the Coast, Inc.
//   - System Reference Document, Copyright 2000, Wizards of the Coast, Inc.
//   - Pathfinder Core Rulebook (Second Edition), Copyright 2019, Paizo Inc.
//
// Except for material designated as Product Identity, the game mechanics and logic in this file are Open Game Content,
// as defined in the Open Game License version 1.0a, Section 1(d) (see accompanying LICENSE.TXT). No portion of this
// file other than the material designated as Open Game Content may be reproduced in any form without written
// permission.

#include "CharacterStats/PF2KeyAbilityTemlCalculationBase.h"

#include "OpenPF2GameFramework.h"

#include "CharacterStats/PF2CharacterAttributeSet.h"
#include "CharacterStats/PF2TemlCalculation.h"

#include "GameplayTags/Stats/KeyAbilities.h"

#include "Libraries/PF2AbilitySystemLibrary.h"
#include "Libraries/PF2TagLibrary.h"

#include "Utilities/PF2GameplayAbilityUtilities.h"

UPF2KeyAbilityTemlCalculationBase::UPF2KeyAbilityTemlCalculationBase() :
	UPF2KeyAbilityTemlCalculationBase(
		FGameplayTag(),
		Pf2TagKeyAbilities
	)
{
}

UPF2KeyAbilityTemlCalculationBase::UPF2KeyAbilityTemlCalculationBase(const FGameplayTag& StatPrefixTag,
                                                                     const FGameplayTag& KeyAbilityPrefixTag,
                                                                     const float         BaseValue) :
	StatPrefixTag(StatPrefixTag),
	BaseValue(BaseValue)
{
	this->DefineKeyAbilityCapture(
		UPF2TagLibrary::RequestCombinedTagByString(KeyAbilityPrefixTag, TEXT("Strength")),
		UPF2CharacterAttributeSet::GetAbStrengthModifierAttribute()
	);

	this->DefineKeyAbilityCapture(
		UPF2TagLibrary::RequestCombinedTagByString(KeyAbilityPrefixTag, TEXT("Dexterity")),
		UPF2CharacterAttributeSet::GetAbDexterityModifierAttribute()
	);

	this->DefineKeyAbilityCapture(
		UPF2TagLibrary::RequestCombinedTagByString(KeyAbilityPrefixTag, TEXT("Constitution")),
		UPF2CharacterAttributeSet::GetAbConstitutionModifierAttribute()
	);

	this->DefineKeyAbilityCapture(
		UPF2TagLibrary::RequestCombinedTagByString(KeyAbilityPrefixTag, TEXT("Intelligence")),
		UPF2CharacterAttributeSet::GetAbIntelligenceModifierAttribute()
	);

	this->DefineKeyAbilityCapture(
		UPF2TagLibrary::RequestCombinedTagByString(KeyAbilityPrefixTag, TEXT("Wisdom")),
		UPF2CharacterAttributeSet::GetAbWisdomModifierAttribute()
	);

	this->DefineKeyAbilityCapture(
		UPF2TagLibrary::RequestCombinedTagByString(KeyAbilityPrefixTag, TEXT("Charisma")),
		UPF2CharacterAttributeSet::GetAbCharismaModifierAttribute()
	);
}

void UPF2KeyAbilityTemlCalculationBase::DefineKeyAbilityCapture(const FGameplayTag&       KeyAbilityTag,
                                                                const FGameplayAttribute& Attribute)
{
	const FGameplayEffectAttributeCaptureDefinition CaptureDefinition =
		PF2GameplayAbilityUtilities::BuildSourceCaptureFor(Attribute);

	this->KeyAbilityCaptureDefinitions.Add(KeyAbilityTag, CaptureDefinition);
	this->RelevantAttributesToCapture.Add(CaptureDefinition);
}

float UPF2KeyAbilityTemlCalculationBase::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	// Logic shared by the "Class DC", "Spell Attack Roll", and "Spell DC" calculations.
	// "A class DC ... equals 10 plus their proficiency bonus for their class DC (+3 for most 1st-level characters) plus
	// the modifier for the class’s key ability score."
	//
	// Source: Pathfinder 2E Core Rulebook, page 29, "Class DC".
	//
	//
	// "Spell attack roll = your spellcasting ability modifier + proficiency bonus + other bonuses + penalties
	// Spell DC = 10 + your spellcasting ability modifier + proficiency bonus + other bonuses + penalties"
	//
	// Source: Pathfinder 2E Core Rulebook, page 298, "Spell Attack Roll and Spell DC".
	const float ProficiencyBonus   = FPF2TemlCalculation(this->StatPrefixTag, Spec).GetValue(),
	            KeyAbilityModifier = this->CalculateKeyAbilityModifier(Spec),
	            AbilityScore       = this->BaseValue + ProficiencyBonus + KeyAbilityModifier;

	UE_LOG(
		LogPf2Stats,
		VeryVerbose,
		TEXT("Calculated key ability score ('%s'): %f + %f + %f = %f"),
		*(this->StatPrefixTag.ToString()),
		this->BaseValue,
		ProficiencyBonus,
		KeyAbilityModifier,
		AbilityScore
	);

	return AbilityScore;
}

float UPF2KeyAbilityTemlCalculationBase::CalculateKeyAbilityModifier(const FGameplayEffectSpec& Spec) const
{
	float                        KeyAbilityModifier = 0.0f;
	const FGameplayTagContainer* SourceTags         = Spec.CapturedSourceTags.GetAggregatedTags();

	// ReSharper disable once CppTooWideScopeInitStatement
	const FGameplayEffectAttributeCaptureDefinition KeyAbilityCaptureDefinition =
		this->DetermineKeyAbility(SourceTags);

	if (KeyAbilityCaptureDefinition.AttributeToCapture.IsValid())
	{
		const FAggregatorEvaluateParameters EvaluationParameters =
			UPF2AbilitySystemLibrary::BuildEvaluationParameters(Spec);

		this->GetCapturedAttributeMagnitude(
			KeyAbilityCaptureDefinition,
			Spec,
			EvaluationParameters,
			KeyAbilityModifier
		);
	}

	return KeyAbilityModifier;
}

FGameplayEffectAttributeCaptureDefinition UPF2KeyAbilityTemlCalculationBase::DetermineKeyAbility(
	const FGameplayTagContainer* SourceTags) const
{
	FGameplayEffectAttributeCaptureDefinition KeyAbilityCaptureDefinition;

	for (auto PairIterator = this->KeyAbilityCaptureDefinitions.CreateConstIterator(); PairIterator; ++PairIterator)
	{
		if (const FGameplayTag Tag = PairIterator.Key(); SourceTags->HasTag(Tag))
		{
			KeyAbilityCaptureDefinition = PairIterator.Value();
			break;
		}
	}

	return KeyAbilityCaptureDefinition;
}

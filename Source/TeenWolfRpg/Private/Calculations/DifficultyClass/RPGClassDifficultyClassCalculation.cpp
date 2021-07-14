// Teen Wolf RPG game logic, Copyright 2021, Teen Wolf RPG. All Rights Reserved.
// Content from Pathfinder 2nd Edition is licensed under the Open Game License (OGL) v1.0a, subject to the following:
//	 - Open Game License v 1.0a, Copyright 2000, Wizards of the Coast, Inc.
//	 - System Reference Document, Copyright 2000, Wizards of the Coast, Inc.
//	 - Pathfinder Core Rulebook (Second Edition), Copyright 2019, Paizo Inc.
// Except for material designated as Product Identity or External Tools, the game mechanics of this Teen Wolf RPG
// product are Open Game Content, as defined in the Open Game License version 1.0a, Section 1(d) (see accompanying
// LICENSE.TXT). No portion of this work other than the material designated as Open Game Content may be reproduced in
// any form without written permission.

#include "TeenWolfRpg.h"
#include "GameplayAbilityUtils.h"
#include "Abilities/RPGAttributeSet.h"
#include "Calculations/DifficultyClass/RPGClassDifficultyClassCalculation.h"

URPGClassDifficultyClassCalculation::URPGClassDifficultyClassCalculation() :
	UGameplayModMagnitudeCalculation()
{
	this->DefineKeyAbilityCapture(
		TEXT("KeyAbility.Strength"),
		URPGAttributeSet::GetAbStrengthModifierAttribute()
	);

	this->DefineKeyAbilityCapture(
		TEXT("KeyAbility.Dexterity"),
		URPGAttributeSet::GetAbDexterityModifierAttribute()
	);

	this->DefineKeyAbilityCapture(
		TEXT("KeyAbility.Constitution"),
		URPGAttributeSet::GetAbConstitutionModifierAttribute()
	);

	this->DefineKeyAbilityCapture(
		TEXT("KeyAbility.Intelligence"),
		URPGAttributeSet::GetAbIntelligenceModifierAttribute()
	);

	this->DefineKeyAbilityCapture(
		TEXT("KeyAbility.Wisdom"),
		URPGAttributeSet::GetAbWisdomModifierAttribute()
	);

	this->DefineKeyAbilityCapture(
		TEXT("KeyAbility.Charisma"),
		URPGAttributeSet::GetAbCharismaModifierAttribute()
	);
}

float URPGClassDifficultyClassCalculation::CalculateProficiencyBonus(const FGameplayEffectSpec& Spec)
{
	float						ProficiencyBonus    = 0;
	const FGameplayTagContainer	*SourceTags			= Spec.CapturedSourceTags.GetAggregatedTags();

	// Bypass additional checks if the character has no Class DC proficiency, to avoid checking every TEML option.
	if (GameplayAbilityUtils::HasTag(SourceTags, TEXT("ClassDc")))
	{
		const float CharacterLevel = Spec.GetLevel();

		if (GameplayAbilityUtils::HasTag(SourceTags, TEXT("ClassDc.Legendary")))
		{
			// Legendary -> Your level + 8
			ProficiencyBonus += CharacterLevel + 8;
		}
		else if (GameplayAbilityUtils::HasTag(SourceTags, TEXT("ClassDc.Master")))
		{
			// Master -> Your level + 6
			ProficiencyBonus += CharacterLevel + 6;
		}
		else if (GameplayAbilityUtils::HasTag(SourceTags, TEXT("ClassDc.Expert")))
		{
			// Expert -> Your level + 4
			ProficiencyBonus += CharacterLevel + 4;
		}
		else if (GameplayAbilityUtils::HasTag(SourceTags, TEXT("ClassDc.Trained")))
		{
			// Trained -> Your level + 2
			ProficiencyBonus += CharacterLevel + 2;
		}
		else
		{
			// Untrained -> No bonus at all, no matter what level.
			ProficiencyBonus += 0;
		}
	}

	return ProficiencyBonus;
}

float URPGClassDifficultyClassCalculation::CalculateBaseMagnitude_Implementation(
																				const FGameplayEffectSpec& Spec) const
{
	// Source for all that follows: Pathfinder 2E Core Rulebook, page 29, "Class DC".
	//
	// "A class DC sets the difficulty for certain abilities granted by your character’s class. This DC equals 10 plus
	// their proficiency bonus for their class DC (+3 for most 1st-level characters) plus the modifier for the class’s
	// key ability score."
	return 10.0f + CalculateProficiencyBonus(Spec) + CalculateKeyAbilityModifier(Spec);
}

float URPGClassDifficultyClassCalculation::CalculateKeyAbilityModifier(const FGameplayEffectSpec& Spec) const
{
	float											KeyAbilityModifier			= 0.0f;
	const FGameplayTagContainer						*SourceTags					= Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayEffectAttributeCaptureDefinition	KeyAbilityCaptureDefinition	= DetermineKeyAbility(SourceTags);

	if (KeyAbilityCaptureDefinition.AttributeToCapture.IsValid())
	{
		const FGameplayTagContainer		*TargetTags				= Spec.CapturedTargetTags.GetAggregatedTags();
		FAggregatorEvaluateParameters	EvaluationParameters;

		EvaluationParameters.SourceTags = SourceTags;
		EvaluationParameters.TargetTags = TargetTags;

		GetCapturedAttributeMagnitude(KeyAbilityCaptureDefinition, Spec, EvaluationParameters, KeyAbilityModifier);
	}

	return KeyAbilityModifier;
}

FGameplayEffectAttributeCaptureDefinition URPGClassDifficultyClassCalculation::DetermineKeyAbility(
																		const FGameplayTagContainer* SourceTags) const
{
	FGameplayEffectAttributeCaptureDefinition KeyAbilityCaptureDefinition;

	for (auto PairIterator = this->KeyAbilityCaptureDefinitions.CreateConstIterator(); PairIterator; ++PairIterator)
	{
		const FString TagName = PairIterator.Key();

		if (GameplayAbilityUtils::HasTag(SourceTags, TagName))
		{
			KeyAbilityCaptureDefinition = PairIterator.Value();
			break;
		}
	}

	return KeyAbilityCaptureDefinition;
}

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
#include "Calculations/RPGKeyAbilityCalculationBase.h"

URPGKeyAbilityCalculationBase::URPGKeyAbilityCalculationBase() :
	URPGKeyAbilityCalculationBase(
		TEXT(""),
		TEXT("KeyAbility")
	)
{
}

URPGKeyAbilityCalculationBase::URPGKeyAbilityCalculationBase(const FString StatGameplayTagPrefix,
															 const FString KeyAbilityGameplayTagPrefix,
															 const float BaseValue) :
	URPGTemlCalculationBase(),
	StatGameplayTagPrefix(StatGameplayTagPrefix),
	BaseValue(BaseValue)
{
	this->DefineKeyAbilityCapture(
		KeyAbilityGameplayTagPrefix + ".Strength",
		URPGAttributeSet::GetAbStrengthModifierAttribute()
	);

	this->DefineKeyAbilityCapture(
		KeyAbilityGameplayTagPrefix + ".Dexterity",
		URPGAttributeSet::GetAbDexterityModifierAttribute()
	);

	this->DefineKeyAbilityCapture(
		KeyAbilityGameplayTagPrefix + ".Constitution",
		URPGAttributeSet::GetAbConstitutionModifierAttribute()
	);

	this->DefineKeyAbilityCapture(
		KeyAbilityGameplayTagPrefix + ".Intelligence",
		URPGAttributeSet::GetAbIntelligenceModifierAttribute()
	);

	this->DefineKeyAbilityCapture(
		KeyAbilityGameplayTagPrefix + ".Wisdom",
		URPGAttributeSet::GetAbWisdomModifierAttribute()
	);

	this->DefineKeyAbilityCapture(
		KeyAbilityGameplayTagPrefix + ".Charisma",
		URPGAttributeSet::GetAbCharismaModifierAttribute()
	);
}

void URPGKeyAbilityCalculationBase::DefineKeyAbilityCapture(const FString KeyAbilityTagName,
															const FGameplayAttribute Attribute)
{
	const FGameplayEffectAttributeCaptureDefinition CaptureDefinition =
		GameplayAbilityUtils::BuildSourceCaptureFor(Attribute);

	this->KeyAbilityCaptureDefinitions.Add(
		KeyAbilityTagName,
		CaptureDefinition
	);

	this->RelevantAttributesToCapture.Add(CaptureDefinition);
}

float URPGKeyAbilityCalculationBase::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
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
	const float	ProficiencyBonus	= CalculateProficiencyBonus(this->StatGameplayTagPrefix, Spec),
				KeyAbilityModifier	= CalculateKeyAbilityModifier(Spec),
				AbilityScore		= this->BaseValue + ProficiencyBonus + KeyAbilityModifier;

	UE_LOG(
		LogTwRpg,
		VeryVerbose,
		TEXT("Calculated key ability score ('%s'): %f + %f + %f = %f"),
		*(this->StatGameplayTagPrefix),
		this->BaseValue,
		ProficiencyBonus,
		KeyAbilityModifier,
		AbilityScore
	);

	return AbilityScore;
}

float URPGKeyAbilityCalculationBase::CalculateKeyAbilityModifier(const FGameplayEffectSpec& Spec) const
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

FGameplayEffectAttributeCaptureDefinition URPGKeyAbilityCalculationBase::DetermineKeyAbility(
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

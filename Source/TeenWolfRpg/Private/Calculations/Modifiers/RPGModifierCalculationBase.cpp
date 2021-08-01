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
#include "Calculations/Modifiers/RPGModifierCalculationBase.h"

URPGModifierCalculationBase::URPGModifierCalculationBase(const FGameplayAttribute SkillAbilityAttribute,
														 const FString SkillGameplayTagPrefix) :
	UGameplayModMagnitudeCalculation()
{
	this->SkillAbilityCaptureDefinition.AttributeToCapture	= SkillAbilityAttribute;
	this->SkillAbilityCaptureDefinition.AttributeSource		= EGameplayEffectAttributeCaptureSource::Source;
	this->SkillAbilityCaptureDefinition.bSnapshot			= false;

	RelevantAttributesToCapture.Add(this->SkillAbilityCaptureDefinition);

	this->SkillGameplayTagPrefix = SkillGameplayTagPrefix;
}

float URPGModifierCalculationBase::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	float							AbilityScore			= 0.0f,
									ProficiencyBonus;
	const FGameplayTagContainer		*SourceTags				= Spec.CapturedSourceTags.GetAggregatedTags(),
									*TargetTags				= Spec.CapturedTargetTags.GetAggregatedTags();
	FAggregatorEvaluateParameters	EvaluationParameters;

	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	GetCapturedAttributeMagnitude(this->SkillAbilityCaptureDefinition, Spec, EvaluationParameters, AbilityScore);

	// Source for all that follows: Pathfinder 2E Core Rulebook, page 444,
	// "Step 1: Roll D20 and Identify The Modifiers, Bonuses, and Penalties That Apply".
	//
	// Start with a bonus equal to the character's score in the ability that influences the skill (e.g. Dexterity
	// affects Acrobatics, Intelligence affects Arcana, etc.)
	ProficiencyBonus = AbilityScore;

	// Bypass additional checks if the character has no proficiency with this skill, to avoid checking every TEML
	// option.
	if (GameplayAbilityUtils::HasTag(SourceTags, this->SkillGameplayTagPrefix))
	{
		const float CharacterLevel = Spec.GetLevel();

		// "When attempting a check that involves something you have some training in, you will also add your
		// proficiency bonus. This bonus depends on your proficiency rank: untrained, trained, expert, master, or
		// legendary. If you’re untrained, your bonus is +0—you must rely on raw talent and any bonuses from the
		// situation. Otherwise, the bonus equals your character’s level plus a certain amount depending on your rank.
		// If your proficiency rank is trained, this bonus is equal to your level + 2, and higher proficiency ranks
		// further increase the amount you add to your level."
		if (GameplayAbilityUtils::HasTag(SourceTags, this->SkillGameplayTagPrefix + ".Legendary"))
		{
			// Legendary -> Your level + 8
			ProficiencyBonus += CharacterLevel + 8;
		}
		else if (GameplayAbilityUtils::HasTag(SourceTags, this->SkillGameplayTagPrefix + ".Master"))
		{
			// Master -> Your level + 6
			ProficiencyBonus += CharacterLevel + 6;
		}
		else if (GameplayAbilityUtils::HasTag(SourceTags, this->SkillGameplayTagPrefix + ".Expert"))
		{
			// Expert -> Your level + 4
			ProficiencyBonus += CharacterLevel + 4;
		}
		else if (GameplayAbilityUtils::HasTag(SourceTags, this->SkillGameplayTagPrefix + ".Trained"))
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

	UE_LOG(
		LogTwRpg,
		VeryVerbose,
		TEXT("Calculated skill proficiency/modifier ('%s': %f): %f"),
		*(this->SkillGameplayTagPrefix),
		AbilityScore,
		ProficiencyBonus
	);

	return ProficiencyBonus;
}

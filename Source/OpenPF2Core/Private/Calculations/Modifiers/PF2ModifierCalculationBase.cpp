// OpenPF2 for UE Game Logic, Copyright 2021, Guy Elsmore-Paddock. All Rights Reserved.
//
// Content from Pathfinder 2nd Edition is licensed under the Open Game License (OGL) v1.0a, subject to the following:
//	 - Open Game License v 1.0a, Copyright 2000, Wizards of the Coast, Inc.
//	 - System Reference Document, Copyright 2000, Wizards of the Coast, Inc.
//	 - Pathfinder Core Rulebook (Second Edition), Copyright 2019, Paizo Inc.
// Except for material designated as Product Identity, the game mechanics and logic in this file are Open Game Content,
// as defined in the Open Game License version 1.0a, Section 1(d) (see accompanying LICENSE.TXT). No portion of this
// file other than the material designated as Open Game Content may be reproduced in any form without written
// permission.

#include "Calculations/Modifiers/PF2ModifierCalculationBase.h"

#include "OpenPF2Core.h"
#include "GameplayAbilityUtils.h"
#include "Abilities/PF2AttributeSet.h"

UPF2ModifierCalculationBase::UPF2ModifierCalculationBase(const FGameplayAttribute SkillAbilityAttribute,
														 const FString SkillGameplayTagPrefix) :
	UPF2TemlCalculationBase()
{
	this->SkillAbilityCaptureDefinition.AttributeToCapture	= SkillAbilityAttribute;
	this->SkillAbilityCaptureDefinition.AttributeSource		= EGameplayEffectAttributeCaptureSource::Source;
	this->SkillAbilityCaptureDefinition.bSnapshot			= false;

	RelevantAttributesToCapture.Add(this->SkillAbilityCaptureDefinition);

	this->SkillGameplayTagPrefix = SkillGameplayTagPrefix;
}

float UPF2ModifierCalculationBase::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	float							AbilityScore			= 0.0f,
									ProficiencyBonus,
									Modifier;
	const FGameplayTagContainer		*SourceTags				= Spec.CapturedSourceTags.GetAggregatedTags(),
									*TargetTags				= Spec.CapturedTargetTags.GetAggregatedTags();
	FAggregatorEvaluateParameters	EvaluationParameters;

	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	GetCapturedAttributeMagnitude(this->SkillAbilityCaptureDefinition, Spec, EvaluationParameters, AbilityScore);

	// "In the second box to the right of each skill name on your character sheet, there’s an abbreviation that reminds
	// you of the ability score tied to that skill. For each skill in which your character is trained, add your
	// proficiency bonus for that skill (typically +3 for a 1st-level character) to the indicated ability’s modifier, as
	// well as any other applicable bonuses and penalties, to determine the total modifier for that skill. For skills
	// your character is untrained in, use the same method, but your proficiency bonus is +0."
	//
	// Source: Pathfinder 2E Core Rulebook, page 28, "Skills".
	ProficiencyBonus = CalculateProficiencyBonus(this->SkillGameplayTagPrefix, Spec);

	Modifier = AbilityScore + ProficiencyBonus;

	UE_LOG(
		LogPf2Core,
		VeryVerbose,
		TEXT("Calculated modifier ('%s'): %f + %f = %f"),
		*(this->SkillGameplayTagPrefix),
		AbilityScore,
		ProficiencyBonus,
		Modifier
	);

	return Modifier;
}

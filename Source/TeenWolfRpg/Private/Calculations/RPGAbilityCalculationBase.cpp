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
#include "Abilities/RPGAttributeSet.h"

#include "Calculations/RPGAbilityCalculationBase.h"

float URPGAbilityCalculationBase::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	float		Value					= 0.0f;
	const int	CapturedAttributeCount	= RelevantAttributesToCapture.Num();

	if (CapturedAttributeCount == 0)
	{
		UE_LOG(
			LogTwRpg,
			Error,
			TEXT("No attributes were captured for calculation; exactly 1 was expected.")
		);
	}
	else if (CapturedAttributeCount == 1)
	{
		Value = DoCalculation(Spec);
	}
	else
	{
		UE_LOG(
			LogTwRpg,
			Error,
			TEXT("Multiple attributes (%d) were captured for calculation, when exactly 1 was expected."),
			CapturedAttributeCount
		);
	}

	return Value;
}

float URPGAbilityCalculationBase::DoCalculation(const FGameplayEffectSpec& Spec) const
{
	const FGameplayEffectAttributeCaptureDefinition AbilityAttributeDef   = RelevantAttributesToCapture[0];
	const FGameplayAttribute						AbilityAttribute	  = AbilityAttributeDef.AttributeToCapture;
	const FGameplayTagContainer						*SourceTags			  = Spec.CapturedSourceTags.GetAggregatedTags(),
													*TargetTags			  = Spec.CapturedTargetTags.GetAggregatedTags();
	FAggregatorEvaluateParameters					EvaluationParameters;
	float											AbilityScore		  = 0.0f;

	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	GetCapturedAttributeMagnitude(AbilityAttributeDef, Spec, EvaluationParameters, AbilityScore);

	return DoCalculation(AbilityAttribute, AbilityScore);
}

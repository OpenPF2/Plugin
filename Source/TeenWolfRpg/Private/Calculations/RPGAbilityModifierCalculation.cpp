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

#include "Calculations/RPGAbilityModifierCalculation.h"

float URPGAbilityModifierCalculation::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	float		Modifier				= 0.0f;
	const int	CapturedAttributeCount	= RelevantAttributesToCapture.Num();

	if (CapturedAttributeCount == 0)
	{
		UE_LOG(
			LogTwRpg,
			Error,
			TEXT("No attributes were captured for modifier calculation; exactly 1 was expected.")
		);
	}
	else if (CapturedAttributeCount == 1)
	{
		Modifier = CalculateAbilityModifier(Spec);
	}
	else
	{
		UE_LOG(
			LogTwRpg,
			Error,
			TEXT("Multiple attributes (%d) were captured for modifier calculation, when only 1 was expected."),
			CapturedAttributeCount
		);
	}

	return Modifier;
}

float URPGAbilityModifierCalculation::CalculateAbilityModifier(const FGameplayEffectSpec& Spec) const
{
	const FGameplayEffectAttributeCaptureDefinition CapturedAttributeDef  = RelevantAttributesToCapture[0];
	const FGameplayAttribute						CapturedAttribute	  = CapturedAttributeDef.AttributeToCapture;
	const FGameplayTagContainer						*SourceTags			  = Spec.CapturedSourceTags.GetAggregatedTags(),
													*TargetTags			  = Spec.CapturedTargetTags.GetAggregatedTags();
	FAggregatorEvaluateParameters					EvaluationParameters;
	float											AbilityScore		  = 0.0f,
													AbilityModifier;

	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	GetCapturedAttributeMagnitude(CapturedAttributeDef, Spec, EvaluationParameters, AbilityScore);

	// Source: Pathfinder 2E Core Rulebook, page 20, Table 1-1: Ability Modifiers.
	AbilityModifier = FMath::FloorToFloat(AbilityScore / 2.0f) - 5.0f;

	UE_LOG(
		LogTwRpg,
		VeryVerbose,
		TEXT("Calculated ability modifier for attribute ('%s': %f): %f"),
		*(CapturedAttribute.GetName()),
		AbilityScore,
		AbilityModifier
	);

	return AbilityModifier;
}

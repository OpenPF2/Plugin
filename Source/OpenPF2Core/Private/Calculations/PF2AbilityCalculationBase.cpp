// OpenPF2 for UE Game Logic, Copyright 2021, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "Calculations/PF2AbilityCalculationBase.h"

#include "OpenPF2Core.h"
#include "Abilities/PF2AttributeSet.h"

float UPF2AbilityCalculationBase::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	float		Value					= 0.0f;
	const int	CapturedAttributeCount	= RelevantAttributesToCapture.Num();

	if (CapturedAttributeCount == 0)
	{
		UE_LOG(
			LogPf2Core,
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
			LogPf2Core,
			Error,
			TEXT("Multiple attributes (%d) were captured for calculation, when exactly 1 was expected."),
			CapturedAttributeCount
		);
	}

	return Value;
}

float UPF2AbilityCalculationBase::DoCalculation(const FGameplayEffectSpec& Spec) const
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

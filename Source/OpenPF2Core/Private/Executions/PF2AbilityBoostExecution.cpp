// OpenPF2 for UE Game Logic, Copyright 2021, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "Executions/PF2AbilityBoostExecution.h"
#include "OpenPF2Core.h"
#include "Abilities/PF2AbilityAttributes.h"
#include "Abilities/PF2AttributeSet.h"

const FGameplayEffectAttributeCaptureDefinition* UPF2AbilityBoostExecution::GetTargetCaptureDefinition() const
{
	const FPF2AbilityAttributes&	AbilityAttributes = FPF2AbilityAttributes::GetInstance();

	return AbilityAttributes.GetCaptureByAttribute(this->GetTargetAbilityAttribute());
}

UPF2AbilityBoostExecution::UPF2AbilityBoostExecution()
{
	const FPF2AbilityAttributes AbilityAttributes = FPF2AbilityAttributes::GetInstance();

	for (auto& Elem : AbilityAttributes.GetCaptureDefinitions())
	{
		RelevantAttributesToCapture.Add(Elem);
	}
}

void UPF2AbilityBoostExecution::Execute_Implementation(
													const FGameplayEffectCustomExecutionParameters& ExecutionParams,
													OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	const FGameplayEffectAttributeCaptureDefinition* CaptureDefinition = this->GetTargetCaptureDefinition();

	if (CaptureDefinition == nullptr)
	{
		UE_LOG(
			LogPf2Core,
			Error,
			TEXT("GE execution '%s' can only boost ability-related attributes, but was invoked with the attribute '%s'."),
			*(this->GetClass()->GetName()),
			*(this->GetTargetAbilityAttribute().GetName())
		);
	}
	else
	{
		DoCalculation(
			ExecutionParams,
			*CaptureDefinition,
			OutExecutionOutput
		);
	}
}

void UPF2AbilityBoostExecution::DoCalculation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
											  const FGameplayEffectAttributeCaptureDefinition TargetCapture,
											  OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	const FPF2AbilityAttributes&	AbilityAttributes		 = FPF2AbilityAttributes::GetInstance();
	const FGameplayAttribute&		TargetAttribute			 = this->GetTargetAbilityAttribute();
	const FGameplayEffectSpec&		Spec					 = ExecutionParams.GetOwningSpec();
	const FGameplayTagContainer		*SourceTags				 = Spec.CapturedSourceTags.GetAggregatedTags(),
									*TargetTags				 = Spec.CapturedTargetTags.GetAggregatedTags();
	FAggregatorEvaluateParameters	EvaluationParameters;
	float							CurrentAppliedBoostCount = 0,
									CurrentAbilityScore		 = 0.0f,
									BoostAmount;

	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(
		AbilityAttributes.AbBoostCountDef,
		EvaluationParameters,
		CurrentAppliedBoostCount
	);

	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(
		TargetCapture,
		EvaluationParameters,
		CurrentAbilityScore
	);

	BoostAmount = this->CalculateBoost(CurrentAbilityScore);

	UE_LOG(
		LogPf2Core,
		VeryVerbose,
		TEXT("Calculated GEX boost for ability score attribute ('%s'): %f + %f = %f"),
		*(TargetAttribute.GetName()),
		CurrentAbilityScore,
		BoostAmount,
		CurrentAbilityScore + BoostAmount
	);

	OutExecutionOutput.AddOutputModifier(
		FGameplayModifierEvaluatedData(
			AbilityAttributes.AbBoostCountProperty,
			EGameplayModOp::Additive,
			1
		)
	);

	OutExecutionOutput.AddOutputModifier(
		FGameplayModifierEvaluatedData(
			TargetAttribute,
			EGameplayModOp::Additive,
			BoostAmount
		)
	);
}

float UPF2AbilityBoostExecution::CalculateBoost(const float BaseAbilityScore)
{
	float Boost;

	// From the Pathfinder 2E Core Rulebook, page 68, "Ability Boosts":
	// "Boosting an ability score increases it by 1 if it's already 18 or above, or by 2 if it starts out below 18."
	if (BaseAbilityScore < 18.0f)
	{
		Boost = 2.0f;
	}
	else
	{
		Boost = 1.0f;
	}

	return Boost;
}

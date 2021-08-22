// OpenPF2 for UE Game Logic, Copyright 2021, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "Executions/PF2AbilityBoostExecution.h"
#include "OpenPF2Core.h"
#include "Abilities/PF2AttributeSet.h"
#include "Effects/PF2AbilityBoostGameplayEffect.h"

#define DEFINE_ABILITY_CAPTUREDEF(S, P, T, B) \
{ \
	DEFINE_ATTRIBUTE_CAPTUREDEF(S, P, T, B) \
	this->CaptureDefinitions.Add(P##Property->GetName(), P##Def); \
}

class FPF2AbilityAttributes final
{
public:
	DECLARE_ATTRIBUTE_CAPTUREDEF(AbBoostCount);
	DECLARE_ATTRIBUTE_CAPTUREDEF(AbCharisma);
	DECLARE_ATTRIBUTE_CAPTUREDEF(AbConstitution);
	DECLARE_ATTRIBUTE_CAPTUREDEF(AbDexterity);
	DECLARE_ATTRIBUTE_CAPTUREDEF(AbIntelligence);
	DECLARE_ATTRIBUTE_CAPTUREDEF(AbStrength);
	DECLARE_ATTRIBUTE_CAPTUREDEF(AbWisdom);

	static const FPF2AbilityAttributes& Get()
	{
		static FPF2AbilityAttributes AbilityStatics;

		return AbilityStatics;
	}

	FGameplayEffectAttributeCaptureDefinition GetCaptureDefinitionByAttribute(const FGameplayAttribute TargetAttribute) const
	{
		return this->GetCaptureDefinitionByAttributeName(TargetAttribute.GetName());
	}

	FGameplayEffectAttributeCaptureDefinition GetCaptureDefinitionByAttributeName(FString Name) const
	{
		return CaptureDefinitions[Name];
	}

private:
	TMap<FString, FGameplayEffectAttributeCaptureDefinition> CaptureDefinitions;

	FPF2AbilityAttributes()
	{
		DEFINE_ABILITY_CAPTUREDEF(UPF2AttributeSet, AbBoostCount, Target, false);
		DEFINE_ABILITY_CAPTUREDEF(UPF2AttributeSet, AbCharisma, Target, false);
		DEFINE_ABILITY_CAPTUREDEF(UPF2AttributeSet, AbConstitution, Target, false);
		DEFINE_ABILITY_CAPTUREDEF(UPF2AttributeSet, AbDexterity, Target, true);
		DEFINE_ABILITY_CAPTUREDEF(UPF2AttributeSet, AbIntelligence, Target, true);
		DEFINE_ABILITY_CAPTUREDEF(UPF2AttributeSet, AbStrength, Target, true);
		DEFINE_ABILITY_CAPTUREDEF(UPF2AttributeSet, AbWisdom, Target, true);
	}
};

UPF2AbilityBoostExecution::UPF2AbilityBoostExecution()
{
	const FPF2AbilityAttributes AbilityAttributes = FPF2AbilityAttributes::Get();

	RelevantAttributesToCapture.Add(AbilityAttributes.AbBoostCountDef);
	RelevantAttributesToCapture.Add(AbilityAttributes.AbCharismaDef);
	RelevantAttributesToCapture.Add(AbilityAttributes.AbConstitutionDef);
	RelevantAttributesToCapture.Add(AbilityAttributes.AbDexterityDef);
	RelevantAttributesToCapture.Add(AbilityAttributes.AbIntelligenceDef);
	RelevantAttributesToCapture.Add(AbilityAttributes.AbStrengthDef);
	RelevantAttributesToCapture.Add(AbilityAttributes.AbWisdomDef);
}

void UPF2AbilityBoostExecution::Execute_Implementation(
													const FGameplayEffectCustomExecutionParameters& ExecutionParams,
													OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	const FGameplayEffectSpec&	Spec = ExecutionParams.GetOwningSpec();

	const UPF2AbilityBoostGameplayEffect*	BoostDefinition =
		Cast<const UPF2AbilityBoostGameplayEffect>(Spec.Def);

	if (BoostDefinition == nullptr)
	{
		UE_LOG(
			LogPf2Core,
			Error,
			TEXT("GE execution '%s' was invoked by a GE that is of type '%s', which is not '%s' or one of its sub-classes."),
			*(this->GetClass()->GetName()),
			*(Spec.Def->GetClass()->GetName()),
			*(UPF2AbilityBoostGameplayEffect::StaticClass()->GetName())
		);
	}
	else
	{
		const FGameplayAttribute TargetAttribute = BoostDefinition->GetTargetAbilityAttribute();

		DoCalculation(ExecutionParams, TargetAttribute, OutExecutionOutput);
	}
}

void UPF2AbilityBoostExecution::DoCalculation(
											const FGameplayEffectCustomExecutionParameters& ExecutionParams,
											const FGameplayAttribute& TargetAttribute,
											OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	const FPF2AbilityAttributes		AbilityAttributes		 = FPF2AbilityAttributes::Get();
	const FGameplayEffectSpec&		Spec					 = ExecutionParams.GetOwningSpec();
	const FGameplayTagContainer		*SourceTags				 = Spec.CapturedSourceTags.GetAggregatedTags(),
									*TargetTags				 = Spec.CapturedTargetTags.GetAggregatedTags();
	FAggregatorEvaluateParameters	EvaluationParameters;
	float							CurrentAppliedBoostCount = 0,
									CurrentAbilityScore		 = 0.0f,
									BoostAmount;

	const FGameplayEffectAttributeCaptureDefinition TargetCapture =
		AbilityAttributes.GetCaptureDefinitionByAttribute(TargetAttribute);

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
		TEXT("Calculated boost for ability score attribute ('%s'): %f + %f = %f"),
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

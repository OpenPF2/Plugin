// OpenPF2 for UE Game Logic, Copyright 2021-2022, Guy Elsmore-Paddock. All Rights Reserved.
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

#include "Calculations/PF2StandardDamageExecution.h"

#include "Abilities/PF2CharacterAttributeStatics.h"
#include "Utilities/PF2GameplayAbilityUtilities.h"

UPF2StandardDamageExecution::UPF2StandardDamageExecution() :
	DamageParameterTag(FGameplayTag::RequestGameplayTag(this->DamageParameterTagName)),
	ResistanceParameterTag(FGameplayTag::RequestGameplayTag(this->ResistanceParameterTagName))
{
	this->ValidTransientAggregatorIdentifiers.AddTag(this->DamageParameterTag);
	this->ValidTransientAggregatorIdentifiers.AddTag(this->ResistanceParameterTag);
}

void UPF2StandardDamageExecution::Execute_Implementation(
	const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	OUT FGameplayEffectCustomExecutionOutput&       OutExecutionOutput) const
{
	float IncomingDamage = 0.0f,
	      Resistance     = 0.0f,
	      DamageDone;

	const FGameplayEffectSpec&   Spec       = ExecutionParams.GetOwningSpec();
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;

	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	ExecutionParams.AttemptCalculateTransientAggregatorMagnitude(
		this->DamageParameterTag,
		EvaluationParameters,
		IncomingDamage
	);

	ExecutionParams.AttemptCalculateTransientAggregatorMagnitude(
		this->ResistanceParameterTag,
		EvaluationParameters,
		Resistance
	);

	// Don't allow resistance to make damage negative (i.e., damage can never heal, but it can become ineffectual).
	//
	// From the Pathfinder 2E Core Rulebook, page 453, "Resistance":
	// "If you have resistance to a type of damage, each time you take that type of damage, you reduce the amount of
	// damage you take by the listed amount (to a minimum of 0 damage)."
	DamageDone = FMath::Max(0.0f, IncomingDamage - Resistance);

	if (DamageDone > 0.0f)
	{
		OutExecutionOutput.AddOutputModifier(
			FGameplayModifierEvaluatedData(
				FPF2CharacterAttributeStatics::GetInstance().TmpDamageIncomingProperty,
				EGameplayModOp::Additive,
				DamageDone
			)
		);
	}
}

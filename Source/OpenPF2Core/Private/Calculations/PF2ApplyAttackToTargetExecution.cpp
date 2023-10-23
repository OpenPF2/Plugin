// OpenPF2 for UE Game Logic, Copyright 2023, Guy Elsmore-Paddock. All Rights Reserved.
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

#include "Calculations/PF2ApplyAttackToTargetExecution.h"

#include "Abilities/PF2AttackAttributeStatics.h"
#include "Abilities/PF2TargetCharacterAttributeStatics.h"


UPF2ApplyAttackToTargetExecution::UPF2ApplyAttackToTargetExecution()
{
	const FPF2AttackAttributeStatics          AttackCaptures = FPF2AttackAttributeStatics::GetInstance();
	const FPF2TargetCharacterAttributeStatics TargetCaptures = FPF2TargetCharacterAttributeStatics::GetInstance();

	this->RelevantAttributesToCapture.Add(AttackCaptures.TmpAttackDegreeOfSuccessDef);

	for (const FGameplayEffectAttributeCaptureDefinition* Capture : AttackCaptures.GetAllDamageCaptures())
	{
		this->RelevantAttributesToCapture.Add(*Capture);
	}
}

void UPF2ApplyAttackToTargetExecution::Execute_Implementation(
	const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	const FGameplayEffectSpec                 OwningSpec            = ExecutionParams.GetOwningSpec();
	const FGameplayTagContainer *             SourceTags            = OwningSpec.CapturedSourceTags.GetAggregatedTags(),
	                            *             TargetTags            = OwningSpec.CapturedTargetTags.GetAggregatedTags();
	FAggregatorEvaluateParameters             EvaluationParameters;
	const FPF2AttackAttributeStatics          AttackCaptures        = FPF2AttackAttributeStatics::GetInstance();
	const FPF2TargetCharacterAttributeStatics TargetCaptures        = FPF2TargetCharacterAttributeStatics::GetInstance();
	float                                     AttackDegreeOfSuccess;

	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	// Capture: Degree of success from attack roll.
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(
		AttackCaptures.TmpAttackDegreeOfSuccessDef,
		EvaluationParameters,
		AttackDegreeOfSuccess
	);

	// Apply: Degree of success from attack roll.
	OutExecutionOutput.AddOutputModifier(
		FGameplayModifierEvaluatedData(
			TargetCaptures.TmpIncomingAttackDegreeOfSuccessProperty,
			EGameplayModOp::Override,
			AttackDegreeOfSuccess
		)
	);

	for (const FGameplayEffectAttributeCaptureDefinition* Capture : AttackCaptures.GetAllDamageCaptures())
	{
		FString DamageAttributeName = Capture->AttributeToCapture.AttributeName;
		float   AmountFromDamageType;
		float   AmountOfResistanceToDamageType;
		float   EffectiveDamage;

		const FGameplayEffectAttributeCaptureDefinition* ResistanceCapture =
			TargetCaptures.GetResistanceCaptureForDamageAttribute(DamageAttributeName);

		// Capture: Amount of this type of damage source has attempted against the target.
		ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(
			*Capture,
			EvaluationParameters,
			AmountFromDamageType
		);

		// Capture: Amount of resistance that the target has for this type of damage.
		ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(
			*ResistanceCapture,
			EvaluationParameters,
			AmountOfResistanceToDamageType
		);

		// Apply resistance to reduce damage, but don't allow resistance to make damage negative (i.e., damage can never
		// heal, but it can become ineffectual).
		//
		// From the Pathfinder 2E Core Rulebook, page 453, "Resistance":
		// "If you have resistance to a type of damage, each time you take that type of damage, you reduce the amount of
		// damage you take by the listed amount (to a minimum of 0 damage)."
		EffectiveDamage = FMath::Max(0.0f, AmountFromDamageType - AmountOfResistanceToDamageType);

		UE_LOG(
			LogPf2CoreStats,
			VeryVerbose,
			TEXT("Damage (%s: %f) - Resistance (%s: %f) = %f (CLAMPED >= 0)."),
			*DamageAttributeName,
			AmountFromDamageType,
			*ResistanceCapture->AttributeToCapture.GetName(),
			AmountOfResistanceToDamageType,
			EffectiveDamage
		);

		if (EffectiveDamage > 0)
		{
			// Apply: Damage, less resistance.
			OutExecutionOutput.AddOutputModifier(
				FGameplayModifierEvaluatedData(
					TargetCaptures.TmpDamageIncomingProperty,
					EGameplayModOp::Additive,
					EffectiveDamage
				)
			);
		}
	}
}

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

#include "Calculations/PF2WeaponDamageExecution.h"

#include "Abilities/PF2CharacterAttributeStatics.h"

void UPF2WeaponDamageExecution::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
                                                       FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();
	const float DamageDone = 0.1f;

	OutExecutionOutput.AddOutputModifier(
		FGameplayModifierEvaluatedData(
			FPF2CharacterAttributeStatics::GetInstance().TmpDamageIncomingProperty,
			EGameplayModOp::Additive,
			DamageDone
		)
	);
}

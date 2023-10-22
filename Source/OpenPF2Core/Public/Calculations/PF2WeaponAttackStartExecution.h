// OpenPF2 for UE Game Logic, Copyright 2023, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#pragma once

#include <GameplayEffectExecutionCalculation.h>

#include "PF2WeaponAttackStartExecution.generated.h"

/**
 * An execution calculation that should appear at the start of every weapon attack gameplay effect.
 *
 * This execution initializes the transient attack attribute set with stats from the weapon at the beginning of an
 * attack. This allows subsequent gameplay effects to be applied for bonuses and penalties (e.g., runes, magical spells,
 * etc.) that affect the weapon stats before they're actually used to calculate the attack.
 */
UCLASS()
class OPENPF2CORE_API UPF2WeaponAttackStartExecution : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()

protected:
	// =================================================================================================================
	// Protected Static Methods
	// =================================================================================================================
	static void InitializeAttackStats(FGameplayEffectCustomExecutionOutput& OutExecutionOutput,
	                                  const int32                           WeaponRollCount,
	                                  const int32                           WeaponDieSize);
public:
	// =================================================================================================================
	// Public Methods - UGameplayEffectExecutionCalculation Implementation
	// =================================================================================================================
	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	                                    FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
};

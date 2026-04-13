// OpenPF2 Game Framework for Unreal Engine, Copyright 2021-2024, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#pragma once

#include <GameplayEffectExecutionCalculation.h>

#include "PF2SimpleDamageExecution.generated.h"

/**
 * Gameplay effect execution calculation that applies a fixed amount of damage to a target, factoring in resistance.
 *
 * The amount of damage to inflict and the amount of resistance that the target has to that type of damage are passed-in
 * via "Transient Aggregators" (a.k.a., "Temporary Variables" in the Editor UI). The damage is typically a
 * "set by caller" input to the GE while the resistance value is sourced from a resistance attribute on the target.
 */
UCLASS()
// ReSharper disable once CppClassCanBeFinal
class OPENPF2GAMEFRAMEWORK_API UPF2SimpleDamageExecution : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()

public:
	// =================================================================================================================
	// Public Constructors
	// =================================================================================================================
	UPF2SimpleDamageExecution();

	// =================================================================================================================
	// Public Methods - UGameplayEffectExecutionCalculation Implementation
	// =================================================================================================================
	virtual void Execute_Implementation(
		const FGameplayEffectCustomExecutionParameters& ExecutionParams,
		FGameplayEffectCustomExecutionOutput&           OutExecutionOutput) const override;

};

// OpenPF2 for UE Game Logic, Copyright 2021, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#pragma once

#include "GameplayEffectExecutionCalculation.h"
#include "PF2AbilityBoostExecution.generated.h"

/**
 * A GE execution that boosts a character ability.
 *
 * This execution can only be invoked by a GE that is a sub-class of UPF2AbilityBoostGameplayEffect, since this
 * execution gets context from the GE itself.
 */
UCLASS()
class UPF2AbilityBoostExecution : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()

public:
	/**
	 * Constructor for UPF2AbilityBoostExecution.
	 */
	UPF2AbilityBoostExecution();

	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	                                    OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;

protected:
	/**
	 * Performs the calculations involved in boosting a character ability and the ability boost counter.
	 *
	 * @param ExecutionParams
	 *   The parameters being passed-in to the execution from the GAS.
	 * @param TargetAttribute
	 *   The RPG attribute that is being boosted.
	 * @param OutExecutionOutput
	 *   The output of the calculation.
	 */
	void DoCalculation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
					   const FGameplayAttribute& TargetAttribute,
					   OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const;

	/**
	 * Calculates the boost for a character ability.
	 *
	 * @param BaseAbilityScore
	 *   The current value of the ability, before boosting.
	 *
	 * @return
	 *   The calculated amount of the boost.
	 */
	static float CalculateBoost(float BaseAbilityScore);
};

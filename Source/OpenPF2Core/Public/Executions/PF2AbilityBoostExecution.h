// OpenPF2 for UE Game Logic, Copyright 2021, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#pragma once

#include "GameplayEffectExecutionCalculation.h"
#include "PF2AbilityBoostExecution.generated.h"

/**
 * A Gameplay Effect Execution Calculation (GEX) that boosts a character ability.
 *
 * Ability boosts are available via both an Modifier Magnitude Calculation (MMC) and a GEX. Prefer this GEX variation
 * whenever possible, as it automatically increments the count of how many boosts are applied. The MMC variant should be
 * used only when an ability needs to be boosted in response to changes in tags on the source or target.
 */
UCLASS(Abstract, HideCategories=(Attributes))
class UPF2AbilityBoostExecution : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()

public:
	/** The attribute of the ability to boost. */
	UPROPERTY(EditDefaultsOnly, Category=TargetAbility)
	FGameplayAttribute TargetAbilityAttribute;

	/**
	 * Constructor for UPF2AbilityBoostExecution.
	 */
	UPF2AbilityBoostExecution();

	/**
	 * Invokes the calculation of this execution.
	 */
	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	                                    OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;

protected:
	/**
	 * Gets the attribute for the ability that is being boosted.
	 *
	 * @return
	 *   The RPG attribute for the boosted ability.
	 */
	const FGameplayAttribute& GetTargetAbilityAttribute() const
	{
		return TargetAbilityAttribute;
	}

	/**
	 * Gets the attribute capture definition for the target ability.
	 *
	 * @return
	 *   The capture definition for the attribute of the boosted ability.
	 */
	const FGameplayEffectAttributeCaptureDefinition* GetTargetCaptureDefinition() const;

	/**
	 * Performs the calculations involved in boosting a character ability and the ability boost counter.
	 *
	 * @param ExecutionParams
	 *   The parameters being passed-in to the execution from the GAS.
	 * @param TargetCapture
	 *   The capture specification for the target attribute.
	 * @param OutExecutionOutput
	 *   The output of the calculation.
	 */
	void DoCalculation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
					   const FGameplayEffectAttributeCaptureDefinition TargetCapture,
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

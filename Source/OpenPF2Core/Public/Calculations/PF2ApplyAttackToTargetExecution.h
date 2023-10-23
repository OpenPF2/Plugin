// OpenPF2 for UE Game Logic, Copyright 2023, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#pragma once

#include <GameplayEffectExecutionCalculation.h>

#include "PF2ApplyAttackToTargetExecution.generated.h"

/**
 * A gameplay effect execution for applying the output of an attack to a target.
 *
 * The output of an attack is represented as transient attack statistics on the attack attribute set.
 */
UCLASS()
class OPENPF2CORE_API UPF2ApplyAttackToTargetExecution : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()

public:
	// =================================================================================================================
	// Constructors
	// =================================================================================================================
	/**
	 * Default constructor.
	 */
	explicit UPF2ApplyAttackToTargetExecution();

	// =================================================================================================================
	// Public Methods - UGameplayEffectExecutionCalculation Implementation
	// =================================================================================================================
	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	                                    OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
};

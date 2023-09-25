// OpenPF2 for UE Game Logic, Copyright 2023, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#pragma once

#include <GameplayEffectExecutionCalculation.h>

#include "PF2WeaponDamageExecution.generated.h"

/**
 * Damage execution calculation for applying damage from a weapon.
 */
UCLASS()
// ReSharper disable once CppClassCanBeFinal
class OPENPF2CORE_API UPF2WeaponDamageExecution : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()

public:
	// =================================================================================================================
	// UGameplayEffectExecutionCalculation Implementation
	// =================================================================================================================
	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	                                    OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;

};

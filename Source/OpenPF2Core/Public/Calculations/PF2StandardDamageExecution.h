// OpenPF2 for UE Game Logic, Copyright 2021-2022, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#pragma once

#include <GameplayEffectExecutionCalculation.h>

#include "PF2StandardDamageExecution.generated.h"

/**
 * Damage execution calculation for applying damage and resistance logic according to standard PF2 rules.
 */
UCLASS()
// ReSharper disable once CppClassCanBeFinal
class OPENPF2CORE_API UPF2StandardDamageExecution : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()

protected:
	// =================================================================================================================
	// Protected Constants
	// =================================================================================================================
	/**
	 * Name of the tag that is used to pass a dynamic damage amount into the calculation.
	 */
	const FName DamageParameterTagName = "GameplayEffect.Parameter.Damage";

	/**
	 * Name of the tag that is used to pass a dynamic resistance amount into the calculation.
	 */
	const FName ResistanceParameterTagName = "GameplayEffect.Parameter.Resistance";

	// =================================================================================================================
	// Protected Fields
	// =================================================================================================================
	/**
	 * The tag for the parameter that is used to pass a dynamic damage amount into the calculation.
	 *
	 * The parameter is typically read from a set-by-caller tag-based value so that GAs can populate damage dynamically,
	 * unless the GE is expected to hard-code a specific amount of damage or reading it from a data table.
	 */
	FGameplayTag DamageParameterTag;

	/**
	 * The tag that is used to pass a dynamic damage amount into the calculation.
	 *
	 * The parameter should be provided via an attribute-based modifier that reads it from the appropriate resistance
	 * attribute of the character's attribute set (e.g., typically an attribute having a name that starts with "Rst",
	 * such as "RstPhysicalBludgeoning", "RstEnergyCold", etc.).
	 */
	FGameplayTag ResistanceParameterTag;

public:
	// =================================================================================================================
	// Constructors
	// =================================================================================================================
	UPF2StandardDamageExecution();

	// =================================================================================================================
	// UGameplayEffectExecutionCalculation Implementation
	// =================================================================================================================
	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
										OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;

};

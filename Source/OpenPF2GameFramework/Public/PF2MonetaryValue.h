// OpenPF2 for UE Game Logic, Copyright 2021-2024, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#pragma once

#include "GameplayTagContainer.h"

#include "Utilities/PF2GameplayAbilityUtilities.h"

#include "PF2MonetaryValue.generated.h"

/**
 * Representation of the cost or value of an item.
 */
USTRUCT(Blueprintable)
struct FPF2MonetaryValue
{
	GENERATED_BODY()

	/**
	 * The amount of this value relative to its monetary system.
	 */
	UPROPERTY(EditAnywhere)
	float Amount;

	/**
	 * The unit of currency that this value is relative to.
	 */
	UPROPERTY(EditAnywhere, meta=(Categories="CurrencyUnit"))
	FGameplayTag MonetaryUnit;

	/**
	 * Default constructor for PF2MonetaryValues.
	 */
	FPF2MonetaryValue() : Amount(0)
	{
	}

	/**
	 * Constructor for PF2MonetaryValues that allows initialization of amount and unit.
	 *
	 * @param Amount
	 *	The amount of this value relative to its monetary system.
	 * @param MonetaryUnit
	 *	The unit of currency that this value is relative to.
	 */
	FPF2MonetaryValue(const float Amount, const FGameplayTag MonetaryUnit) : Amount(Amount), MonetaryUnit(MonetaryUnit)
	{
		checkf(
			PF2GameplayAbilityUtilities::HasTag(&MonetaryUnit.GetSingleTagContainer(), FName("CurrencyUnit")),
			TEXT("Monetary unit must be a CurrencyUnit tag.")
		);
	}
};

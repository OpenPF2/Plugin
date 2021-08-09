// OpenPF2 for UE Game Logic, Copyright 2021, Guy Elsmore-Paddock. All Rights Reserved.
//
// Content from Pathfinder 2nd Edition is licensed under the Open Game License (OGL) v1.0a, subject to the following:
//	 - Open Game License v 1.0a, Copyright 2000, Wizards of the Coast, Inc.
//	 - System Reference Document, Copyright 2000, Wizards of the Coast, Inc.
//	 - Pathfinder Core Rulebook (Second Edition), Copyright 2019, Paizo Inc.
// Except for material designated as Product Identity, the game mechanics and logic in this file are Open Game Content,
// as defined in the Open Game License version 1.0a, Section 1(d) (see accompanying LICENSE.TXT). No portion of this
// file other than the material designated as Open Game Content may be reproduced in any form without written
// permission.

#pragma once

#include <CoreMinimal.h>

#include "PF2AbilityCalculationBase.h"
#include "PF2AbilityBoostCalculation.generated.h"

/**
 * An MMC for adding points to an ability score.
 */
UCLASS()
class OPENPF2CORE_API UPF2AbilityBoostCalculation : public UPF2AbilityCalculationBase
{
	GENERATED_BODY()

	/**
	 * Calculates an ability boost.
	 *
	 * From the Pathfinder 2E Core Rulebook, page 20:
	 * "An ability boost normally increases an ability score’s value by 2. However, if the ability score to which you’re
	 * applying an ability boost is already 18 or higher, its value increases by only 1. At 1st level, a character can
	 * never have any ability score that’s higher than 18."
	 *
	 * @param AbilityAttribute
	 *	The type of ability score for which an ability boost is desired.
	 * @param AbilityScore
	 *	The current base value of the ability attribute.
	 *
	 * @return
	 *	The boost to apply to the ability score. (This is just the boost; the ability score has not been added to the
	 *	result).
	 */
	virtual float DoCalculation(const FGameplayAttribute AbilityAttribute, const float AbilityScore) const override;
};

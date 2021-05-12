// Teen Wolf RPG game logic, Copyright 2021, Teen Wolf RPG. All Rights Reserved.
// Content from Pathfinder 2nd Edition is licensed under the Open Game License (OGL) v1.0a, subject to the following:
//	 - Open Game License v 1.0a, Copyright 2000, Wizards of the Coast, Inc.
//	 - System Reference Document, Copyright 2000, Wizards of the Coast, Inc.
//	 - Pathfinder Core Rulebook (Second Edition), Copyright 2019, Paizo Inc.
// Except for material designated as Product Identity or External Tools, the game mechanics of this Teen Wolf RPG
// product are Open Game Content, as defined in the Open Game License version 1.0a, Section 1(d) (see accompanying
// LICENSE.TXT). No portion of this work other than the material designated as Open Game Content may be reproduced in
// any form without written permission.

#pragma once

#include <CoreMinimal.h>

#include "RPGAbilityCalculationBase.h"
#include "RPGAbilityBoostCalculation.generated.h"

/**
 * An MMC for adding points to an ability score.
 */
UCLASS()
class TEENWOLFRPG_API URPGAbilityBoostCalculation : public URPGAbilityCalculationBase
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
	 *   The type of ability score for which an ability boost is desired.
	 * @param AbilityScore
	 *   The current base value of the ability attribute.
	 *
	 * @return
	 *   The boost to apply to the ability score. (This is just the boost; the ability score has not been added to the
	 *   result).
	 */
	virtual float DoCalculation(const FGameplayAttribute AbilityAttribute, const float AbilityScore) const override;
};

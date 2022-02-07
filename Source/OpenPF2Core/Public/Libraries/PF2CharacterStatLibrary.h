// OpenPF2 for UE Game Logic, Copyright 2021-2022, Guy Elsmore-Paddock. All Rights Reserved.
//
// Content from Pathfinder 2nd Edition is licensed under the Open Game License (OGL) v1.0a, subject to the following:
//   - Open Game License v 1.0a, Copyright 2000, Wizards of the Coast, Inc.
//   - System Reference Document, Copyright 2000, Wizards of the Coast, Inc.
//   - Pathfinder Core Rulebook (Second Edition), Copyright 2019, Paizo Inc.
//
// Except for material designated as Product Identity, the game mechanics and logic in this file are Open Game Content,
// as defined in the Open Game License version 1.0a, Section 1(d) (see accompanying LICENSE.TXT). No portion of this
// file other than the material designated as Open Game Content may be reproduced in any form without written
// permission.

#pragma once

#include <Kismet/BlueprintFunctionLibrary.h>

#include "PF2CharacterStatLibrary.generated.h"

/**
 * Function library for standard PF2 character statistic calculations.
 */
UCLASS()
class UPF2CharacterStatLibrary final : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/**
	 * Calculates the modifier for an ability score value.
	 *
	 * According to "Table 1-1: Ability Modifiers" in the Pathfinder 2E Core Rulebook, the ability modifier for an
	 * ability is equal to:
	 *
	 * Floor(Score / 2) - 5
	 *
	 * So:
	 *  1 => -5
	 *  2 => -4
	 *  3 => -4
	 * 10 =>  0
	 * 11 =>  0
	 * 24 => +7
	 * 25 => +7
	 *
	 * ... and so on.
	 *
	 * @param AbilityScore
	 *	The value of the ability attribute.
	 *
	 * @return
	 *	The modifier value for the ability.
	 */
	UFUNCTION(BlueprintPure, Category="OpenPF2|Character Stats")
	static float CalculateAbilityModifier(const float AbilityScore);

	/**
	 * Calculates how much the specified number of ability boosts adds to an ability with the given ability score value.
	 *
	 * From the Pathfinder 2E Core Rulebook, page 68, "Ability Boosts":
	 * "Boosting an ability score increases it by 1 if it's already 18 or above, or by 2 if it starts out below 18."
	 *
	 * For example:
	 * - If the starting ability score value is 10, and 5 boosts are getting applied, the result would be:
	 *   2 + 2 + 2 + 2 + 1 = 9, for an ending ability score value of 19.
	 * - If the starting ability score value is 18, and 1 boost is getting applied, the result would be 1.
	 *
	 * @param StartingAbilityScoreValue
	 *	The score of the ability score that is being boosted before the boost is being applied.
	 * @param BoostCount
	 *	An optional parameter for controlling how many boosts are being applied. If not specified, the default is only a
	 *	single boost.
	 *
	 * @return
	 *	The amount of the boost to apply to the ability score. (This is just the boost amount; the starting ability
	 *	score value is not added to the result).
	 */
	UFUNCTION(BlueprintPure, Category="OpenPF2|Character Stats")
	static float CalculateAbilityBoostAmount(const float StartingAbilityScoreValue, const int BoostCount = 1);

	/**
	 * Calculates how many ancestry feats a character is entitled to have at their current level.
	 *
	 * @param CharacterLevel
	 *	The character's current level.
	 *
	 * @return
	 *	The number of ancestry feats the character is entitled to have at their level.
	 */
	UFUNCTION(BlueprintPure, Category="OpenPF2|Character Stats")
	static float CalculateAncestryFeatCap(const float CharacterLevel);
};

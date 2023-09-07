// OpenPF2 for UE Game Logic, Copyright 2023, Guy Elsmore-Paddock. All Rights Reserved.
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

#include "PF2AttackStatLibrary.generated.h"

/**
 * Function library for standard OpenPF2 attack statistic calculations.
 */
UCLASS()
class UPF2AttackStatLibrary final : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

protected:
	/**
	 * The maximum multiple of the range of a ranged weapon within which the weapon still has a chance to hit a target.
	 *
	 * From the Pathfinder 2E Core Rulebook, page 279, "Range":
	 * "Attacks beyond the sixth range increment are impossible."
	 */
	static constexpr float MaxRangeIncrement = 6.0f;

	/**
	 * The amount of additional penalty to add to ranged attack rolls for each additional increment of the weapon range.
	 */
	static constexpr float RangePenaltyPerIncrement = -2.0f;

	/**
	 * The maximum range penalty a ranged weapon can have while still having a chance to hit a target.
	 *
	 * We subtract 1.0 because the range penalty starts at 0 for all distances less than the range increment of the
	 * weapon.
	 */
	static constexpr float MaxRangePenalty = (MaxRangeIncrement - 1.0f) * RangePenaltyPerIncrement;

public:
	/**
	 * Calculates the penalty at the specified distance from a target for a weapon that has the given range increment.
	 *
	 * From the Pathfinder 2E Core Rulebook, page 279, "Range":
	 * "Ranged and thrown weapons have a range increment. Attacks with these weapons work normally up to that distance.
	 * Attack rolls beyond a weapon’s range increment take a –2 penalty for each additional multiple of that increment
	 * between you and the target. Attacks beyond the sixth range increment are impossible."
	 *
	 * From the Pathfinder 2E Core Rulebook, page 446, "Range":
	 * "Ranged and thrown weapons each have a listed range increment, and attacks with them grow less accurate against
	 * targets farther away [...] As long as your target is at or within the listed range increment, also called the
	 * first range increment, you take no penalty to the attack roll. If you’re attacking beyond that range increment,
	 * you take a –2 penalty for each additional increment beyond the first. You can attempt to attack with a ranged
	 * weapon or thrown weapon up to six range increments away, but the farther away you are, the harder it is to hit
	 * your target."
	 *
	 * @param WeaponRangeIncrementCentimeters
	 *	The range increment (in centimeters) of the ranged or thrown weapon. This is the distance up to which a ranged
	 *	weapon works "normally"
	 * @param DistanceCentimeters
	 *	The distance (in centimeters) to the target.
	 *
	 * @return
	 *	The range increment penalty for the given range.
	 */
	UFUNCTION(BlueprintPure, Category="OpenPF2|Attack Stats")
	static float CalculateRangePenalty(
		UPARAM(DisplayName="Weapon Range Increment (cm)")
		const float WeaponRangeIncrementCentimeters,

		UPARAM(DisplayName="Distance (cm)")
		const float DistanceCentimeters);

	/**
	 * Calculates the maximum range of a weapon that has the given range increment.
	 *
	 * From the Pathfinder 2E Core Rulebook, page 279, "Range":
	 * "Ranged and thrown weapons have a range increment. Attacks with these weapons work normally up to that distance.
	 * Attack rolls beyond a weapon’s range increment take a –2 penalty for each additional multiple of that increment
	 * between you and the target. Attacks beyond the sixth range increment are impossible."
	 *
	 * From the Pathfinder 2E Core Rulebook, page 446, "Range":
	 * "Ranged and thrown weapons each have a listed range increment, and attacks with them grow less accurate against
	 * targets farther away [...] As long as your target is at or within the listed range increment, also called the
	 * first range increment, you take no penalty to the attack roll. If you’re attacking beyond that range increment,
	 * you take a –2 penalty for each additional increment beyond the first. You can attempt to attack with a ranged
	 * weapon or thrown weapon up to six range increments away, but the farther away you are, the harder it is to hit
	 * your target."
	 *
	 * @param WeaponRangeIncrementCentimeters
	 *	The range increment (in centimeters) of the ranged or thrown weapon. This is the distance up to which a ranged
	 *	weapon works "normally"
	 *
	 * @return
	 *	The maximum range (in centimeters) of a weapon with the given range increment.
	 */
	UFUNCTION(BlueprintPure, Category="OpenPF2|Attack Stats")
	static float CalculateMaximumRange(
		UPARAM(DisplayName="Weapon Range Increment (cm)")
		const float WeaponRangeIncrementCentimeters);

	/**
	 * Determines if the specified distance is within range of the weapon having the given range increment.
	 *
	 * From the Pathfinder 2E Core Rulebook, page 279, "Range":
	 * "Ranged and thrown weapons have a range increment. Attacks with these weapons work normally up to that distance.
	 * Attack rolls beyond a weapon’s range increment take a –2 penalty for each additional multiple of that increment
	 * between you and the target. Attacks beyond the sixth range increment are impossible."
	 *
	 * From the Pathfinder 2E Core Rulebook, page 446, "Range":
	 * "Ranged and thrown weapons each have a listed range increment, and attacks with them grow less accurate against
	 * targets farther away [...] As long as your target is at or within the listed range increment, also called the
	 * first range increment, you take no penalty to the attack roll. If you’re attacking beyond that range increment,
	 * you take a –2 penalty for each additional increment beyond the first. You can attempt to attack with a ranged
	 * weapon or thrown weapon up to six range increments away, but the farther away you are, the harder it is to hit
	 * your target."
	 *
	 * @param WeaponRangeIncrementCentimeters
	 *	The range increment of the ranged or thrown weapon.
	 * @param DistanceCentimeters
	 *	The distance to the target.
	 *
	 * @return
	 *	Whether the specified distance is within range of the weapon.
	 */
	UFUNCTION(BlueprintPure, Category="OpenPF2|Attack Stats")
	static bool IsWithinRange(
		UPARAM(DisplayName="Weapon Range Increment (cm)")
		const float WeaponRangeIncrementCentimeters,

		UPARAM(DisplayName="Distance (cm)")
		const float DistanceCentimeters);
};

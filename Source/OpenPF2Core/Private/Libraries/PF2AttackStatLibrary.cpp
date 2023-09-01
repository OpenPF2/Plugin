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

#include "Libraries/PF2AttackStatLibrary.h"

float UPF2AttackStatLibrary::CalculateRangePenalty(const float WeaponRangeIncrement, const float Distance)
{
	// From the Pathfinder 2E Core Rulebook, page 279, "Range":
	// "Ranged and thrown weapons have a range increment. Attacks with these weapons work normally up to that distance.
	// Attack rolls beyond a weapon’s range increment take a –2 penalty for each additional multiple of that increment
	// between you and the target."
	//
	// From the Pathfinder 2E Core Rulebook, page 446, "Range":
	// "Ranged and thrown weapons each have a listed range increment, and attacks with them grow less accurate against
	// targets farther away [...] As long as your target is at or within the listed range increment, also called the
	// first range increment, you take no penalty to the attack roll. If you’re attacking beyond that range increment,
	// you take a –2 penalty for each additional increment beyond the first. You can attempt to attack with a ranged
	// weapon or thrown weapon up to six range increments away, but the farther away you are, the harder it is to hit
	// your target."
	float Penalty =
		FMath::Max(0, FMath::FloorToFloat((Distance - 1.0f) / WeaponRangeIncrement)) * RangePenaltyIncrement;

	// These are both negative values, so "less than" is equivalent to "greater than" for positive values.
	if (Penalty < MaxRangePenalty)
	{
		Penalty = -UE_MAX_FLT;
	}

	return Penalty;
}

float UPF2AttackStatLibrary::CalculateMaximumRange(const float WeaponRangeIncrement)
{
	return WeaponRangeIncrement * MaxRangeIncrement;
}

bool UPF2AttackStatLibrary::IsWithinRange(const float WeaponRangeIncrement, const float Distance)
{
	return Distance <= CalculateMaximumRange(WeaponRangeIncrement);
}

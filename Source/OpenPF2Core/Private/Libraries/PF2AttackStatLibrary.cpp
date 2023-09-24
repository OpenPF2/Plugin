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

#include "Calculations/PF2TemlCalculation.h"

#include "Libraries/PF2DiceLibrary.h"

float UPF2AttackStatLibrary::CalculateAttackRoll(const int32                  CharacterLevel,
                                                 const FGameplayTagContainer& CharacterTags,
                                                 const float                  AttackAbilityModifier,
                                                 const FGameplayTagContainer& ProficiencyTagPrefixes)
{
	// "When making an attack roll, determine the result by rolling 1d20 and adding your attack modifier for the weapon
	// or unarmed attack you’re using."
	//
	// Source: Pathfinder 2E Core Rulebook, Chapter 6, page 278, "Attack Rolls".
	const int32 RollResult = UPF2DiceLibrary::RollSum(1, 20);

	float WeaponProficiencyBonus = 0;

	for (const FGameplayTag& ProficiencyTagPrefix : ProficiencyTagPrefixes)
	{
		FPF2TemlCalculation Calculation(ProficiencyTagPrefix, &CharacterTags, CharacterLevel);

		WeaponProficiencyBonus = FMath::Max(WeaponProficiencyBonus, Calculation.GetValue());
	}

	// Melee attack modifier = Strength modifier (or optionally Dexterity for a finesse weapon) + proficiency bonus +
	// other bonuses + penalties
	//
	// Ranged attack modifier = Dexterity modifier + proficiency bonus + other bonuses + penalties
	//
	// Source: Pathfinder 2E Core Rulebook, Chapter 6, page 278, "Attack Rolls".
	return RollResult + AttackAbilityModifier + WeaponProficiencyBonus;
}

float UPF2AttackStatLibrary::CalculateDamageRoll(const FName DamageDie, const float DamageAbilityModifier)
{
	const int32 RollResult = UPF2DiceLibrary::RollStringSum(DamageDie);

	// Melee damage roll  = damage die of weapon or unarmed attack + Strength modifier + bonuses + penalties
	// Ranged damage roll = damage die of weapon + Strength modifier for thrown weapons + bonuses + penalties
	//
	// Source: Pathfinder 2E Core Rulebook, Chapter 6, page 278, "Damage Rolls".
	return RollResult + DamageAbilityModifier;
}

float UPF2AttackStatLibrary::CalculateRangePenalty(const float WeaponRangeIncrementCentimeters,
                                                   const float DistanceCentimeters)
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
	const float RangeIncrement =
		FMath::Max(0, FMath::FloorToFloat((DistanceCentimeters - 1.0f) / WeaponRangeIncrementCentimeters));

	float Penalty = RangeIncrement * RangePenaltyPerIncrement;

	// These are both negative values, so "less than" is equivalent to "greater than" for positive values.
	if (Penalty < MaxRangePenalty)
	{
		Penalty = -UE_MAX_FLT;
	}

	return Penalty;
}

float UPF2AttackStatLibrary::CalculateMaximumRange(const float WeaponRangeIncrementCentimeters)
{
	return WeaponRangeIncrementCentimeters * MaxRangeIncrement;
}

bool UPF2AttackStatLibrary::IsWithinRange(const float WeaponRangeIncrementCentimeters, const float DistanceCentimeters)
{
	const float MaximumRange = CalculateMaximumRange(WeaponRangeIncrementCentimeters);
	const bool  bInRange     = (DistanceCentimeters <= MaximumRange);

	UE_LOG(
		LogPf2CoreAbilities,
		VeryVerbose,
		TEXT("IsWithinRange(%f,%f): %s (Max Range = %f)"),
		WeaponRangeIncrementCentimeters,
		DistanceCentimeters,
		bInRange ? TEXT("true") : TEXT("false"),
		MaximumRange
	);

	return bInRange;
}

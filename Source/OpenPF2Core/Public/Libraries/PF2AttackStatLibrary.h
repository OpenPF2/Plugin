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

#include <GameplayTagContainer.h>

#include <Kismet/BlueprintFunctionLibrary.h>

#include "Calculations/PF2CheckResult.h"

#include "PF2AttackStatLibrary.generated.h"

/**
 * Function library for standard OpenPF2 attack statistic and distance calculations.
 */
UCLASS()
class UPF2AttackStatLibrary final : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

protected:
	/**
	 * The default maximum distance (in centimeters) at which movement to a location is considered acceptable.
	 *
	 * For example, if Character A is moving into range of Character B to make a melee attack on Character B, and the
	 * reach of Character A is 1.5 meters (the standard distance for reach in OpenPF2), then Character A and Character B
	 * must be no further than 3.5 meters away from each other (reach + acceptance radius => 1.5 meters + 2.0 meters)
	 * for the attack to proceed.
	 */
	static constexpr float DefaultMovementAcceptanceRadiusCentimeters = 2.0f;

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
	 * Gets the default maximum distance (in centimeters) at which movement to a location is considered acceptable.
	 *
	 * @return
	 *	The default acceptance radius, in centimeters.
	 */
	UFUNCTION(BlueprintPure, Category="OpenPF2|Attack Stats")
	static UPARAM(DisplayName="Acceptance radius (cm)") FORCEINLINE float GetDefaultMovementAcceptanceRadius()
	{
		return DefaultMovementAcceptanceRadiusCentimeters;
	}

	/**
	 * Calculates the attack roll, which determines if an attack was successful (it hit its target).
	 *
	 * "When making an attack roll, determine the result by rolling 1d20 and adding your attack modifier for the weapon
	 * or unarmed attack you’re using. Modifiers for melee and ranged attacks are calculated differently.
	 *
	 * Melee attack modifier = Strength modifier (or optionally Dexterity for a finesse weapon) + proficiency bonus +
	 * other bonuses + penalties
	 * Ranged attack modifier = Dexterity modifier + proficiency bonus + other bonuses + penalties
	 *
	 * Bonuses, and penalties apply to these rolls just like with other types of checks. Weapons with potency runes add
	 * an item bonus to your attack rolls."
	 *
	 * Source: Pathfinder 2E Core Rulebook, Chapter 6, page 278, "Attack Rolls".
	 *
	 * @see EPF2CheckResult
	 *
	 * @param CharacterLevel
	 *	The level of the character.
	 * @param CharacterTags
	 *	The tags applied to the character.
	 * @param AttackAbilityModifier
	 *	The value of the character ability modifier to add to *attack* rolls, based on the type of weapon being used:
	 *	- For melee:
	 *	  - Regular weapons: the value of the "Strength" modifier.
	 *	  - Finesse weapons: the value of the "Dexterity" modifier.
	 *	- For ranged: the value of the the "Dexterity" modifier.
	 * @param MultipleAttackPenalty
	 *	The penalty to apply for attempting multiple attacks during the same turn. This should be a negative number.
	 * @param ProficiencyTagPrefixes
	 *	The root/parent tag of each set of tags that represent a character's TEML proficiencies with the weapon.
	 * @param TargetArmorClass
	 *	The armor class of the attack target. This represents the difficulty class to check against the attack roll.
	 */
	UFUNCTION(BlueprintPure, Category="OpenPF2|Attack Stats")
	static EPF2CheckResult PerformAttackRoll(const int32                  CharacterLevel,
	                                         const FGameplayTagContainer& CharacterTags,
	                                         const float                  AttackAbilityModifier,
	                                         const float                  MultipleAttackPenalty,
	                                         const FGameplayTagContainer& ProficiencyTagPrefixes,
	                                         const float                  TargetArmorClass);

	/**
	 * Performs a check of a value against a Difficulty Class (DC).
	 *
	 * @see EPF2CheckResult
	 *
	 * @param Value
	 *	The value to check.
	 * @param DifficultyClass
	 *	The difficulty class to check the value against.
	 *
	 * @return
	 *	The result of the check.
	 */
	UFUNCTION(BlueprintPure, Category="OpenPF2|Attack Stats")
	static EPF2CheckResult CheckAgainstDifficultyClass(const float Value, const float DifficultyClass);

	/**
	 * Upgrades a check result to one degree of success better, up to a maximum of "critical success".
	 *
	 * @param CheckResult
	 *	The check result to upgrade.
	 *
	 * @return
	 *	Either:
	 *	  - If CheckResult is not EPF2CheckResult::CriticalSuccess: The next-highest check result value.
	 *	  - If CheckResult is EPF2CheckResult::CriticalSuccess: No change (EPF2CheckResult::CriticalSuccess).
	 */
	UFUNCTION(BlueprintPure, Category="OpenPF2|Attack Stats")
	static FORCEINLINE EPF2CheckResult IncreaseDegreeOfSuccess(const EPF2CheckResult CheckResult)
	{
		const int32 MaxCheckResult   = static_cast<int32>(EPF2CheckResult::CriticalSuccess),
		            CheckResultValue = FMath::Min(static_cast<int32>(CheckResult) + 1, MaxCheckResult);

		return static_cast<EPF2CheckResult>(CheckResultValue);
	}

	/**
	 * Downgrades a check result to one degree of success worse, down to a minimum of "critical failure".
	 *
	 * @param CheckResult
	 *	The check result to upgrade.
	 *
	 * @return
	 *	Either:
	 *	  - If CheckResult is not EPF2CheckResult::CriticalFailure: The next-lowest check result value.
	 *	  - If CheckResult is EPF2CheckResult::CriticalFailure: No change (EPF2CheckResult::CriticalFailure).
	 */
	static FORCEINLINE EPF2CheckResult DecreaseDegreeOfSuccess(const EPF2CheckResult CheckResult)
	{
		const int32 MinCheckResult   = static_cast<int32>(EPF2CheckResult::CriticalFailure),
					CheckResultValue = FMath::Max(static_cast<int32>(CheckResult) - 1, MinCheckResult);

		return static_cast<EPF2CheckResult>(CheckResultValue);
	}

	/**
	 * Determines if the specified check result is a success or critical success.
	 *
	 * From the Pathfinder 2E Core Rulebook, Chapter 9, page 445, "Step 3: Compare the Result to the DC":
	 * "[...] if your result is equal to or greater than the DC, you succeed!"
	 *
	 * @param CheckResult
	 *	The result to check.
	 *
	 * @return
	 *	- true if the result represents a successful outcome (success or critical success).
	 *	- false if the result represents a failed outcome (failure or a critical failure/fumble).
	 */
	UFUNCTION(BlueprintPure, Category="OpenPF2|Attack Stats")
	static FORCEINLINE bool IsSuccess(const EPF2CheckResult CheckResult)
	{
		return ((CheckResult == EPF2CheckResult::Success) || (CheckResult == EPF2CheckResult::CriticalSuccess));
	}

	/**
	 * Determines if the specified check result is a failure or critical failure.
	 *
	 * From the Pathfinder 2E Core Rulebook, Chapter 9, page 445, "Step 3: Compare the Result to the DC":
	 * "If [you] roll anything less than the DC, you fail."
	 *
	 * @param CheckResult
	 *	The result to check.
	 *
	 * @return
	 *	- true if the result represents a failed outcome (failure or a critical failure/fumble).
	 *	- false if the result represents a successful outcome (success or critical success).
	 */
	UFUNCTION(BlueprintPure, Category="OpenPF2|Attack Stats")
	static FORCEINLINE bool IsFailure(const EPF2CheckResult CheckResult)
	{
		return ((CheckResult == EPF2CheckResult::Failure) || (CheckResult == EPF2CheckResult::CriticalFailure));
	}

	/**
	 * Calculates the damage roll, which determines how much of an effect an attack has on the target.
	 *
	 * "When the result of your attack roll with a weapon or unarmed attack equals or exceeds your target’s AC, you hit
	 * your target! Roll the weapon or unarmed attack’s damage die and add the relevant modifiers, bonuses, and
	 * penalties to determine the amount of damage you deal. Calculate a damage roll as follows.
	 *
	 * Melee damage roll  = damage die of weapon or unarmed attack + Strength modifier + bonuses + penalties
	 * Ranged damage roll = damage die of weapon + Strength modifier for thrown weapons + bonuses + penalties"
	 *
	 * Source: Pathfinder 2E Core Rulebook, Chapter 6, page 278, "Damage Rolls".
	 *
	 * @param DamageDie
	 *	The damage die of weapon or unarmed attack.
	 * @param DamageAbilityModifier
	 *	The modifier for the type of damage (e.g., Strength modifier or Strength modifier for thrown weapons).
	 */
	UFUNCTION(BlueprintPure, Category="OpenPF2|Attack Stats")
	static float CalculateDamageRoll(const FName DamageDie,
	                                 const float DamageAbilityModifier);

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

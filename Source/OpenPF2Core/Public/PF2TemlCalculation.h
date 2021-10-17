// OpenPF2 for UE Game Logic, Copyright 2021, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#pragma once

#include <CoreMinimal.h>
#include <GameplayModMagnitudeCalculation.h>

#include "GameplayEffectTypes.h"
#include "GameplayTagContainer.h"

/**
 * A single TEML proficiency calculation for a character attribute.
 *
 * TEML proficiency in an attribute is represented by a tag under a unique prefix for that attribute. For example, a
 * character with the "SavingThrow.Reflex.Trained" and "Perception.Master" tags has a "Trained" proficiency in reflex
 * saving throws and "Master" proficiency in Perception, with the "SavingThrow.Reflex" and "Perception" tag prefixes,
 * respectively.
 */
class OPENPF2CORE_API FPF2TemlCalculation
{
protected:
	/**
	 * The value that was calculated for this TEML proficiency.
	 */
	float Value;

public:
	/**
	 * Creates and calculates a character's TEML proficiency in a stat based on the given prefix/root tag.
	 *
	 * @param TagPrefix
	 *	The root/parent tag of tags that represent the TEML proficiency to examine; as a tag.
	 * @param Spec
	 *	The Gameplay Effect (GE) specification that provides information about the character and their proficiencies.
	 */
	FPF2TemlCalculation(const FGameplayTag TagPrefix, const FGameplayEffectSpec& Spec);

	/**
	 * Creates and calculates a character's TEML proficiency in a stat based on the given prefix/root tag.
	 *
	 * @param TagPrefix
	 *	The root/parent tag of tags that represent the TEML proficiency to examine; as a tag name.
	 * @param Spec
	 *	The Gameplay Effect (GE) specification that provides information about the character and their proficiencies.
	 */
	FPF2TemlCalculation(const FName TagPrefix, const FGameplayEffectSpec& Spec);

	/**
	 * Creates and calculates a character's TEML proficiency in a stat based on the given prefix/root tag.
	 *
	 * @param TagPrefix
	 *	The root/parent tag of tags that represent the TEML proficiency to examine; as a string.
	 * @param Spec
	 *	The Gameplay Effect (GE) specification that provides information about the character and their proficiencies.
	 */
	FPF2TemlCalculation(const FString TagPrefix, const FGameplayEffectSpec& Spec);

	/**
	 * Gets the calculated TEML proficiency.
	 *
	 * @return
	 *	The amount that the character's proficiency in a stat contributes to the modifier for the stat.
	 */
	float GetValue() const;
};

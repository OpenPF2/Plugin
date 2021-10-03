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
 * Utility logic for calculating TEML proficiencies for a character.
 *
 * FIXME: Make me a small object/class instead of a static utility class.
 */
namespace TemlCalculationUtils
{
	/**
	 * Calculates a character's TEML proficiency in a stat.
	 *
	 * A character's TEML proficiency is represented by a tag having the unique prefix of the appropriate stat.
	 *
	 * @param TagPrefix
	 *	The prefix of the TEML proficiency to examine; as tag.
	 *
	 * @param Spec
	 *	The Gameplay Effect (GE) specification that provides information about the character and their proficiencies.
	 *
	 * @return
	 *	The amount that the character's proficiency in a stat contributes to the modifier for the stat.
	 */
	static float CalculateProficiencyBonus(const FGameplayTag TagPrefix, const FGameplayEffectSpec& Spec);

	/**
	 * Calculates a character's TEML proficiency in a stat.
	 *
	 * A character's TEML proficiency is represented by a tag having the unique prefix of the appropriate stat.
	 *
	 * @param TagPrefix
	 *	The prefix of the TEML proficiency to examine; as a tag name.
	 *
	 * @param Spec
	 *	The Gameplay Effect (GE) specification that provides information about the character and their proficiencies.
	 *
	 * @return
	 *	The amount that the character's proficiency in a stat contributes to the modifier for the stat.
	 */
	static float CalculateProficiencyBonus(const FName TagPrefix, const FGameplayEffectSpec& Spec);

	/**
	 * Calculates a character's TEML proficiency in a stat.
	 *
	 * A character's TEML proficiency is represented by a tag having the unique prefix of the appropriate stat.
	 *
	 * @param TagPrefix
	 *	The prefix of the TEML proficiency to examine; as a string.
	 *
	 * @param Spec
	 *	The Gameplay Effect (GE) specification that provides information about the character and their proficiencies.
	 *
	 * @return
	 *	The amount that the character's proficiency in a stat contributes to the modifier for the stat.
	 */
	static float CalculateProficiencyBonus(const FString TagPrefix, const FGameplayEffectSpec& Spec);
}

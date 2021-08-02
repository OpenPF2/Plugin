// OpenPF2 for UE Game Logic, Copyright 2021, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#pragma once

#include <GameplayModMagnitudeCalculation.h>
#include <CoreMinimal.h>
#include "PF2TemlCalculationBase.generated.h"

/**
 * Base class for MMCs that rely on TEML (Trained, Expert, Master, Legendary) proficiency calculation.
 */
UCLASS(Abstract)
class TEENWOLFRPG_API UPF2TemlCalculationBase : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()

protected:
	/**
	 * Calculates the character's TEML proficiency in this stat.
	 *
	 * @param TagPrefix
	 *	The prefix of the TEML proficiency to examine; as tag.
	 *
	 * @param Spec
	 *	The Gameplay Effect (GE) specification that provides information about the character and their proficiencies.
	 */
	static float CalculateProficiencyBonus(const FGameplayTag TagPrefix, const FGameplayEffectSpec& Spec);

	/**
	 * Calculates the character's TEML proficiency in this stat.
	 *
	 * @param TagPrefix
	 *	The prefix of the TEML proficiency to examine; as a tag name.
	 *
	 * @param Spec
	 *	The Gameplay Effect (GE) specification that provides information about the character and their proficiencies.
	 */
	static float CalculateProficiencyBonus(const FName TagPrefix, const FGameplayEffectSpec& Spec);

	/**
	 * Calculates the character's TEML proficiency in this stat.
	 *
	 * @param TagPrefix
	 *	The prefix of the TEML proficiency to examine; as a string.
	 *
	 * @param Spec
	 *	The Gameplay Effect (GE) specification that provides information about the character and their proficiencies.
	 */
	static float CalculateProficiencyBonus(const FString TagPrefix, const FGameplayEffectSpec& Spec);
};

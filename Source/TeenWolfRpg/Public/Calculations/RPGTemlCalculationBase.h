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

#include <GameplayModMagnitudeCalculation.h>
#include <CoreMinimal.h>
#include "RPGTemlCalculationBase.generated.h"

/**
 * Base class for MMCs that rely on TEML (Trained, Expert, Master, Legendary) proficiency calculation.
 */
UCLASS(Abstract)
class TEENWOLFRPG_API URPGTemlCalculationBase : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()

protected:
	/**
	 * Calculates the character's TEML proficiency in this stat.
	 *
	 * @param TagPrefix
	 *   The prefix of the TEML proficiency to examine.
	 *
	 * @param Spec
	 *   The Gameplay Effect (GE) specification that provides information about the character and their proficiencies.
	 */
	float CalculateProficiencyBonus(const FString TagPrefix, const FGameplayEffectSpec& Spec) const;
};

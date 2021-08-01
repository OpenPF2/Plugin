// Teen Wolf RPG game logic, Copyright 2021, Teen Wolf RPG. All Rights Reserved.
// Content from Pathfinder 2nd Edition is licensed under the Open Game License (OGL) v1.0a, subject to the following:
//	 - Open Game License v 1.0a, Copyright 2000, Wizards of the Coast, Inc.
//	 - System Reference Document, Copyright 2000, Wizards of the Coast, Inc.
//	 - Pathfinder Core Rulebook (Second Edition), Copyright 2019, Paizo Inc.
// Except for material designated as Product Identity or External Tools, the game mechanics of this Teen Wolf RPG
// product are Open Game Content, as defined in the Open Game License version 1.0a, Section 1(d) (see accompanying
// LICENSE.TXT). No portion of this work other than the material designated as Open Game Content may be reproduced in
// any form without written permission.

#include "TeenWolfRpg.h"

#include "Abilities/RPGAttributeSet.h"
#include "Calculations/RPGAbilityBoostCalculation.h"

float URPGAbilityBoostCalculation::DoCalculation(const FGameplayAttribute AbilityAttribute,
												 const float AbilityScore) const
{
	float BoostedScore;

	// From the Pathfinder 2E Core Rulebook, page 68, "Ability Boosts":
	// "Boosting an ability score increases it by 1 if it's already 18 or above, or by 2 if it starts out below 18."
	if (AbilityScore < 18.0f)
	{
		BoostedScore = 2.0f;
	}
	else
	{
		BoostedScore = 1.0f;
	}

	UE_LOG(
		LogTwRpg,
		VeryVerbose,
		TEXT("Calculated boost for ability score attribute ('%s': %f): %f"),
		*(AbilityAttribute.GetName()),
		AbilityScore,
		BoostedScore
	);

	return BoostedScore;
}

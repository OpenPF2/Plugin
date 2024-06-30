// OpenPF2 Game Framework for Unreal Engine, Copyright 2021-2024, Guy Elsmore-Paddock. All Rights Reserved.
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

#include "Libraries/PF2CharacterStatLibrary.h"

float UPF2CharacterStatLibrary::CalculateAbilityModifier(const float AbilityScore)
{
	// Source: Pathfinder 2E Core Rulebook, page 20, Table 1-1: Ability Modifiers.
	return FMath::FloorToFloat(AbilityScore / 2.0f) - 5.0f;
}

float UPF2CharacterStatLibrary::CalculateAbilityBoostAmount(const float StartingAbilityScoreValue,
                                                            const int   BoostCount)
{
	float BoostAmount = 0.0f;

	for (int BoostIndex = 0; BoostIndex < BoostCount; ++BoostIndex)
	{
		// From the Pathfinder 2E Core Rulebook, page 68, "Ability Boosts":
		// "Boosting an ability score increases it by 1 if it's already 18 or above, or by 2 if it starts out below 18."
		if ((StartingAbilityScoreValue + BoostAmount) >= 18.0f)
		{
			BoostAmount += 1.0f;
		}
		else
		{
			BoostAmount += 2.0f;
		}
	}

	return BoostAmount;
}

float UPF2CharacterStatLibrary::CalculateAncestryFeatCap(const float CharacterLevel)
{
	// From the Pathfinder 2E Core Rulebook, pages 36, 40, 44, 48, 52, and 56:
	// "At 1st level, you gain one ancestry feat, and you gain an additional ancestry feat every 4 levels thereafter (at
	// 5th, 9th, 13th, and 17th level)."
	return 1.0f + FMath::FloorToFloat((CharacterLevel - 1.0f) / 4.0f);
}

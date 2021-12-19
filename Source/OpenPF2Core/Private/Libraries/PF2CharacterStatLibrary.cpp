// OpenPF2 for UE Game Logic, Copyright 2021, Guy Elsmore-Paddock. All Rights Reserved.
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

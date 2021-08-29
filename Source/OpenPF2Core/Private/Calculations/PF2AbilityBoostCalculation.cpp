// OpenPF2 for UE Game Logic, Copyright 2021, Guy Elsmore-Paddock. All Rights Reserved.
//
// Content from Pathfinder 2nd Edition is licensed under the Open Game License (OGL) v1.0a, subject to the following:
//	 - Open Game License v 1.0a, Copyright 2000, Wizards of the Coast, Inc.
//	 - System Reference Document, Copyright 2000, Wizards of the Coast, Inc.
//	 - Pathfinder Core Rulebook (Second Edition), Copyright 2019, Paizo Inc.
// Except for material designated as Product Identity, the game mechanics and logic in this file are Open Game Content,
// as defined in the Open Game License version 1.0a, Section 1(d) (see accompanying LICENSE.TXT). No portion of this
// file other than the material designated as Open Game Content may be reproduced in any form without written
// permission.

#include "Calculations/PF2AbilityBoostCalculation.h"

#include "OpenPF2Core.h"
#include "Abilities/PF2AttributeSet.h"

float UPF2AbilityBoostCalculation::DoCalculation(const FGameplayAttribute AbilityAttribute,
												 const float AbilityScore) const
{
	float Boost;

	// From the Pathfinder 2E Core Rulebook, page 68, "Ability Boosts":
	// "Boosting an ability score increases it by 1 if it's already 18 or above, or by 2 if it starts out below 18."
	if (AbilityScore < 18.0f)
	{
		Boost = 2.0f;
	}
	else
	{
		Boost = 1.0f;
	}

	UE_LOG(
		LogPf2Core,
		VeryVerbose,
		TEXT("Calculated MMC boost for ability score attribute ('%s'): %f + %f = %f"),
		*(AbilityAttribute.GetName()),
		AbilityScore,
		Boost,
		AbilityScore + Boost
	);

	return Boost;
}

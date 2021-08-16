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

#include "Calculations/PF2AncestryFeatCapCalculation.h"

float UPF2AncestryFeatCapCalculation::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	const float CharacterLevel = Spec.GetLevel();

	// From the Pathfinder 2E Core Rulebook, pages 36, 40, 44, 48, 52, and 56:
	// "At 1st level, you gain one ancestry feat, and you gain an additional ancestry feat every 4 levels thereafter (at
	// 5th, 9th, 13th, and 17th level)."
	return 1 + FMath::FloorToFloat(CharacterLevel / 4.0f);
}

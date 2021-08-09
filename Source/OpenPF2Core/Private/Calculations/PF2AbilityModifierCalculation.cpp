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

#include "Calculations/PF2AbilityModifierCalculation.h"

#include "OpenPF2Core.h"
#include "Abilities/PF2AttributeSet.h"

float UPF2AbilityModifierCalculation::DoCalculation(const FGameplayAttribute AbilityAttribute, float AbilityScore) const
{
	float AbilityModifier;

	// Source: Pathfinder 2E Core Rulebook, page 20, Table 1-1: Ability Modifiers.
	AbilityModifier = FMath::FloorToFloat(AbilityScore / 2.0f) - 5.0f;

	UE_LOG(
		LogPf2Core,
		VeryVerbose,
		TEXT("Calculated ability modifier for attribute ('%s': %f): %f"),
		*(AbilityAttribute.GetName()),
		AbilityScore,
		AbilityModifier
	);

	return AbilityModifier;
}

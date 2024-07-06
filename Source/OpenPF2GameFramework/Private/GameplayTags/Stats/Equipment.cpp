// OpenPF2 Game Framework for Unreal Engine, Copyright 2021-2024, Guy Elsmore-Paddock. All Rights Reserved.
//
// Content from Pathfinder 2nd Edition is licensed under the Open Game License (OGL) v1.0a, subject to the following:
//	- Open Game License v 1.0a, Copyright 2000, Wizards of the Coast, Inc.
//	- System Reference Document, Copyright 2000, Wizards of the Coast, Inc.
//	- Pathfinder Core Rulebook (Second Edition), Copyright 2019, Paizo Inc.
//
// Except for material designated as Product Identity, the game mechanics and logic in this file are Open Game Content,
// as defined in the Open Game License version 1.0a, Section 1(d) (see accompanying LICENSE.TXT). No portion of this
// file other than the material designated as Open Game Content may be reproduced in any form without written
// permission.

#include "GameplayTags/Stats/Equipment.h"

// =====================================================================================================================
// The types of item(s) the character *currently* has equipped.
// =====================================================================================================================
UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagEquipped,
	"PF2.Equipped",
	"The types of item(s) the character *currently* has equipped."
)

// =====================================================================================================================
// The type of armor the character *currently* has equipped.
// =====================================================================================================================
UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagEquippedArmor,
	"PF2.Equipped.Armor",
	"The types of armor the character can *currently* has equipped."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagEquippedArmorUnarmored,
	"PF2.Equipped.Armor.Unarmored",
	"Character has no armor equipped."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagEquippedArmorLight,
	"PF2.Equipped.Armor.Light",
	"Character has Light armor equipped."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagEquippedArmorMedium,
	"PF2.Equipped.Armor.Medium",
	"Character has Medium armor equipped."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagEquippedArmorHeavy,
	"PF2.Equipped.Armor.Heavy",
	"Character has Heavy armor equipped."
)

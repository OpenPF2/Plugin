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

#include "GameplayTags/Stats/CreatureSizes.h"

// =====================================================================================================================
// Creature Size - The approximate physical amount of space a creature occupies.
// =====================================================================================================================
// Source: Pathfinder 2E Core Rulebook, page 474, Table 9-1: Size and Reach.
UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagCreatureSizes,
	"PF2.CreatureSize",
	"The approximate physical amount of space a creature occupies."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagCreatureSizeTiny,
	"PF2.CreatureSize.Tiny",
	"The creature or character occupies less than 1.5 meters of space."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagCreatureSizeSmall,
	"PF2.CreatureSize.Small",
	"The creature or character occupies 1.5 meters of space and is slightly smaller than medium size."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagCreatureSizeMedium,
	"PF2.CreatureSize.Medium",
	"The creature or character occupies 1.5 meters of space and is slightly larger than small size."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagCreatureSizeLarge,
	"PF2.CreatureSize.Large",
	"The creature or character occupies 3.0 meters of space."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagCreatureSizeHuge,
	"PF2.CreatureSize.Huge",
	"The creature or character occupies 4.5 meters of space."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagCreatureSizeGargantuan,
	"PF2.CreatureSize.Gargantuan",
	"The creature or character occupies 6.0 or more meters of space."
)

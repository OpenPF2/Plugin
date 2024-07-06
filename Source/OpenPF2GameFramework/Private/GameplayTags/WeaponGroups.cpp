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

#include "GameplayTags/WeaponGroups.h"

// =====================================================================================================================
// Weapon Groups
// =====================================================================================================================
// From the Pathfinder 2E Core Rulebook, pages 280-282; Tables 6-6, 6-7, and 6-8.
UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeapons,
	"PF2.WeaponGroup",
	"The broad categories of weapons by shape and type of attack (ranged vs. melee)."
)

UE_DEFINE_GAMEPLAY_TAG(Pf2TagWeaponGroupAxe,      "PF2.WeaponGroup.Axe")
UE_DEFINE_GAMEPLAY_TAG(Pf2TagWeaponGroupBomb,     "PF2.WeaponGroup.Bomb")
UE_DEFINE_GAMEPLAY_TAG(Pf2TagWeaponGroupBow,      "PF2.WeaponGroup.Bow")
UE_DEFINE_GAMEPLAY_TAG(Pf2TagWeaponGroupBrawling, "PF2.WeaponGroup.Brawling")
UE_DEFINE_GAMEPLAY_TAG(Pf2TagWeaponGroupClub,     "PF2.WeaponGroup.Club")
UE_DEFINE_GAMEPLAY_TAG(Pf2TagWeaponGroupDart,     "PF2.WeaponGroup.Dart")
UE_DEFINE_GAMEPLAY_TAG(Pf2TagWeaponGroupFlail,    "PF2.WeaponGroup.Flail")
UE_DEFINE_GAMEPLAY_TAG(Pf2TagWeaponGroupHammer,   "PF2.WeaponGroup.Hammer")
UE_DEFINE_GAMEPLAY_TAG(Pf2TagWeaponGroupKnife,    "PF2.WeaponGroup.Knife")
UE_DEFINE_GAMEPLAY_TAG(Pf2TagWeaponGroupPick,     "PF2.WeaponGroup.Pick")
UE_DEFINE_GAMEPLAY_TAG(Pf2TagWeaponGroupPolearm,  "PF2.WeaponGroup.Polearm")
UE_DEFINE_GAMEPLAY_TAG(Pf2TagWeaponGroupShield,   "PF2.WeaponGroup.Shield")
UE_DEFINE_GAMEPLAY_TAG(Pf2TagWeaponGroupSling,    "PF2.WeaponGroup.Sling")
UE_DEFINE_GAMEPLAY_TAG(Pf2TagWeaponGroupSpear,    "PF2.WeaponGroup.Spear")
UE_DEFINE_GAMEPLAY_TAG(Pf2TagWeaponGroupSword,    "PF2.WeaponGroup.Sword")

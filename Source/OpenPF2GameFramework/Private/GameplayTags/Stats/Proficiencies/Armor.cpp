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

#include "GameplayTags/Stats/Proficiencies/Armor.h"

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyArmor,
	"PF2.Proficiency.Armor",
	"Character proficiency ranks for armor."
)

// =====================================================================================================================
// Proficiency Ranks for Different Classes of Armor (Unarmored, Light, Medium, or Heavy)
// =====================================================================================================================
// Sources:
//	- Pathfinder 2E Core Rulebook, Chapter 1: "Introduction", page 11, "Playing the Game".
//	- Pathfinder 2E Core Rulebook, Chapter 1: "Introduction", page 13, "Proficiency".
//	- Pathfinder 2E Core Rulebook, Chapter 1: "Introduction", page 27, "Character Sheet".
//	- Pathfinder 2E Core Rulebook, Appendix, page 624, "Armor Class".
UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyArmorCategory,
	"PF2.Proficiency.Armor.Category",
	"Character proficiency ranks for different categories of armor."
)

// === Unarmored
UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyArmorCategoryUnarmored,
	"PF2.Proficiency.Armor.Category.Unarmored",
	"Character proficiency ranks for Unarmored Defense."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyArmorCategoryUnarmoredUntrained,
	"PF2.Proficiency.Armor.Category.Unarmored.Untrained",
	"Character is Untrained in Unarmored Defense."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyArmorCategoryUnarmoredTrained,
	"PF2.Proficiency.Armor.Category.Unarmored.Trained",
	"Character is Trained in Unarmored Defense."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyArmorCategoryUnarmoredExpert,
	"PF2.Proficiency.Armor.Category.Unarmored.Expert",
	"Character is Expert in Unarmored Defense."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyArmorCategoryUnarmoredMaster,
	"PF2.Proficiency.Armor.Category.Unarmored.Master",
	"Character is Master in Unarmored Defense."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyArmorCategoryUnarmoredLegendary,
	"PF2.Proficiency.Armor.Category.Unarmored.Legendary",
	"Character is Legendary in Unarmored Defense."
)

// === Light
UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyArmorCategoryLight,
	"PF2.Proficiency.Armor.Category.Light",
	"Character proficiency ranks for Light Armor Defense."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyArmorCategoryLightUntrained,
	"PF2.Proficiency.Armor.Category.Light.Untrained",
	"Character is Untrained in Light Armor Defense."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyArmorCategoryLightTrained,
	"PF2.Proficiency.Armor.Category.Light.Trained",
	"Character is Trained in Light Armor Defense."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyArmorCategoryLightExpert,
	"PF2.Proficiency.Armor.Category.Light.Expert",
	"Character is Expert in Light Armor Defense."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyArmorCategoryLightMaster,
	"PF2.Proficiency.Armor.Category.Light.Master",
	"Character is Master in Light Armor Defense."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyArmorCategoryLightLegendary,
	"PF2.Proficiency.Armor.Category.Light.Legendary",
	"Character is Legendary in Light Armor Defense."
)

// === Medium
UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyArmorCategoryMedium,
	"PF2.Proficiency.Armor.Category.Medium",
	"Character proficiency ranks for Medium Armor Defense."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyArmorCategoryMediumUntrained,
	"PF2.Proficiency.Armor.Category.Medium.Untrained",
	"Character is Untrained in Medium Armor Defense."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyArmorCategoryMediumTrained,
	"PF2.Proficiency.Armor.Category.Medium.Trained",
	"Character is Trained in Medium Armor Defense."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyArmorCategoryMediumExpert,
	"PF2.Proficiency.Armor.Category.Medium.Expert",
	"Character is Expert in Medium Armor Defense."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyArmorCategoryMediumMaster,
	"PF2.Proficiency.Armor.Category.Medium.Master",
	"Character is Master in Medium Armor Defense."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyArmorCategoryMediumLegendary,
	"PF2.Proficiency.Armor.Category.Medium.Legendary",
	"Character is Legendary in Medium Armor Defense."
)

// === Heavy
UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyArmorCategoryHeavy,
	"PF2.Proficiency.Armor.Category.Heavy",
	"Character proficiency ranks for Heavy Armor Defense."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyArmorCategoryHeavyUntrained,
	"PF2.Proficiency.Armor.Category.Heavy.Untrained",
	"Character is Untrained in Heavy Armor Defense."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyArmorCategoryHeavyTrained,
	"PF2.Proficiency.Armor.Category.Heavy.Trained",
	"Character is Trained in Heavy Armor Defense."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyArmorCategoryHeavyExpert,
	"PF2.Proficiency.Armor.Category.Heavy.Expert",
	"Character is Expert in Heavy Armor Defense."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyArmorCategoryHeavyMaster,
	"PF2.Proficiency.Armor.Category.Heavy.Master",
	"Character is Master in Heavy Armor Defense."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyArmorCategoryHeavyLegendary,
	"PF2.Proficiency.Armor.Category.Heavy.Legendary",
	"Character is Legendary in Heavy Armor Defense."
)

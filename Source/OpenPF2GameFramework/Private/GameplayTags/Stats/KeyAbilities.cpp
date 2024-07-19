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

#include "GameplayTags/Stats/KeyAbilities.h"

// =====================================================================================================================
// Key Ability - The most important ability of a particular character/creature.
// =====================================================================================================================
// Sources:
//	- Pathfinder 2E Core Rulebook, Chapter 3: "Classes", page 68, "Key Ability".
//	- Pathfinder 2E Core Rulebook, Chapter 3: "Classes", pages 72-232 ("Key Ability" sections in each class entry).
//
UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagKeyAbilities,
	"PF2.KeyAbility",
	"The most important ability of a particular character/creature."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagKeyAbilityStrength,
	"PF2.KeyAbility.Strength",
	"Character's key ability is Strength."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagKeyAbilityDexterity,
	"PF2.KeyAbility.Dexterity",
	"Character's key ability is Dexterity."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagKeyAbilityConstitution,
	"PF2.KeyAbility.Constitution",
	"Character's key ability is Constitution."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagKeyAbilityIntelligence,
	"PF2.KeyAbility.Intelligence",
	"Character's key ability is Intelligence."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagKeyAbilityWisdom,
	"PF2.KeyAbility.Wisdom",
	"Character's key ability is Wisdom."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagKeyAbilityCharisma,
	"PF2.KeyAbility.Charisma",
	"Character's key ability is Charisma."
)

// =====================================================================================================================
// Spellcasting Ability - The key ability of a character/creature that can cast spells.
// =====================================================================================================================
// The classes in the core rulebook don't have any spellcasting abilities other than Wisdom and Charisma, but there's no
// reason to limit game makers to just those options. Plus, add-on material for OpenPF2 could always invent a new class
// that uses something like Intelligence for a character that does complex spellcasting or Dexterity for a character who
// performs physically-dexterous spells.
//
// Sources:
//	- Pathfinder 2E Core Rulebook, Chapter 3: "Classes", page 68, "Key Ability".
//	- Pathfinder 2E Core Rulebook, Chapter 3: "Classes", pages 72-232 ("Key Ability" sections in each class entry).
//
UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagSpellcastingAbilities,
	"PF2.SpellcastingAbility",
	"The key ability of a character/creature that can cast spells."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagSpellcastingAbilityStrength,
	"PF2.SpellcastingAbility.Strength",
	"Character's spellcasting ability is Strength."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagSpellcastingAbilityDexterity,
	"PF2.SpellcastingAbility.Dexterity",
	"Character's spellcasting ability is Dexterity."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagSpellcastingAbilityConstitution,
	"PF2.SpellcastingAbility.Constitution",
	"Character's spellcasting ability is Constitution."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagSpellcastingAbilityIntelligence,
	"PF2.SpellcastingAbility.Intelligence",
	"Character's spellcasting ability is Intelligence."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagSpellcastingAbilityWisdom,
	"PF2.SpellcastingAbility.Wisdom",
	"Character's spellcasting ability is Wisdom."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagSpellcastingAbilityCharisma,
	"PF2.SpellcastingAbility.Charisma",
	"Character's spellcasting ability is Charisma."
)

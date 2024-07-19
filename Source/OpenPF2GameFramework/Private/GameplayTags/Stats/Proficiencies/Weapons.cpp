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

#include "GameplayTags/Stats/Proficiencies/Weapons.h"

// =====================================================================================================================
// Proficiency Ranks for Weapons
// =====================================================================================================================
UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeapon,
	"PF2.Proficiency.Weapon",
	"Character proficiency ranks for weapons."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponCategory,
	"PF2.Proficiency.Weapon.Category",
	"Character proficiency ranks for broad categories of weapons."
)

// =====================================================================================================================
// Proficiency Ranks for Unarmed Attacks
// =====================================================================================================================
// Weapon type mentioned in Pathfinder 2E Core Rulebook under:
//	- Chapter 3, page 71, "Attacks" for "Alchemist"
//	- Chapter 3, page 83, "Attacks" for "Barbarian"
//	- Chapter 3, page 95, "Attacks" for "Bard"
//	- Chapter 3, page 105, "Attacks" for "Champion"
//	- Chapter 3, page 117, "Attacks" for "Cleric"
//	- Chapter 3, page 129, "Attacks" for "Druid"
//	- Chapter 3, page 141, "Attacks" for "Fighter"
//	- Chapter 3, page 155, "Attacks" for "Monk"
//	- Chapter 3, page 167, "Attacks" for "Ranger"
//	- Chapter 3, page 179, "Attacks" for "Rogue"
//	- Chapter 3, page 191, "Attacks" for "Sorcerer"
//	- Chapter 3, page 203, "Attacks" for "Wizard"
UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponCategoryUnarmed,
	"PF2.Proficiency.Weapon.Category.Unarmed",
	"Character proficiency ranks for Unarmed attacks."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponCategoryUnarmedUntrained,
	"PF2.Proficiency.Weapon.Category.Unarmed.Untrained",
	"Character is Untrained with Unarmed attacks."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponCategoryUnarmedTrained,
	"PF2.Proficiency.Weapon.Category.Unarmed.Trained",
	"Character is Trained with Unarmed attacks."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponCategoryUnarmedExpert,
	"PF2.Proficiency.Weapon.Category.Unarmed.Expert",
	"Character is Expert with Unarmed attacks."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponCategoryUnarmedMaster,
	"PF2.Proficiency.Weapon.Category.Unarmed.Master",
	"Character is Master with Unarmed attacks."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponCategoryUnarmedLegendary,
	"PF2.Proficiency.Weapon.Category.Unarmed.Legendary",
	"Character is Legendary with Unarmed attacks."
)

// =====================================================================================================================
// Proficiency Ranks for Simple Weapons
// =====================================================================================================================
// Weapon type mentioned in Pathfinder 2E Core Rulebook under:
//	- Chapter 3, page 71, "Attacks" for "Alchemist"
//	- Chapter 3, page 83, "Attacks" for "Barbarian"
//	- Chapter 3, page 95, "Attacks" for "Bard"
//	- Chapter 3, page 105, "Attacks" for "Champion"
//	- Chapter 3, page 117, "Attacks" for "Cleric"
//	- Chapter 3, page 129, "Attacks" for "Druid"
//	- Chapter 3, page 141, "Attacks" for "Fighter"
//	- Chapter 3, page 155, "Attacks" for "Monk"
//	- Chapter 3, page 167, "Attacks" for "Ranger"
//	- Chapter 3, page 179, "Attacks" for "Rogue"
//	- Chapter 3, page 191, "Attacks" for "Sorcerer"
UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponCategorySimple,
	"PF2.Proficiency.Weapon.Category.Simple",
	"Character proficiency ranks for Simple weapons."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponCategorySimpleUntrained,
	"PF2.Proficiency.Weapon.Category.Simple.Untrained",
	"Character is Untrained with Simple weapons."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponCategorySimpleTrained,
	"PF2.Proficiency.Weapon.Category.Simple.Trained",
	"Character is Trained with Simple weapons."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponCategorySimpleExpert,
	"PF2.Proficiency.Weapon.Category.Simple.Expert",
	"Character is Expert with Simple weapons."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponCategorySimpleMaster,
	"PF2.Proficiency.Weapon.Category.Simple.Master",
	"Character is Master with Simple weapons."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponCategorySimpleLegendary,
	"PF2.Proficiency.Weapon.Category.Simple.Legendary",
	"Character is Legendary with Simple weapons."
)

// =====================================================================================================================
// Proficiency Ranks for Advanced Weapons
// =====================================================================================================================
// Weapon type mentioned in Pathfinder 2E Core Rulebook under:
//	- Chapter 3, page 141, "Attacks" for "Fighter"
UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponCategoryAdvanced,
	"PF2.Proficiency.Weapon.Category.Advanced",
	"Character proficiency ranks for Advanced weapons."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponCategoryAdvancedUntrained,
	"PF2.Proficiency.Weapon.Category.Advanced.Untrained",
	"Character is Untrained with Advanced weapons."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponCategoryAdvancedTrained,
	"PF2.Proficiency.Weapon.Category.Advanced.Trained",
	"Character is Trained with Advanced weapons."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponCategoryAdvancedExpert,
	"PF2.Proficiency.Weapon.Category.Advanced.Expert",
	"Character is Expert with Advanced weapons."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponCategoryAdvancedMaster,
	"PF2.Proficiency.Weapon.Category.Advanced.Master",
	"Character is Master with Advanced weapons."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponCategoryAdvancedLegendary,
	"PF2.Proficiency.Weapon.Category.Advanced.Legendary",
	"Character is Legendary with Advanced weapons."
)

// =====================================================================================================================
// Proficiency Ranks for Advanced Dwarf Weapons
// =====================================================================================================================
// From the Pathfinder 2E Core Rulebook, Chapter 2, page 36, "Dwarven Weapon Familiarity":
// "For the purpose of determining your proficiency, [...] advanced dwarf weapons are martial weapons."
UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponCategoryAdvancedDwarf,
	"PF2.Proficiency.Weapon.Category.AdvancedDwarf",
	"Character proficiency ranks for Advanced Dwarf weapons."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponCategoryAdvancedDwarfUntrained,
	"PF2.Proficiency.Weapon.Category.AdvancedDwarf.Untrained",
	"Character is Untrained with Advanced Dwarf weapons."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponCategoryAdvancedDwarfTrained,
	"PF2.Proficiency.Weapon.Category.AdvancedDwarf.Trained",
	"Character is Trained with Advanced Dwarf weapons."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponCategoryAdvancedDwarfExpert,
	"PF2.Proficiency.Weapon.Category.AdvancedDwarf.Expert",
	"Character is Expert with Advanced Dwarf weapons."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponCategoryAdvancedDwarfMaster,
	"PF2.Proficiency.Weapon.Category.AdvancedDwarf.Master",
	"Character is Master with Advanced Dwarf weapons."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponCategoryAdvancedDwarfLegendary,
	"PF2.Proficiency.Weapon.Category.AdvancedDwarf.Legendary",
	"Character is Legendary with Advanced Dwarf weapons."
)

// =====================================================================================================================
// Proficiency Ranks for Advanced Elf Weapons
// =====================================================================================================================
// From the Pathfinder 2E Core Rulebook, Chapter 2, page 40, "Elven Weapon Familiarity":
// "For the purpose of determining your proficiency, [...] advanced elf weapons are martial weapons."
UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponCategoryAdvancedElf,
	"PF2.Proficiency.Weapon.Category.AdvancedElf",
	"Character proficiency ranks for Advanced Elf weapons."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponCategoryAdvancedElfUntrained,
	"PF2.Proficiency.Weapon.Category.AdvancedElf.Untrained",
	"Character is Untrained with Advanced Elf weapons."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponCategoryAdvancedElfTrained,
	"PF2.Proficiency.Weapon.Category.AdvancedElf.Trained",
	"Character is Trained with Advanced Elf weapons."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponCategoryAdvancedElfExpert,
	"PF2.Proficiency.Weapon.Category.AdvancedElf.Expert",
	"Character is Expert with Advanced Elf weapons."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponCategoryAdvancedElfMaster,
	"PF2.Proficiency.Weapon.Category.AdvancedElf.Master",
	"Character is Master with Advanced Elf weapons."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponCategoryAdvancedElfLegendary,
	"PF2.Proficiency.Weapon.Category.AdvancedElf.Legendary",
	"Character is Legendary with Advanced Elf weapons."
)

// =====================================================================================================================
// Proficiency Ranks for Advanced Gnome Weapons
// =====================================================================================================================
// From the Pathfinder 2E Core Rulebook, Chapter 2, page 44, "Gnome Weapon Familiarity":
// "For the purpose of determining your proficiency, [...] advanced gnome weapons are martial weapons."
UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponCategoryAdvancedGnome,
	"PF2.Proficiency.Weapon.Category.AdvancedGnome",
	"Character proficiency ranks for Advanced Gnome weapons."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponCategoryAdvancedGnomeUntrained,
	"PF2.Proficiency.Weapon.Category.AdvancedGnome.Untrained",
	"Character is Untrained with Advanced Gnome weapons."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponCategoryAdvancedGnomeTrained,
	"PF2.Proficiency.Weapon.Category.AdvancedGnome.Trained",
	"Character is Trained with Advanced Gnome weapons."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponCategoryAdvancedGnomeExpert,
	"PF2.Proficiency.Weapon.Category.AdvancedGnome.Expert",
	"Character is Expert with Advanced Gnome weapons."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponCategoryAdvancedGnomeMaster,
	"PF2.Proficiency.Weapon.Category.AdvancedGnome.Master",
	"Character is Master with Advanced Gnome weapons."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponCategoryAdvancedGnomeLegendary,
	"PF2.Proficiency.Weapon.Category.AdvancedGnome.Legendary",
	"Character is Legendary with Advanced Gnome weapons."
)

// =====================================================================================================================
// Proficiency Ranks for Advanced Goblin Weapons
// =====================================================================================================================
// From the Pathfinder 2E Core Rulebook, Chapter 2, page 48, "Goblin Weapon Familiarity":
// "For the purpose of determining your proficiency, [...] advanced goblin weapons are martial weapons."
UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponCategoryAdvancedGoblin,
	"PF2.Proficiency.Weapon.Category.AdvancedGoblin",
	"Character proficiency ranks for Advanced Goblin weapons."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponCategoryAdvancedGoblinUntrained,
	"PF2.Proficiency.Weapon.Category.AdvancedGoblin.Untrained",
	"Character is Untrained with Advanced Goblin weapons."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponCategoryAdvancedGoblinTrained,
	"PF2.Proficiency.Weapon.Category.AdvancedGoblin.Trained",
	"Character is Trained with Advanced Goblin weapons."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponCategoryAdvancedGoblinExpert,
	"PF2.Proficiency.Weapon.Category.AdvancedGoblin.Expert",
	"Character is Expert with Advanced Goblin weapons."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponCategoryAdvancedGoblinMaster,
	"PF2.Proficiency.Weapon.Category.AdvancedGoblin.Master",
	"Character is Master with Advanced Goblin weapons."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponCategoryAdvancedGoblinLegendary,
	"PF2.Proficiency.Weapon.Category.AdvancedGoblin.Legendary",
	"Character is Legendary with Advanced Goblin weapons."
)

// =====================================================================================================================
// Proficiency Ranks for Advanced Halfling Weapons
// =====================================================================================================================
// From the Pathfinder 2E Core Rulebook, Chapter 2, page 52, "Halfling Weapon Familiarity":
// "For the purpose of determining your proficiency, [...] advanced halfling weapons are martial weapons."
UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponCategoryAdvancedHalfling,
	"PF2.Proficiency.Weapon.Category.AdvancedHalfling",
	"Character proficiency ranks for Advanced Halfling weapons."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponCategoryAdvancedHalflingUntrained,
	"PF2.Proficiency.Weapon.Category.AdvancedHalfling.Untrained",
	"Character is Untrained with Advanced Halfling weapons."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponCategoryAdvancedHalflingTrained,
	"PF2.Proficiency.Weapon.Category.AdvancedHalfling.Trained",
	"Character is Trained with Advanced Halfling weapons."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponCategoryAdvancedHalflingExpert,
	"PF2.Proficiency.Weapon.Category.AdvancedHalfling.Expert",
	"Character is Expert with Advanced Halfling weapons."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponCategoryAdvancedHalflingMaster,
	"PF2.Proficiency.Weapon.Category.AdvancedHalfling.Master",
	"Character is Master with Advanced Halfling weapons."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponCategoryAdvancedHalflingLegendary,
	"PF2.Proficiency.Weapon.Category.AdvancedHalfling.Legendary",
	"Character is Legendary with Advanced Halfling weapons."
)

// =====================================================================================================================
// Proficiency Ranks for Martial Weapons
// =====================================================================================================================
// Weapon type mentioned in Pathfinder 2E Core Rulebook under:
//	- Chapter 3, page 83, "Attacks" for "Barbarian"
//	- Chapter 3, page 105, "Attacks" for "Champion"
//	- Chapter 3, page 141, "Attacks" for "Fighter"
//	- Chapter 3, page 167, "Attacks" for "Ranger"
UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponCategoryMartial,
	"PF2.Proficiency.Weapon.Category.Martial",
	"Character proficiency ranks for Martial weapons."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponCategoryMartialUntrained,
	"PF2.Proficiency.Weapon.Category.Martial.Untrained",
	"Character is Untrained with Martial weapons."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponCategoryMartialTrained,
	"PF2.Proficiency.Weapon.Category.Martial.Trained",
	"Character is Trained with Martial weapons."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponCategoryMartialExpert,
	"PF2.Proficiency.Weapon.Category.Martial.Expert",
	"Character is Expert with Martial weapons."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponCategoryMartialMaster,
	"PF2.Proficiency.Weapon.Category.Martial.Master",
	"Character is Master with Martial weapons."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponCategoryMartialLegendary,
	"PF2.Proficiency.Weapon.Category.Martial.Legendary",
	"Character is Legendary with Martial weapons."
)

// =====================================================================================================================
// Proficiency Ranks for Martial Dwarf Weapons
// =====================================================================================================================
// From the Pathfinder 2E Core Rulebook, Chapter 2, page 36, "Dwarven Weapon Familiarity":
// "For the purpose of determining your proficiency, martial dwarf weapons are simple weapons..."
UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponCategoryMartialDwarf,
	"PF2.Proficiency.Weapon.Category.MartialDwarf",
	"Character proficiency ranks for Martial Dwarf weapons."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponCategoryMartialDwarfUntrained,
	"PF2.Proficiency.Weapon.Category.MartialDwarf.Untrained",
	"Character is Untrained with Martial Dwarf weapons."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponCategoryMartialDwarfTrained,
	"PF2.Proficiency.Weapon.Category.MartialDwarf.Trained",
	"Character is Trained with Martial Dwarf weapons."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponCategoryMartialDwarfExpert,
	"PF2.Proficiency.Weapon.Category.MartialDwarf.Expert",
	"Character is Expert with Martial Dwarf weapons."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponCategoryMartialDwarfMaster,
	"PF2.Proficiency.Weapon.Category.MartialDwarf.Master",
	"Character is Master with Martial Dwarf weapons."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponCategoryMartialDwarfLegendary,
	"PF2.Proficiency.Weapon.Category.MartialDwarf.Legendary",
	"Character is Legendary with Martial Dwarf weapons."
)

// =====================================================================================================================
// Proficiency Ranks for Martial Elf Weapons
// =====================================================================================================================
// From the Pathfinder 2E Core Rulebook, Chapter 2, page 40, "Elven Weapon Familiarity":
// "For the purpose of determining your proficiency, martial elf weapons are simple weapons..."
UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponCategoryMartialElf,
	"PF2.Proficiency.Weapon.Category.MartialElf",
	"Character proficiency ranks for Martial Elf weapons."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponCategoryMartialElfUntrained,
	"PF2.Proficiency.Weapon.Category.MartialElf.Untrained",
	"Character is Untrained with Martial Elf weapons."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponCategoryMartialElfTrained,
	"PF2.Proficiency.Weapon.Category.MartialElf.Trained",
	"Character is Trained with Martial Elf weapons."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponCategoryMartialElfExpert,
	"PF2.Proficiency.Weapon.Category.MartialElf.Expert",
	"Character is Expert with Martial Elf weapons."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponCategoryMartialElfMaster,
	"PF2.Proficiency.Weapon.Category.MartialElf.Master",
	"Character is Master with Martial Elf weapons."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponCategoryMartialElfLegendary,
	"PF2.Proficiency.Weapon.Category.MartialElf.Legendary",
	"Character is Legendary with Martial Elf weapons."
)

// =====================================================================================================================
// Proficiency Ranks for Martial Gnome Weapons
// =====================================================================================================================
// From the Pathfinder 2E Core Rulebook, Chapter 2, page 44, "Gnome Weapon Familiarity":
// "For the purpose of determining your proficiency, martial gnome weapons are simple weapons..."
UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponCategoryMartialGnome,
	"PF2.Proficiency.Weapon.Category.MartialGnome",
	"Character proficiency ranks for Martial Gnome weapons."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponCategoryMartialGnomeUntrained,
	"PF2.Proficiency.Weapon.Category.MartialGnome.Untrained",
	"Character is Untrained with Martial Gnome weapons."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponCategoryMartialGnomeTrained,
	"PF2.Proficiency.Weapon.Category.MartialGnome.Trained",
	"Character is Trained with Martial Gnome weapons."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponCategoryMartialGnomeExpert,
	"PF2.Proficiency.Weapon.Category.MartialGnome.Expert",
	"Character is Expert with Martial Gnome weapons."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponCategoryMartialGnomeMaster,
	"PF2.Proficiency.Weapon.Category.MartialGnome.Master",
	"Character is Master with Martial Gnome weapons."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponCategoryMartialGnomeLegendary,
	"PF2.Proficiency.Weapon.Category.MartialGnome.Legendary",
	"Character is Legendary with Martial Gnome weapons."
)

// =====================================================================================================================
// Proficiency Ranks for Martial Goblin Weapons
// =====================================================================================================================
// From the Pathfinder 2E Core Rulebook, Chapter 2, page 48, "Goblin Weapon Familiarity":
// "For the purpose of determining your proficiency, martial goblin weapons are simple weapons..."
UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponCategoryMartialGoblin,
	"PF2.Proficiency.Weapon.Category.MartialGoblin",
	"Character proficiency ranks for Martial Goblin weapons."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponCategoryMartialGoblinUntrained,
	"PF2.Proficiency.Weapon.Category.MartialGoblin.Untrained",
	"Character is Untrained with Martial Goblin weapons."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponCategoryMartialGoblinTrained,
	"PF2.Proficiency.Weapon.Category.MartialGoblin.Trained",
	"Character is Trained with Martial Goblin weapons."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponCategoryMartialGoblinExpert,
	"PF2.Proficiency.Weapon.Category.MartialGoblin.Expert",
	"Character is Expert with Martial Goblin weapons."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponCategoryMartialGoblinMaster,
	"PF2.Proficiency.Weapon.Category.MartialGoblin.Master",
	"Character is Master with Martial Goblin weapons."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponCategoryMartialGoblinLegendary,
	"PF2.Proficiency.Weapon.Category.MartialGoblin.Legendary",
	"Character is Legendary with Martial Goblin weapons."
)

// =====================================================================================================================
// Proficiency Ranks for Martial Halfling Weapons
// =====================================================================================================================
// From the Pathfinder 2E Core Rulebook, Chapter 2, page 52, "Halfling Weapon Familiarity":
// "For the purpose of determining your proficiency, martial halfling weapons are simple weapons..."
UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponCategoryMartialHalfling,
	"PF2.Proficiency.Weapon.Category.MartialHalfling",
	"Character proficiency ranks for Martial Halfling weapons."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponCategoryMartialHalflingUntrained,
	"PF2.Proficiency.Weapon.Category.MartialHalfling.Untrained",
	"Character is Untrained with Martial Halfling weapons."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponCategoryMartialHalflingTrained,
	"PF2.Proficiency.Weapon.Category.MartialHalfling.Trained",
	"Character is Trained with Martial Halfling weapons."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponCategoryMartialHalflingExpert,
	"PF2.Proficiency.Weapon.Category.MartialHalfling.Expert",
	"Character is Expert with Martial Halfling weapons."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponCategoryMartialHalflingMaster,
	"PF2.Proficiency.Weapon.Category.MartialHalfling.Master",
	"Character is Master with Martial Halfling weapons."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponCategoryMartialHalflingLegendary,
	"PF2.Proficiency.Weapon.Category.MartialHalfling.Legendary",
	"Character is Legendary with Martial Halfling weapons."
)

// =====================================================================================================================
// Proficiency Ranks for Alchemical Bombs
// =====================================================================================================================
// Weapon type mentioned in Pathfinder 2E Core Rulebook under:
//	- Chapter 3, page 71, "Attacks" for "Alchemist"
UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponAlchemicalBomb,
	"PF2.Proficiency.Weapon.AlchemicalBomb",
	"Character proficiency ranks for Alchemical Bombs."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponAlchemicalBombUntrained,
	"PF2.Proficiency.Weapon.AlchemicalBomb.Untrained",
	"Character is Untrained with Alchemical Bombs."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponAlchemicalBombTrained,
	"PF2.Proficiency.Weapon.AlchemicalBomb.Trained",
	"Character is Trained with Alchemical Bombs."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponAlchemicalBombExpert,
	"PF2.Proficiency.Weapon.AlchemicalBomb.Expert",
	"Character is Expert with Alchemical Bombs."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponAlchemicalBombMaster,
	"PF2.Proficiency.Weapon.AlchemicalBomb.Master",
	"Character is Master with Alchemical Bombs."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponAlchemicalBombLegendary,
	"PF2.Proficiency.Weapon.AlchemicalBomb.Legendary",
	"Character is Legendary with Alchemical Bombs."
)

// =====================================================================================================================
// Proficiency Ranks for Battle Axes
// =====================================================================================================================
// Weapon mentioned in Pathfinder 2E Core Rulebook, Chapter 2, page 36, "Dwarven Weapon Familiarity".
UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponBattleAxe,
	"PF2.Proficiency.Weapon.BattleAxe",
	"Character proficiency ranks for Battle Axes."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponBattleAxeUntrained,
	"PF2.Proficiency.Weapon.BattleAxe.Untrained",
	"Character is Untrained with Battle Axes."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponBattleAxeTrained,
	"PF2.Proficiency.Weapon.BattleAxe.Trained",
	"Character is Trained with Battle Axes."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponBattleAxeExpert,
	"PF2.Proficiency.Weapon.BattleAxe.Expert",
	"Character is Expert with Battle Axes."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponBattleAxeMaster,
	"PF2.Proficiency.Weapon.BattleAxe.Master",
	"Character is Master with Battle Axes."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponBattleAxeLegendary,
	"PF2.Proficiency.Weapon.BattleAxe.Legendary",
	"Character is Legendary with Battle Axes."
)

// =====================================================================================================================
// Proficiency Ranks for Clubs
// =====================================================================================================================
// Weapon mentioned in Pathfinder 2E Core Rulebook, under:
//	- Chapter 3, page 203, "Attacks" for "Wizard"
UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponClub,
	"PF2.Proficiency.Weapon.Club",
	"Character proficiency ranks for Clubs."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponClubUntrained,
	"PF2.Proficiency.Weapon.Club.Untrained",
	"Character is Untrained with Clubs."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponClubTrained,
	"PF2.Proficiency.Weapon.Club.Trained",
	"Character is Trained with Clubs."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponClubExpert,
	"PF2.Proficiency.Weapon.Club.Expert",
	"Character is Expert with Clubs."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponClubMaster,
	"PF2.Proficiency.Weapon.Club.Master",
	"Character is Master with Clubs."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponClubLegendary,
	"PF2.Proficiency.Weapon.Club.Legendary",
	"Character is Legendary with Clubs."
)

// =====================================================================================================================
// Proficiency Ranks for Composite Longbows
// =====================================================================================================================
// Weapon mentioned in Pathfinder 2E Core Rulebook, Chapter 2, page 40, "Elven Weapon Familiarity".
UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponCompositeLongbow,
	"PF2.Proficiency.Weapon.CompositeLongbow",
	"Character proficiency ranks for Composite Longbows."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponCompositeLongbowUntrained,
	"PF2.Proficiency.Weapon.CompositeLongbow.Untrained",
	"Character is Untrained with Composite Longbows."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponCompositeLongbowTrained,
	"PF2.Proficiency.Weapon.CompositeLongbow.Trained",
	"Character is Trained with Composite Longbows."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponCompositeLongbowExpert,
	"PF2.Proficiency.Weapon.CompositeLongbow.Expert",
	"Character is Expert with Composite Longbows."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponCompositeLongbowMaster,
	"PF2.Proficiency.Weapon.CompositeLongbow.Master",
	"Character is Master with Composite Longbows."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponCompositeLongbowLegendary,
	"PF2.Proficiency.Weapon.CompositeLongbow.Legendary",
	"Character is Legendary with Composite Longbows."
)

// =====================================================================================================================
// Proficiency Ranks for Composite Shortbows
// =====================================================================================================================
// Weapon mentioned in Pathfinder 2E Core Rulebook, Chapter 2, page 40, "Elven Weapon Familiarity".
UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponCompositeShortbow,
	"PF2.Proficiency.Weapon.CompositeShortbow",
	"Character proficiency ranks for Composite Shortbows."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponCompositeShortbowUntrained,
	"PF2.Proficiency.Weapon.CompositeShortbow.Untrained",
	"Character is Untrained with Composite Shortbows."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponCompositeShortbowTrained,
	"PF2.Proficiency.Weapon.CompositeShortbow.Trained",
	"Character is Trained with Composite Shortbows."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponCompositeShortbowExpert,
	"PF2.Proficiency.Weapon.CompositeShortbow.Expert",
	"Character is Expert with Composite Shortbows."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponCompositeShortbowMaster,
	"PF2.Proficiency.Weapon.CompositeShortbow.Master",
	"Character is Master with Composite Shortbows."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponCompositeShortbowLegendary,
	"PF2.Proficiency.Weapon.CompositeShortbow.Legendary",
	"Character is Legendary with Composite Shortbows."
)

// =====================================================================================================================
// Proficiency Ranks for Crossbows
// =====================================================================================================================
// Weapon mentioned in Pathfinder 2E Core Rulebook, under:
//	- Chapter 3, page 203, "Attacks" for "Wizard"
UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponCrossbow,
	"PF2.Proficiency.Weapon.Crossbow",
	"Character proficiency ranks for Crossbows."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponCrossbowUntrained,
	"PF2.Proficiency.Weapon.Crossbow.Untrained",
	"Character is Untrained with Crossbows."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponCrossbowTrained,
	"PF2.Proficiency.Weapon.Crossbow.Trained",
	"Character is Trained with Crossbows."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponCrossbowExpert,
	"PF2.Proficiency.Weapon.Crossbow.Expert",
	"Character is Expert with Crossbows."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponCrossbowMaster,
	"PF2.Proficiency.Weapon.Crossbow.Master",
	"Character is Master with Crossbows."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponCrossbowLegendary,
	"PF2.Proficiency.Weapon.Crossbow.Legendary",
	"Character is Legendary with Crossbows."
)

// =====================================================================================================================
// Proficiency Ranks for Daggers
// =====================================================================================================================
// Weapon mentioned in Pathfinder 2E Core Rulebook, under:
//	- Chapter 3, page 203, "Attacks" for "Wizard"
UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponDagger,
	"PF2.Proficiency.Weapon.Dagger",
	"Character proficiency ranks for Daggers."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponDaggerUntrained,
	"PF2.Proficiency.Weapon.Dagger.Untrained",
	"Character is Untrained with Daggers."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponDaggerTrained,
	"PF2.Proficiency.Weapon.Dagger.Trained",
	"Character is Trained with Daggers."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponDaggerExpert,
	"PF2.Proficiency.Weapon.Dagger.Expert",
	"Character is Expert with Daggers."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponDaggerMaster,
	"PF2.Proficiency.Weapon.Dagger.Master",
	"Character is Master with Daggers."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponDaggerLegendary,
	"PF2.Proficiency.Weapon.Dagger.Legendary",
	"Character is Legendary with Daggers."
)

// =====================================================================================================================
// Proficiency Ranks for Dogslicers
// =====================================================================================================================
// Weapon mentioned in Pathfinder 2E Core Rulebook, Chapter 2, page 48, "Goblin Weapon Familiarity".
UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponDogslicer,
	"PF2.Proficiency.Weapon.Dogslicer",
	"Character proficiency ranks for Dogslicers."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponDogslicerUntrained,
	"PF2.Proficiency.Weapon.Dogslicer.Untrained",
	"Character is Untrained with Dogslicers."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponDogslicerTrained,
	"PF2.Proficiency.Weapon.Dogslicer.Trained",
	"Character is Trained with Dogslicers."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponDogslicerExpert,
	"PF2.Proficiency.Weapon.Dogslicer.Expert",
	"Character is Expert with Dogslicers."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponDogslicerMaster,
	"PF2.Proficiency.Weapon.Dogslicer.Master",
	"Character is Master with Dogslicers."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponDogslicerLegendary,
	"PF2.Proficiency.Weapon.Dogslicer.Legendary",
	"Character is Legendary with Dogslicers."
)

// =====================================================================================================================
// Proficiency Ranks for Falchions
// =====================================================================================================================
// Weapon mentioned in Pathfinder 2E Core Rulebook, Chapter 2, page 58, "Orc Weapon Familiarity".
UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponFalchion,
	"PF2.Proficiency.Weapon.Falchion",
	"Character proficiency ranks for Falchions."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponFalchionUntrained,
	"PF2.Proficiency.Weapon.Falchion.Untrained",
	"Character is Untrained with Falchions."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponFalchionTrained,
	"PF2.Proficiency.Weapon.Falchion.Trained",
	"Character is Trained with Falchions."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponFalchionExpert,
	"PF2.Proficiency.Weapon.Falchion.Expert",
	"Character is Expert with Falchions."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponFalchionMaster,
	"PF2.Proficiency.Weapon.Falchion.Master",
	"Character is Master with Falchions."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponFalchionLegendary,
	"PF2.Proficiency.Weapon.Falchion.Legendary",
	"Character is Legendary with Falchions."
)

// =====================================================================================================================
// Proficiency Ranks for Glaives
// =====================================================================================================================
// Weapon mentioned in Pathfinder 2E Core Rulebook, Chapter 2, page 44, "Gnome Weapon Familiarity".
UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponGlaive,
	"PF2.Proficiency.Weapon.Glaive",
	"Character proficiency ranks for Glaives."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponGlaiveUntrained,
	"PF2.Proficiency.Weapon.Glaive.Untrained",
	"Character is Untrained with Glaives."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponGlaiveTrained,
	"PF2.Proficiency.Weapon.Glaive.Trained",
	"Character is Trained with Glaives."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponGlaiveExpert,
	"PF2.Proficiency.Weapon.Glaive.Expert",
	"Character is Expert with Glaives."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponGlaiveMaster,
	"PF2.Proficiency.Weapon.Glaive.Master",
	"Character is Master with Glaives."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponGlaiveLegendary,
	"PF2.Proficiency.Weapon.Glaive.Legendary",
	"Character is Legendary with Glaives."
)

// =====================================================================================================================
// Proficiency Ranks for Greataxes
// =====================================================================================================================
// Weapon mentioned in Pathfinder 2E Core Rulebook, Chapter 2, page 58, "Orc Weapon Familiarity".
UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponGreataxe,
	"PF2.Proficiency.Weapon.Greataxe",
	"Character proficiency ranks for Greataxes."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponGreataxeUntrained,
	"PF2.Proficiency.Weapon.Greataxe.Untrained",
	"Character is Untrained with Greataxes."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponGreataxeTrained,
	"PF2.Proficiency.Weapon.Greataxe.Trained",
	"Character is Trained with Greataxes."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponGreataxeExpert,
	"PF2.Proficiency.Weapon.Greataxe.Expert",
	"Character is Expert with Greataxes."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponGreataxeMaster,
	"PF2.Proficiency.Weapon.Greataxe.Master",
	"Character is Master with Greataxes."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponGreataxeLegendary,
	"PF2.Proficiency.Weapon.Greataxe.Legendary",
	"Character is Legendary with Greataxes."
)

// =====================================================================================================================
// Proficiency Ranks for Halfling Sling Staves
// =====================================================================================================================
// Weapon mentioned in Pathfinder 2E Core Rulebook, Chapter 2, page 52, "Halfling Weapon Familiarity".
UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponHalflingSlingStaff,
	"PF2.Proficiency.Weapon.HalflingSlingStaff",
	"Character proficiency ranks for Halfling Sling Staves."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponHalflingSlingStaffUntrained,
	"PF2.Proficiency.Weapon.HalflingSlingStaff.Untrained",
	"Character is Untrained with Halfling Sling Staves."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponHalflingSlingStaffTrained,
	"PF2.Proficiency.Weapon.HalflingSlingStaff.Trained",
	"Character is Trained with Halfling Sling Staves."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponHalflingSlingStaffExpert,
	"PF2.Proficiency.Weapon.HalflingSlingStaff.Expert",
	"Character is Expert with Halfling Sling Staves."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponHalflingSlingStaffMaster,
	"PF2.Proficiency.Weapon.HalflingSlingStaff.Master",
	"Character is Master with Halfling Sling Staves."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponHalflingSlingStaffLegendary,
	"PF2.Proficiency.Weapon.HalflingSlingStaff.Legendary",
	"Character is Legendary with Halfling Sling Staves."
)

// =====================================================================================================================
// Proficiency Ranks for Heavy Crossbows
// =====================================================================================================================
// Weapon mentioned in Pathfinder 2E Core Rulebook, under:
//	- Chapter 3, page 203, "Attacks" for "Wizard"
UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponHeavyCrossbow,
	"PF2.Proficiency.Weapon.HeavyCrossbow",
	"Character proficiency ranks for Heavy Crossbows."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponHeavyCrossbowUntrained,
	"PF2.Proficiency.Weapon.HeavyCrossbow.Untrained",
	"Character is Untrained with Heavy Crossbows."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponHeavyCrossbowTrained,
	"PF2.Proficiency.Weapon.HeavyCrossbow.Trained",
	"Character is Trained with Heavy Crossbows."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponHeavyCrossbowExpert,
	"PF2.Proficiency.Weapon.HeavyCrossbow.Expert",
	"Character is Expert with Heavy Crossbows."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponHeavyCrossbowMaster,
	"PF2.Proficiency.Weapon.HeavyCrossbow.Master",
	"Character is Master with Heavy Crossbows."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponHeavyCrossbowLegendary,
	"PF2.Proficiency.Weapon.HeavyCrossbow.Legendary",
	"Character is Legendary with Heavy Crossbows."
)

// =====================================================================================================================
// Proficiency Ranks for Horsechoppers
// =====================================================================================================================
// Weapon mentioned in Pathfinder 2E Core Rulebook, Chapter 2, page 48, "Goblin Weapon Familiarity".
UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponHorsechopper,
	"PF2.Proficiency.Weapon.Horsechopper",
	"Character proficiency ranks for Horsechoppers."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponHorsechopperUntrained,
	"PF2.Proficiency.Weapon.Horsechopper.Untrained",
	"Character is Untrained with Horsechoppers."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponHorsechopperTrained,
	"PF2.Proficiency.Weapon.Horsechopper.Trained",
	"Character is Trained with Horsechoppers."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponHorsechopperExpert,
	"PF2.Proficiency.Weapon.Horsechopper.Expert",
	"Character is Expert with Horsechoppers."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponHorsechopperMaster,
	"PF2.Proficiency.Weapon.Horsechopper.Master",
	"Character is Master with Horsechoppers."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponHorsechopperLegendary,
	"PF2.Proficiency.Weapon.Horsechopper.Legendary",
	"Character is Legendary with Horsechoppers."
)

// =====================================================================================================================
// Proficiency Ranks for Kukris
// =====================================================================================================================
// Weapon mentioned in Pathfinder 2E Core Rulebook, Chapter 2, page 44, "Gnome Weapon Familiarity".
UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponKukri,
	"PF2.Proficiency.Weapon.Kukri",
	"Character proficiency ranks for Kukris."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponKukriUntrained,
	"PF2.Proficiency.Weapon.Kukri.Untrained",
	"Character is Untrained with Kukris."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponKukriTrained,
	"PF2.Proficiency.Weapon.Kukri.Trained",
	"Character is Trained with Kukris."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponKukriExpert,
	"PF2.Proficiency.Weapon.Kukri.Expert",
	"Character is Expert with Kukris."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponKukriMaster,
	"PF2.Proficiency.Weapon.Kukri.Master",
	"Character is Master with Kukris."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponKukriLegendary,
	"PF2.Proficiency.Weapon.Kukri.Legendary",
	"Character is Legendary with Kukris."
)

// =====================================================================================================================
// Proficiency Ranks for Longbows
// =====================================================================================================================
// Weapon mentioned in Pathfinder 2E Core Rulebook, Chapter 2, page 40, "Elven Weapon Familiarity".
UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponLongbow,
	"PF2.Proficiency.Weapon.Longbow",
	"Character proficiency ranks for Longbows."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponLongbowUntrained,
	"PF2.Proficiency.Weapon.Longbow.Untrained",
	"Character is Untrained with Longbows."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponLongbowTrained,
	"PF2.Proficiency.Weapon.Longbow.Trained",
	"Character is Trained with Longbows."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponLongbowExpert,
	"PF2.Proficiency.Weapon.Longbow.Expert",
	"Character is Expert with Longbows."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponLongbowMaster,
	"PF2.Proficiency.Weapon.Longbow.Master",
	"Character is Master with Longbows."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponLongbowLegendary,
	"PF2.Proficiency.Weapon.Longbow.Legendary",
	"Character is Legendary with Longbows."
)

// =====================================================================================================================
// Proficiency Ranks for Longswords
// =====================================================================================================================
// Weapon mentioned in Pathfinder 2E Core Rulebook, under:
//	- Chapter 2, page 40, "Elven Weapon Familiarity"
//	- Chapter 3, page 95, "Attacks" for "Bard"
UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponLongsword,
	"PF2.Proficiency.Weapon.Longsword",
	"Character proficiency ranks for Longswords."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponLongswordUntrained,
	"PF2.Proficiency.Weapon.Longsword.Untrained",
	"Character is Untrained with Longswords."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponLongswordTrained,
	"PF2.Proficiency.Weapon.Longsword.Trained",
	"Character is Trained with Longswords."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponLongswordExpert,
	"PF2.Proficiency.Weapon.Longsword.Expert",
	"Character is Expert with Longswords."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponLongswordMaster,
	"PF2.Proficiency.Weapon.Longsword.Master",
	"Character is Master with Longswords."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponLongswordLegendary,
	"PF2.Proficiency.Weapon.Longsword.Legendary",
	"Character is Legendary with Longswords."
)

// =====================================================================================================================
// Proficiency Ranks for Picks
// =====================================================================================================================
// Weapon mentioned in Pathfinder 2E Core Rulebook, Chapter 2, page 36, "Dwarven Weapon Familiarity".
UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponPick,
	"PF2.Proficiency.Weapon.Pick",
	"Character proficiency ranks for Picks."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponPickUntrained,
	"PF2.Proficiency.Weapon.Pick.Untrained",
	"Character is Untrained with Picks."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponPickTrained,
	"PF2.Proficiency.Weapon.Pick.Trained",
	"Character is Trained with Picks."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponPickExpert,
	"PF2.Proficiency.Weapon.Pick.Expert",
	"Character is Expert with Picks."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponPickMaster,
	"PF2.Proficiency.Weapon.Pick.Master",
	"Character is Master with Picks."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponPickLegendary,
	"PF2.Proficiency.Weapon.Pick.Legendary",
	"Character is Legendary with Picks."
)

// =====================================================================================================================
// Proficiency Ranks for Rapiers
// =====================================================================================================================
// Weapon mentioned in Pathfinder 2E Core Rulebook, under:
//	- Chapter 2, page 40, "Elven Weapon Familiarity"
//	- Chapter 3, page 95, "Attacks" for "Bard"
//	- Chapter 3, page 179, "Attacks" for "Rogue"
UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponRapier,
	"PF2.Proficiency.Weapon.Rapier",
	"Character proficiency ranks for Rapiers."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponRapierUntrained,
	"PF2.Proficiency.Weapon.Rapier.Untrained",
	"Character is Untrained with Rapiers."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponRapierTrained,
	"PF2.Proficiency.Weapon.Rapier.Trained",
	"Character is Trained with Rapiers."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponRapierExpert,
	"PF2.Proficiency.Weapon.Rapier.Expert",
	"Character is Expert with Rapiers."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponRapierMaster,
	"PF2.Proficiency.Weapon.Rapier.Master",
	"Character is Master with Rapiers."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponRapierLegendary,
	"PF2.Proficiency.Weapon.Rapier.Legendary",
	"Character is Legendary with Rapiers."
)

// =====================================================================================================================
// Proficiency Ranks for Saps
// =====================================================================================================================
// Weapon mentioned in Pathfinder 2E Core Rulebook, under:
//	- Chapter 3, page 95, "Attacks" for "Bard"
//	- Chapter 3, page 179, "Attacks" for "Rogue"
UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponSap,
	"PF2.Proficiency.Weapon.Sap",
	"Character proficiency ranks for Saps."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponSapUntrained,
	"PF2.Proficiency.Weapon.Sap.Untrained",
	"Character is Untrained with Saps."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponSapTrained,
	"PF2.Proficiency.Weapon.Sap.Trained",
	"Character is Trained with Saps."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponSapExpert,
	"PF2.Proficiency.Weapon.Sap.Expert",
	"Character is Expert with Saps."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponSapMaster,
	"PF2.Proficiency.Weapon.Sap.Master",
	"Character is Master with Saps."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponSapLegendary,
	"PF2.Proficiency.Weapon.Sap.Legendary",
	"Character is Legendary with Saps."
)

// =====================================================================================================================
// Proficiency Ranks for Shortbows
// =====================================================================================================================
// Weapon mentioned in Pathfinder 2E Core Rulebook, under:
//	- Chapter 2, page 40, "Elven Weapon Familiarity"
//	- Chapter 3, page 95, "Attacks" for "Bard"
//	- Chapter 3, page 179, "Attacks" for "Rogue"
UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponShortbow,
	"PF2.Proficiency.Weapon.Shortbow",
	"Character proficiency ranks for Shortbows."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponShortbowUntrained,
	"PF2.Proficiency.Weapon.Shortbow.Untrained",
	"Character is Untrained with Shortbows."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponShortbowTrained,
	"PF2.Proficiency.Weapon.Shortbow.Trained",
	"Character is Trained with Shortbows."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponShortbowExpert,
	"PF2.Proficiency.Weapon.Shortbow.Expert",
	"Character is Expert with Shortbows."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponShortbowMaster,
	"PF2.Proficiency.Weapon.Shortbow.Master",
	"Character is Master with Shortbows."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponShortbowLegendary,
	"PF2.Proficiency.Weapon.Shortbow.Legendary",
	"Character is Legendary with Shortbows."
)

// =====================================================================================================================
// Proficiency Ranks for Shortswords
// =====================================================================================================================
// Weapon mentioned in Pathfinder 2E Core Rulebook, under:
//	- Chapter 2, page 52, "Halfling Weapon Familiarity"
//	- Chapter 3, page 95, "Attacks" for "Bard"
//	- Chapter 3, page 179, "Attacks" for "Rogue"
UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponShortsword,
	"PF2.Proficiency.Weapon.Shortsword",
	"Character proficiency ranks for Shortswords."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponShortswordUntrained,
	"PF2.Proficiency.Weapon.Shortsword.Untrained",
	"Character is Untrained with Shortswords."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponShortswordTrained,
	"PF2.Proficiency.Weapon.Shortsword.Trained",
	"Character is Trained with Shortswords."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponShortswordExpert,
	"PF2.Proficiency.Weapon.Shortsword.Expert",
	"Character is Expert with Shortswords."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponShortswordMaster,
	"PF2.Proficiency.Weapon.Shortsword.Master",
	"Character is Master with Shortswords."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponShortswordLegendary,
	"PF2.Proficiency.Weapon.Shortsword.Legendary",
	"Character is Legendary with Shortswords."
)

// =====================================================================================================================
// Proficiency Ranks for Slings
// =====================================================================================================================
// Weapon mentioned in Pathfinder 2E Core Rulebook, Chapter 2, page 52, "Halfling Weapon Familiarity".
UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponSling,
	"PF2.Proficiency.Weapon.Sling",
	"Character proficiency ranks for Slings."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponSlingUntrained,
	"PF2.Proficiency.Weapon.Sling.Untrained",
	"Character is Untrained with Slings."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponSlingTrained,
	"PF2.Proficiency.Weapon.Sling.Trained",
	"Character is Trained with Slings."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponSlingExpert,
	"PF2.Proficiency.Weapon.Sling.Expert",
	"Character is Expert with Slings."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponSlingMaster,
	"PF2.Proficiency.Weapon.Sling.Master",
	"Character is Master with Slings."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponSlingLegendary,
	"PF2.Proficiency.Weapon.Sling.Legendary",
	"Character is Legendary with Slings."
)

// =====================================================================================================================
// Proficiency Ranks for Staves
// =====================================================================================================================
// Weapon mentioned in Pathfinder 2E Core Rulebook, under:
//	- Chapter 3, page 203, "Attacks" for "Wizard"
UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponStaff,
	"PF2.Proficiency.Weapon.Staff",
	"Character proficiency ranks for Staves."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponStaffUntrained,
	"PF2.Proficiency.Weapon.Staff.Untrained",
	"Character is Untrained with Staves."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponStaffTrained,
	"PF2.Proficiency.Weapon.Staff.Trained",
	"Character is Trained with Staves."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponStaffExpert,
	"PF2.Proficiency.Weapon.Staff.Expert",
	"Character is Expert with Staves."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponStaffMaster,
	"PF2.Proficiency.Weapon.Staff.Master",
	"Character is Master with Staves."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponStaffLegendary,
	"PF2.Proficiency.Weapon.Staff.Legendary",
	"Character is Legendary with Staves."
)

// =====================================================================================================================
// Proficiency Ranks for Warhammers
// =====================================================================================================================
// Weapon mentioned in Pathfinder 2E Core Rulebook, Chapter 2, page 36, "Dwarven Weapon Familiarity".
UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponWarhammer,
	"PF2.Proficiency.Weapon.Warhammer",
	"Character proficiency ranks for Warhammers."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponWarhammerUntrained,
	"PF2.Proficiency.Weapon.Warhammer.Untrained",
	"Character is Untrained with Warhammers."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponWarhammerTrained,
	"PF2.Proficiency.Weapon.Warhammer.Trained",
	"Character is Trained with Warhammers."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponWarhammerExpert,
	"PF2.Proficiency.Weapon.Warhammer.Expert",
	"Character is Expert with Warhammers."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponWarhammerMaster,
	"PF2.Proficiency.Weapon.Warhammer.Master",
	"Character is Master with Warhammers."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponWarhammerLegendary,
	"PF2.Proficiency.Weapon.Warhammer.Legendary",
	"Character is Legendary with Warhammers."
)

// =====================================================================================================================
// Proficiency Ranks for Whips
// =====================================================================================================================
// Weapon mentioned in Pathfinder 2E Core Rulebook, under:
//	- Chapter 3, page 95, "Attacks" for "Bard"
UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponWhip,
	"PF2.Proficiency.Weapon.Whip",
	"Character proficiency ranks for Whips."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponWhipUntrained,
	"PF2.Proficiency.Weapon.Whip.Untrained",
	"Character is Untrained with Whips."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponWhipTrained,
	"PF2.Proficiency.Weapon.Whip.Trained",
	"Character is Trained with Whips."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponWhipExpert,
	"PF2.Proficiency.Weapon.Whip.Expert",
	"Character is Expert with Whips."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponWhipMaster,
	"PF2.Proficiency.Weapon.Whip.Master",
	"Character is Master with Whips."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyWeaponWhipLegendary,
	"PF2.Proficiency.Weapon.Whip.Legendary",
	"Character is Legendary with Whips."
)

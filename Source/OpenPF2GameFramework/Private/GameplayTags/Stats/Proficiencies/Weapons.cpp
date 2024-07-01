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
	Pf2TagWeaponProficiencyCategoryUnarmedUntrained,
	"WeaponProficiency.Category.Unarmed.Untrained",
	"Character is Untrained with Unarmed attacks."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyCategoryUnarmedTrained,
	"WeaponProficiency.Category.Unarmed.Trained",
	"Character is Trained with Unarmed attacks."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyCategoryUnarmedExpert,
	"WeaponProficiency.Category.Unarmed.Expert",
	"Character is Expert with Unarmed attacks."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyCategoryUnarmedMaster,
	"WeaponProficiency.Category.Unarmed.Master",
	"Character is Master with Unarmed attacks."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyCategoryUnarmedLegendary,
	"WeaponProficiency.Category.Unarmed.Legendary",
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
	Pf2TagWeaponProficiencyCategorySimpleUntrained,
	"WeaponProficiency.Category.Simple.Untrained",
	"Character is Untrained with Simple weapons."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyCategorySimpleTrained,
	"WeaponProficiency.Category.Simple.Trained",
	"Character is Trained with Simple weapons."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyCategorySimpleExpert,
	"WeaponProficiency.Category.Simple.Expert",
	"Character is Expert with Simple weapons."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyCategorySimpleMaster,
	"WeaponProficiency.Category.Simple.Master",
	"Character is Master with Simple weapons."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyCategorySimpleLegendary,
	"WeaponProficiency.Category.Simple.Legendary",
	"Character is Legendary with Simple weapons."
)

// =====================================================================================================================
// Proficiency Ranks for Advanced Weapons
// =====================================================================================================================
// Weapon type mentioned in Pathfinder 2E Core Rulebook under:
//	- Chapter 3, page 141, "Attacks" for "Fighter"
UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyCategoryAdvancedUntrained,
	"WeaponProficiency.Category.Advanced.Untrained",
	"Character is Untrained with Advanced weapons."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyCategoryAdvancedTrained,
	"WeaponProficiency.Category.Advanced.Trained",
	"Character is Trained with Advanced weapons."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyCategoryAdvancedExpert,
	"WeaponProficiency.Category.Advanced.Expert",
	"Character is Expert with Advanced weapons."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyCategoryAdvancedMaster,
	"WeaponProficiency.Category.Advanced.Master",
	"Character is Master with Advanced weapons."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyCategoryAdvancedLegendary,
	"WeaponProficiency.Category.Advanced.Legendary",
	"Character is Legendary with Advanced weapons."
)

// =====================================================================================================================
// Proficiency Ranks for Advanced Dwarf Weapons
// =====================================================================================================================
// From the Pathfinder 2E Core Rulebook, Chapter 2, page 36, "Dwarven Weapon Familiarity":
// "For the purpose of determining your proficiency, [...] advanced dwarf weapons are martial weapons."
UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyCategoryAdvancedDwarfUntrained,
	"WeaponProficiency.Category.AdvancedDwarf.Untrained",
	"Character is Untrained with Advanced Dwarf weapons."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyCategoryAdvancedDwarfTrained,
	"WeaponProficiency.Category.AdvancedDwarf.Trained",
	"Character is Trained with Advanced Dwarf weapons."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyCategoryAdvancedDwarfExpert,
	"WeaponProficiency.Category.AdvancedDwarf.Expert",
	"Character is Expert with Advanced Dwarf weapons."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyCategoryAdvancedDwarfMaster,
	"WeaponProficiency.Category.AdvancedDwarf.Master",
	"Character is Master with Advanced Dwarf weapons."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyCategoryAdvancedDwarfLegendary,
	"WeaponProficiency.Category.AdvancedDwarf.Legendary",
	"Character is Legendary with Advanced Dwarf weapons."
)

// =====================================================================================================================
// Proficiency Ranks for Advanced Elf Weapons
// =====================================================================================================================
// From the Pathfinder 2E Core Rulebook, Chapter 2, page 40, "Elven Weapon Familiarity":
// "For the purpose of determining your proficiency, [...] advanced elf weapons are martial weapons."
UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyCategoryAdvancedElfUntrained,
	"WeaponProficiency.Category.AdvancedElf.Untrained",
	"Character is Untrained with Advanced Elf weapons."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyCategoryAdvancedElfTrained,
	"WeaponProficiency.Category.AdvancedElf.Trained",
	"Character is Trained with Advanced Elf weapons."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyCategoryAdvancedElfExpert,
	"WeaponProficiency.Category.AdvancedElf.Expert",
	"Character is Expert with Advanced Elf weapons."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyCategoryAdvancedElfMaster,
	"WeaponProficiency.Category.AdvancedElf.Master",
	"Character is Master with Advanced Elf weapons."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyCategoryAdvancedElfLegendary,
	"WeaponProficiency.Category.AdvancedElf.Legendary",
	"Character is Legendary with Advanced Elf weapons."
)

// =====================================================================================================================
// Proficiency Ranks for Advanced Gnome Weapons
// =====================================================================================================================
// From the Pathfinder 2E Core Rulebook, Chapter 2, page 44, "Gnome Weapon Familiarity":
// "For the purpose of determining your proficiency, [...] advanced gnome weapons are martial weapons."
UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyCategoryAdvancedGnomeUntrained,
	"WeaponProficiency.Category.AdvancedGnome.Untrained",
	"Character is Untrained with Advanced Gnome weapons."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyCategoryAdvancedGnomeTrained,
	"WeaponProficiency.Category.AdvancedGnome.Trained",
	"Character is Trained with Advanced Gnome weapons."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyCategoryAdvancedGnomeExpert,
	"WeaponProficiency.Category.AdvancedGnome.Expert",
	"Character is Expert with Advanced Gnome weapons."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyCategoryAdvancedGnomeMaster,
	"WeaponProficiency.Category.AdvancedGnome.Master",
	"Character is Master with Advanced Gnome weapons."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyCategoryAdvancedGnomeLegendary,
	"WeaponProficiency.Category.AdvancedGnome.Legendary",
	"Character is Legendary with Advanced Gnome weapons."
)

// =====================================================================================================================
// Proficiency Ranks for Advanced Goblin Weapons
// =====================================================================================================================
// From the Pathfinder 2E Core Rulebook, Chapter 2, page 48, "Goblin Weapon Familiarity":
// "For the purpose of determining your proficiency, [...] advanced goblin weapons are martial weapons."
UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyCategoryAdvancedGoblinUntrained,
	"WeaponProficiency.Category.AdvancedGoblin.Untrained",
	"Character is Untrained with Advanced Goblin weapons."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyCategoryAdvancedGoblinTrained,
	"WeaponProficiency.Category.AdvancedGoblin.Trained",
	"Character is Trained with Advanced Goblin weapons."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyCategoryAdvancedGoblinExpert,
	"WeaponProficiency.Category.AdvancedGoblin.Expert",
	"Character is Expert with Advanced Goblin weapons."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyCategoryAdvancedGoblinMaster,
	"WeaponProficiency.Category.AdvancedGoblin.Master",
	"Character is Master with Advanced Goblin weapons."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyCategoryAdvancedGoblinLegendary,
	"WeaponProficiency.Category.AdvancedGoblin.Legendary",
	"Character is Legendary with Advanced Goblin weapons."
)

// =====================================================================================================================
// Proficiency Ranks for Advanced Halfling Weapons
// =====================================================================================================================
// From the Pathfinder 2E Core Rulebook, Chapter 2, page 52, "Halfling Weapon Familiarity":
// "For the purpose of determining your proficiency, [...] advanced halfling weapons are martial weapons."
UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyCategoryAdvancedHalflingUntrained,
	"WeaponProficiency.Category.AdvancedHalfling.Untrained",
	"Character is Untrained with Advanced Halfling weapons."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyCategoryAdvancedHalflingTrained,
	"WeaponProficiency.Category.AdvancedHalfling.Trained",
	"Character is Trained with Advanced Halfling weapons."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyCategoryAdvancedHalflingExpert,
	"WeaponProficiency.Category.AdvancedHalfling.Expert",
	"Character is Expert with Advanced Halfling weapons."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyCategoryAdvancedHalflingMaster,
	"WeaponProficiency.Category.AdvancedHalfling.Master",
	"Character is Master with Advanced Halfling weapons."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyCategoryAdvancedHalflingLegendary,
	"WeaponProficiency.Category.AdvancedHalfling.Legendary",
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
	Pf2TagWeaponProficiencyCategoryMartialUntrained,
	"WeaponProficiency.Category.Martial.Untrained",
	"Character is Untrained with Martial weapons."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyCategoryMartialTrained,
	"WeaponProficiency.Category.Martial.Trained",
	"Character is Trained with Martial weapons."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyCategoryMartialExpert,
	"WeaponProficiency.Category.Martial.Expert",
	"Character is Expert with Martial weapons."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyCategoryMartialMaster,
	"WeaponProficiency.Category.Martial.Master",
	"Character is Master with Martial weapons."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyCategoryMartialLegendary,
	"WeaponProficiency.Category.Martial.Legendary",
	"Character is Legendary with Martial weapons."
)

// =====================================================================================================================
// Proficiency Ranks for Martial Dwarf Weapons
// =====================================================================================================================
// From the Pathfinder 2E Core Rulebook, Chapter 2, page 36, "Dwarven Weapon Familiarity":
// "For the purpose of determining your proficiency, martial dwarf weapons are simple weapons..."
UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyCategoryMartialDwarfUntrained,
	"WeaponProficiency.Category.MartialDwarf.Untrained",
	"Character is Untrained with Martial Dwarf weapons."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyCategoryMartialDwarfTrained,
	"WeaponProficiency.Category.MartialDwarf.Trained",
	"Character is Trained with Martial Dwarf weapons."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyCategoryMartialDwarfExpert,
	"WeaponProficiency.Category.MartialDwarf.Expert",
	"Character is Expert with Martial Dwarf weapons."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyCategoryMartialDwarfMaster,
	"WeaponProficiency.Category.MartialDwarf.Master",
	"Character is Master with Martial Dwarf weapons."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyCategoryMartialDwarfLegendary,
	"WeaponProficiency.Category.MartialDwarf.Legendary",
	"Character is Legendary with Martial Dwarf weapons."
)

// =====================================================================================================================
// Proficiency Ranks for Martial Elf Weapons
// =====================================================================================================================
// From the Pathfinder 2E Core Rulebook, Chapter 2, page 40, "Elven Weapon Familiarity":
// "For the purpose of determining your proficiency, martial elf weapons are simple weapons..."
UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyCategoryMartialElfUntrained,
	"WeaponProficiency.Category.MartialElf.Untrained",
	"Character is Untrained with Martial Elf weapons."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyCategoryMartialElfTrained,
	"WeaponProficiency.Category.MartialElf.Trained",
	"Character is Trained with Martial Elf weapons."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyCategoryMartialElfExpert,
	"WeaponProficiency.Category.MartialElf.Expert",
	"Character is Expert with Martial Elf weapons."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyCategoryMartialElfMaster,
	"WeaponProficiency.Category.MartialElf.Master",
	"Character is Master with Martial Elf weapons."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyCategoryMartialElfLegendary,
	"WeaponProficiency.Category.MartialElf.Legendary",
	"Character is Legendary with Martial Elf weapons."
)

// =====================================================================================================================
// Proficiency Ranks for Martial Gnome Weapons
// =====================================================================================================================
// From the Pathfinder 2E Core Rulebook, Chapter 2, page 44, "Gnome Weapon Familiarity":
// "For the purpose of determining your proficiency, martial gnome weapons are simple weapons..."
UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyCategoryMartialGnomeUntrained,
	"WeaponProficiency.Category.MartialGnome.Untrained",
	"Character is Untrained with Martial Gnome weapons."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyCategoryMartialGnomeTrained,
	"WeaponProficiency.Category.MartialGnome.Trained",
	"Character is Trained with Martial Gnome weapons."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyCategoryMartialGnomeExpert,
	"WeaponProficiency.Category.MartialGnome.Expert",
	"Character is Expert with Martial Gnome weapons."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyCategoryMartialGnomeMaster,
	"WeaponProficiency.Category.MartialGnome.Master",
	"Character is Master with Martial Gnome weapons."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyCategoryMartialGnomeLegendary,
	"WeaponProficiency.Category.MartialGnome.Legendary",
	"Character is Legendary with Martial Gnome weapons."
)

// =====================================================================================================================
// Proficiency Ranks for Martial Goblin Weapons
// =====================================================================================================================
// From the Pathfinder 2E Core Rulebook, Chapter 2, page 48, "Goblin Weapon Familiarity":
// "For the purpose of determining your proficiency, martial goblin weapons are simple weapons..."
UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyCategoryMartialGoblinUntrained,
	"WeaponProficiency.Category.MartialGoblin.Untrained",
	"Character is Untrained with Martial Goblin weapons."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyCategoryMartialGoblinTrained,
	"WeaponProficiency.Category.MartialGoblin.Trained",
	"Character is Trained with Martial Goblin weapons."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyCategoryMartialGoblinExpert,
	"WeaponProficiency.Category.MartialGoblin.Expert",
	"Character is Expert with Martial Goblin weapons."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyCategoryMartialGoblinMaster,
	"WeaponProficiency.Category.MartialGoblin.Master",
	"Character is Master with Martial Goblin weapons."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyCategoryMartialGoblinLegendary,
	"WeaponProficiency.Category.MartialGoblin.Legendary",
	"Character is Legendary with Martial Goblin weapons."
)

// =====================================================================================================================
// Proficiency Ranks for Martial Halfling Weapons
// =====================================================================================================================
// From the Pathfinder 2E Core Rulebook, Chapter 2, page 52, "Halfling Weapon Familiarity":
// "For the purpose of determining your proficiency, martial halfling weapons are simple weapons..."
UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyCategoryMartialHalflingUntrained,
	"WeaponProficiency.Category.MartialHalfling.Untrained",
	"Character is Untrained with Martial Halfling weapons."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyCategoryMartialHalflingTrained,
	"WeaponProficiency.Category.MartialHalfling.Trained",
	"Character is Trained with Martial Halfling weapons."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyCategoryMartialHalflingExpert,
	"WeaponProficiency.Category.MartialHalfling.Expert",
	"Character is Expert with Martial Halfling weapons."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyCategoryMartialHalflingMaster,
	"WeaponProficiency.Category.MartialHalfling.Master",
	"Character is Master with Martial Halfling weapons."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyCategoryMartialHalflingLegendary,
	"WeaponProficiency.Category.MartialHalfling.Legendary",
	"Character is Legendary with Martial Halfling weapons."
)

// =====================================================================================================================
// Proficiency Ranks for Alchemical Bombs
// =====================================================================================================================
// Weapon type mentioned in Pathfinder 2E Core Rulebook under:
//	- Chapter 3, page 71, "Attacks" for "Alchemist"
UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyAlchemicalBombUntrained,
	"WeaponProficiency.AlchemicalBomb.Untrained",
	"Character is Untrained with Alchemical Bombs."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyAlchemicalBombTrained,
	"WeaponProficiency.AlchemicalBomb.Trained",
	"Character is Trained with Alchemical Bombs."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyAlchemicalBombExpert,
	"WeaponProficiency.AlchemicalBomb.Expert",
	"Character is Expert with Alchemical Bombs."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyAlchemicalBombMaster,
	"WeaponProficiency.AlchemicalBomb.Master",
	"Character is Master with Alchemical Bombs."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyAlchemicalBombLegendary,
	"WeaponProficiency.AlchemicalBomb.Legendary",
	"Character is Legendary with Alchemical Bombs."
)

// =====================================================================================================================
// Proficiency Ranks for Battle Axes
// =====================================================================================================================
// Weapon mentioned in Pathfinder 2E Core Rulebook, Chapter 2, page 36, "Dwarven Weapon Familiarity".
UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyBattleAxeUntrained,
	"WeaponProficiency.BattleAxe.Untrained",
	"Character is Untrained with Battle Axes."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyBattleAxeTrained,
	"WeaponProficiency.BattleAxe.Trained",
	"Character is Trained with Battle Axes."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyBattleAxeExpert,
	"WeaponProficiency.BattleAxe.Expert",
	"Character is Expert with Battle Axes."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyBattleAxeMaster,
	"WeaponProficiency.BattleAxe.Master",
	"Character is Master with Battle Axes."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyBattleAxeLegendary,
	"WeaponProficiency.BattleAxe.Legendary",
	"Character is Legendary with Battle Axes."
)

// =====================================================================================================================
// Proficiency Ranks for Clubs
// =====================================================================================================================
// Weapon mentioned in Pathfinder 2E Core Rulebook, under:
//	- Chapter 3, page 203, "Attacks" for "Wizard"
UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyClubUntrained,
	"WeaponProficiency.Club.Untrained",
	"Character is Untrained with Clubs."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyClubTrained,
	"WeaponProficiency.Club.Trained",
	"Character is Trained with Clubs."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyClubExpert,
	"WeaponProficiency.Club.Expert",
	"Character is Expert with Clubs."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyClubMaster,
	"WeaponProficiency.Club.Master",
	"Character is Master with Clubs."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyClubLegendary,
	"WeaponProficiency.Club.Legendary",
	"Character is Legendary with Clubs."
)

// =====================================================================================================================
// Proficiency Ranks for Composite Longbows
// =====================================================================================================================
// Weapon mentioned in Pathfinder 2E Core Rulebook, Chapter 2, page 40, "Elven Weapon Familiarity".
UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyCompositeLongbowUntrained,
	"WeaponProficiency.CompositeLongbow.Untrained",
	"Character is Untrained with Composite Longbows."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyCompositeLongbowTrained,
	"WeaponProficiency.CompositeLongbow.Trained",
	"Character is Trained with Composite Longbows."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyCompositeLongbowExpert,
	"WeaponProficiency.CompositeLongbow.Expert",
	"Character is Expert with Composite Longbows."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyCompositeLongbowMaster,
	"WeaponProficiency.CompositeLongbow.Master",
	"Character is Master with Composite Longbows."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyCompositeLongbowLegendary,
	"WeaponProficiency.CompositeLongbow.Legendary",
	"Character is Legendary with Composite Longbows."
)

// =====================================================================================================================
// Proficiency Ranks for Composite Shortbows
// =====================================================================================================================
// Weapon mentioned in Pathfinder 2E Core Rulebook, Chapter 2, page 40, "Elven Weapon Familiarity".
UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyCompositeShortbowUntrained,
	"WeaponProficiency.CompositeShortbow.Untrained",
	"Character is Untrained with Composite Shortbows."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyCompositeShortbowTrained,
	"WeaponProficiency.CompositeShortbow.Trained",
	"Character is Trained with Composite Shortbows."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyCompositeShortbowExpert,
	"WeaponProficiency.CompositeShortbow.Expert",
	"Character is Expert with Composite Shortbows."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyCompositeShortbowMaster,
	"WeaponProficiency.CompositeShortbow.Master",
	"Character is Master with Composite Shortbows."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyCompositeShortbowLegendary,
	"WeaponProficiency.CompositeShortbow.Legendary",
	"Character is Legendary with Composite Shortbows."
)

// =====================================================================================================================
// Proficiency Ranks for Crossbows
// =====================================================================================================================
// Weapon mentioned in Pathfinder 2E Core Rulebook, under:
//	- Chapter 3, page 203, "Attacks" for "Wizard"
UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyCrossbowUntrained,
	"WeaponProficiency.Crossbow.Untrained",
	"Character is Untrained with Crossbows."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyCrossbowTrained,
	"WeaponProficiency.Crossbow.Trained",
	"Character is Trained with Crossbows."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyCrossbowExpert,
	"WeaponProficiency.Crossbow.Expert",
	"Character is Expert with Crossbows."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyCrossbowMaster,
	"WeaponProficiency.Crossbow.Master",
	"Character is Master with Crossbows."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyCrossbowLegendary,
	"WeaponProficiency.Crossbow.Legendary",
	"Character is Legendary with Crossbows."
)

// =====================================================================================================================
// Proficiency Ranks for Daggers
// =====================================================================================================================
// Weapon mentioned in Pathfinder 2E Core Rulebook, under:
//	- Chapter 3, page 203, "Attacks" for "Wizard"
UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyDaggerUntrained,
	"WeaponProficiency.Dagger.Untrained",
	"Character is Untrained with Daggers."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyDaggerTrained,
	"WeaponProficiency.Dagger.Trained",
	"Character is Trained with Daggers."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyDaggerExpert,
	"WeaponProficiency.Dagger.Expert",
	"Character is Expert with Daggers."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyDaggerMaster,
	"WeaponProficiency.Dagger.Master",
	"Character is Master with Daggers."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyDaggerLegendary,
	"WeaponProficiency.Dagger.Legendary",
	"Character is Legendary with Daggers."
)

// =====================================================================================================================
// Proficiency Ranks for Dogslicers
// =====================================================================================================================
// Weapon mentioned in Pathfinder 2E Core Rulebook, Chapter 2, page 48, "Goblin Weapon Familiarity".
UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyDogslicerUntrained,
	"WeaponProficiency.Dogslicer.Untrained",
	"Character is Untrained with Dogslicers."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyDogslicerTrained,
	"WeaponProficiency.Dogslicer.Trained",
	"Character is Trained with Dogslicers."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyDogslicerExpert,
	"WeaponProficiency.Dogslicer.Expert",
	"Character is Expert with Dogslicers."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyDogslicerMaster,
	"WeaponProficiency.Dogslicer.Master",
	"Character is Master with Dogslicers."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyDogslicerLegendary,
	"WeaponProficiency.Dogslicer.Legendary",
	"Character is Legendary with Dogslicers."
)

// =====================================================================================================================
// Proficiency Ranks for Falchions
// =====================================================================================================================
// Weapon mentioned in Pathfinder 2E Core Rulebook, Chapter 2, page 58, "Orc Weapon Familiarity".
UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyFalchionUntrained,
	"WeaponProficiency.Falchion.Untrained",
	"Character is Untrained with Falchions."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyFalchionTrained,
	"WeaponProficiency.Falchion.Trained",
	"Character is Trained with Falchions."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyFalchionExpert,
	"WeaponProficiency.Falchion.Expert",
	"Character is Expert with Falchions."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyFalchionMaster,
	"WeaponProficiency.Falchion.Master",
	"Character is Master with Falchions."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyFalchionLegendary,
	"WeaponProficiency.Falchion.Legendary",
	"Character is Legendary with Falchions."
)

// =====================================================================================================================
// Proficiency Ranks for Glaives
// =====================================================================================================================
// Weapon mentioned in Pathfinder 2E Core Rulebook, Chapter 2, page 44, "Gnome Weapon Familiarity".
UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyGlaiveUntrained,
	"WeaponProficiency.Glaive.Untrained",
	"Character is Untrained with Glaives."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyGlaiveTrained,
	"WeaponProficiency.Glaive.Trained",
	"Character is Trained with Glaives."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyGlaiveExpert,
	"WeaponProficiency.Glaive.Expert",
	"Character is Expert with Glaives."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyGlaiveMaster,
	"WeaponProficiency.Glaive.Master",
	"Character is Master with Glaives."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyGlaiveLegendary,
	"WeaponProficiency.Glaive.Legendary",
	"Character is Legendary with Glaives."
)

// =====================================================================================================================
// Proficiency Ranks for Greataxes
// =====================================================================================================================
// Weapon mentioned in Pathfinder 2E Core Rulebook, Chapter 2, page 58, "Orc Weapon Familiarity".
UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyGreataxeUntrained,
	"WeaponProficiency.Greataxe.Untrained",
	"Character is Untrained with Greataxes."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyGreataxeTrained,
	"WeaponProficiency.Greataxe.Trained",
	"Character is Trained with Greataxes."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyGreataxeExpert,
	"WeaponProficiency.Greataxe.Expert",
	"Character is Expert with Greataxes."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyGreataxeMaster,
	"WeaponProficiency.Greataxe.Master",
	"Character is Master with Greataxes."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyGreataxeLegendary,
	"WeaponProficiency.Greataxe.Legendary",
	"Character is Legendary with Greataxes."
)

// =====================================================================================================================
// Proficiency Ranks for Halfling Sling Staves
// =====================================================================================================================
// Weapon mentioned in Pathfinder 2E Core Rulebook, Chapter 2, page 52, "Halfling Weapon Familiarity".
UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyHalflingSlingStaffUntrained,
	"WeaponProficiency.HalflingSlingStaff.Untrained",
	"Character is Untrained with Halfling Sling Staves."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyHalflingSlingStaffTrained,
	"WeaponProficiency.HalflingSlingStaff.Trained",
	"Character is Trained with Halfling Sling Staves."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyHalflingSlingStaffExpert,
	"WeaponProficiency.HalflingSlingStaff.Expert",
	"Character is Expert with Halfling Sling Staves."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyHalflingSlingStaffMaster,
	"WeaponProficiency.HalflingSlingStaff.Master",
	"Character is Master with Halfling Sling Staves."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyHalflingSlingStaffLegendary,
	"WeaponProficiency.HalflingSlingStaff.Legendary",
	"Character is Legendary with Halfling Sling Staves."
)

// =====================================================================================================================
// Proficiency Ranks for Heavy Crossbows
// =====================================================================================================================
// Weapon mentioned in Pathfinder 2E Core Rulebook, under:
//	- Chapter 3, page 203, "Attacks" for "Wizard"
UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyHeavyCrossbowUntrained,
	"WeaponProficiency.HeavyCrossbow.Untrained",
	"Character is Untrained with Heavy Crossbows."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyHeavyCrossbowTrained,
	"WeaponProficiency.HeavyCrossbow.Trained",
	"Character is Trained with Heavy Crossbows."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyHeavyCrossbowExpert,
	"WeaponProficiency.HeavyCrossbow.Expert",
	"Character is Expert with Heavy Crossbows."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyHeavyCrossbowMaster,
	"WeaponProficiency.HeavyCrossbow.Master",
	"Character is Master with Heavy Crossbows."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyHeavyCrossbowLegendary,
	"WeaponProficiency.HeavyCrossbow.Legendary",
	"Character is Legendary with Heavy Crossbows."
)

// =====================================================================================================================
// Proficiency Ranks for Horsechoppers
// =====================================================================================================================
// Weapon mentioned in Pathfinder 2E Core Rulebook, Chapter 2, page 48, "Goblin Weapon Familiarity".
UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyHorsechopperUntrained,
	"WeaponProficiency.Horsechopper.Untrained",
	"Character is Untrained with Horsechoppers."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyHorsechopperTrained,
	"WeaponProficiency.Horsechopper.Trained",
	"Character is Trained with Horsechoppers."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyHorsechopperExpert,
	"WeaponProficiency.Horsechopper.Expert",
	"Character is Expert with Horsechoppers."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyHorsechopperMaster,
	"WeaponProficiency.Horsechopper.Master",
	"Character is Master with Horsechoppers."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyHorsechopperLegendary,
	"WeaponProficiency.Horsechopper.Legendary",
	"Character is Legendary with Horsechoppers."
)

// =====================================================================================================================
// Proficiency Ranks for Kukris
// =====================================================================================================================
// Weapon mentioned in Pathfinder 2E Core Rulebook, Chapter 2, page 44, "Gnome Weapon Familiarity".
UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyKukriUntrained,
	"WeaponProficiency.Kukri.Untrained",
	"Character is Untrained with Kukris."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyKukriTrained,
	"WeaponProficiency.Kukri.Trained",
	"Character is Trained with Kukris."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyKukriExpert,
	"WeaponProficiency.Kukri.Expert",
	"Character is Expert with Kukris."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyKukriMaster,
	"WeaponProficiency.Kukri.Master",
	"Character is Master with Kukris."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyKukriLegendary,
	"WeaponProficiency.Kukri.Legendary",
	"Character is Legendary with Kukris."
)

// =====================================================================================================================
// Proficiency Ranks for Longbows
// =====================================================================================================================
// Weapon mentioned in Pathfinder 2E Core Rulebook, Chapter 2, page 40, "Elven Weapon Familiarity".
UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyLongbowUntrained,
	"WeaponProficiency.Longbow.Untrained",
	"Character is Untrained with Longbows."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyLongbowTrained,
	"WeaponProficiency.Longbow.Trained",
	"Character is Trained with Longbows."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyLongbowExpert,
	"WeaponProficiency.Longbow.Expert",
	"Character is Expert with Longbows."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyLongbowMaster,
	"WeaponProficiency.Longbow.Master",
	"Character is Master with Longbows."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyLongbowLegendary,
	"WeaponProficiency.Longbow.Legendary",
	"Character is Legendary with Longbows."
)

// =====================================================================================================================
// Proficiency Ranks for Longswords
// =====================================================================================================================
// Weapon mentioned in Pathfinder 2E Core Rulebook, under:
//	- Chapter 2, page 40, "Elven Weapon Familiarity"
//	- Chapter 3, page 95, "Attacks" for "Bard"
UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyLongswordUntrained,
	"WeaponProficiency.Longsword.Untrained",
	"Character is Untrained with Longswords."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyLongswordTrained,
	"WeaponProficiency.Longsword.Trained",
	"Character is Trained with Longswords."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyLongswordExpert,
	"WeaponProficiency.Longsword.Expert",
	"Character is Expert with Longswords."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyLongswordMaster,
	"WeaponProficiency.Longsword.Master",
	"Character is Master with Longswords."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyLongswordLegendary,
	"WeaponProficiency.Longsword.Legendary",
	"Character is Legendary with Longswords."
)

// =====================================================================================================================
// Proficiency Ranks for Picks
// =====================================================================================================================
// Weapon mentioned in Pathfinder 2E Core Rulebook, Chapter 2, page 36, "Dwarven Weapon Familiarity".
UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyPickUntrained,
	"WeaponProficiency.Pick.Untrained",
	"Character is Untrained with Picks."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyPickTrained,
	"WeaponProficiency.Pick.Trained",
	"Character is Trained with Picks."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyPickExpert,
	"WeaponProficiency.Pick.Expert",
	"Character is Expert with Picks."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyPickMaster,
	"WeaponProficiency.Pick.Master",
	"Character is Master with Picks."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyPickLegendary,
	"WeaponProficiency.Pick.Legendary",
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
	Pf2TagWeaponProficiencyRapierUntrained,
	"WeaponProficiency.Rapier.Untrained",
	"Character is Untrained with Rapiers."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyRapierTrained,
	"WeaponProficiency.Rapier.Trained",
	"Character is Trained with Rapiers."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyRapierExpert,
	"WeaponProficiency.Rapier.Expert",
	"Character is Expert with Rapiers."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyRapierMaster,
	"WeaponProficiency.Rapier.Master",
	"Character is Master with Rapiers."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyRapierLegendary,
	"WeaponProficiency.Rapier.Legendary",
	"Character is Legendary with Rapiers."
)

// =====================================================================================================================
// Proficiency Ranks for Saps
// =====================================================================================================================
// Weapon mentioned in Pathfinder 2E Core Rulebook, under:
//	- Chapter 3, page 95, "Attacks" for "Bard"
//	- Chapter 3, page 179, "Attacks" for "Rogue"
UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencySapUntrained,
	"WeaponProficiency.Sap.Untrained",
	"Character is Untrained with Saps."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencySapTrained,
	"WeaponProficiency.Sap.Trained",
	"Character is Trained with Saps."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencySapExpert,
	"WeaponProficiency.Sap.Expert",
	"Character is Expert with Saps."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencySapMaster,
	"WeaponProficiency.Sap.Master",
	"Character is Master with Saps."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencySapLegendary,
	"WeaponProficiency.Sap.Legendary",
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
	Pf2TagWeaponProficiencyShortbowUntrained,
	"WeaponProficiency.Shortbow.Untrained",
	"Character is Untrained with Shortbows."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyShortbowTrained,
	"WeaponProficiency.Shortbow.Trained",
	"Character is Trained with Shortbows."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyShortbowExpert,
	"WeaponProficiency.Shortbow.Expert",
	"Character is Expert with Shortbows."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyShortbowMaster,
	"WeaponProficiency.Shortbow.Master",
	"Character is Master with Shortbows."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyShortbowLegendary,
	"WeaponProficiency.Shortbow.Legendary",
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
	Pf2TagWeaponProficiencyShortswordUntrained,
	"WeaponProficiency.Shortsword.Untrained",
	"Character is Untrained with Shortswords."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyShortswordTrained,
	"WeaponProficiency.Shortsword.Trained",
	"Character is Trained with Shortswords."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyShortswordExpert,
	"WeaponProficiency.Shortsword.Expert",
	"Character is Expert with Shortswords."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyShortswordMaster,
	"WeaponProficiency.Shortsword.Master",
	"Character is Master with Shortswords."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyShortswordLegendary,
	"WeaponProficiency.Shortsword.Legendary",
	"Character is Legendary with Shortswords."
)

// =====================================================================================================================
// Proficiency Ranks for Slings
// =====================================================================================================================
// Weapon mentioned in Pathfinder 2E Core Rulebook, Chapter 2, page 52, "Halfling Weapon Familiarity".
UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencySlingUntrained,
	"WeaponProficiency.Sling.Untrained",
	"Character is Untrained with Slings."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencySlingTrained,
	"WeaponProficiency.Sling.Trained",
	"Character is Trained with Slings."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencySlingExpert,
	"WeaponProficiency.Sling.Expert",
	"Character is Expert with Slings."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencySlingMaster,
	"WeaponProficiency.Sling.Master",
	"Character is Master with Slings."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencySlingLegendary,
	"WeaponProficiency.Sling.Legendary",
	"Character is Legendary with Slings."
)

// =====================================================================================================================
// Proficiency Ranks for Staves
// =====================================================================================================================
// Weapon mentioned in Pathfinder 2E Core Rulebook, under:
//	- Chapter 3, page 203, "Attacks" for "Wizard"
UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyStaffUntrained,
	"WeaponProficiency.Staff.Untrained",
	"Character is Untrained with Staves."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyStaffTrained,
	"WeaponProficiency.Staff.Trained",
	"Character is Trained with Staves."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyStaffExpert,
	"WeaponProficiency.Staff.Expert",
	"Character is Expert with Staves."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyStaffMaster,
	"WeaponProficiency.Staff.Master",
	"Character is Master with Staves."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyStaffLegendary,
	"WeaponProficiency.Staff.Legendary",
	"Character is Legendary with Staves."
)

// =====================================================================================================================
// Proficiency Ranks for Warhammers
// =====================================================================================================================
// Weapon mentioned in Pathfinder 2E Core Rulebook, Chapter 2, page 36, "Dwarven Weapon Familiarity".
UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyWarhammerUntrained,
	"WeaponProficiency.Warhammer.Untrained",
	"Character is Untrained with Warhammers."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyWarhammerTrained,
	"WeaponProficiency.Warhammer.Trained",
	"Character is Trained with Warhammers."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyWarhammerExpert,
	"WeaponProficiency.Warhammer.Expert",
	"Character is Expert with Warhammers."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyWarhammerMaster,
	"WeaponProficiency.Warhammer.Master",
	"Character is Master with Warhammers."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyWarhammerLegendary,
	"WeaponProficiency.Warhammer.Legendary",
	"Character is Legendary with Warhammers."
)

// =====================================================================================================================
// Proficiency Ranks for Whips
// =====================================================================================================================
// Weapon mentioned in Pathfinder 2E Core Rulebook, under:
//	- Chapter 3, page 95, "Attacks" for "Bard"
UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyWhipUntrained,
	"WeaponProficiency.Whip.Untrained",
	"Character is Untrained with Whips."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyWhipTrained,
	"WeaponProficiency.Whip.Trained",
	"Character is Trained with Whips."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyWhipExpert,
	"WeaponProficiency.Whip.Expert",
	"Character is Expert with Whips."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyWhipMaster,
	"WeaponProficiency.Whip.Master",
	"Character is Master with Whips."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagWeaponProficiencyWhipLegendary,
	"WeaponProficiency.Whip.Legendary",
	"Character is Legendary with Whips."
)

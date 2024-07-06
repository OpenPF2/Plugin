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

#pragma once

#include <NativeGameplayTags.h>

// =====================================================================================================================
// Proficiency Ranks for Weapons
// =====================================================================================================================
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeapon)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponCategory)

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
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponCategoryUnarmed)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponCategoryUnarmedUntrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponCategoryUnarmedTrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponCategoryUnarmedExpert)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponCategoryUnarmedMaster)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponCategoryUnarmedLegendary)

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
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponCategorySimple)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponCategorySimpleUntrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponCategorySimpleTrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponCategorySimpleExpert)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponCategorySimpleMaster)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponCategorySimpleLegendary)

// =====================================================================================================================
// Proficiency Ranks for Advanced Weapons
// =====================================================================================================================
// Weapon type mentioned in Pathfinder 2E Core Rulebook under:
//	- Chapter 3, page 141, "Attacks" for "Fighter"
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponCategoryAdvanced)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponCategoryAdvancedUntrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponCategoryAdvancedTrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponCategoryAdvancedExpert)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponCategoryAdvancedMaster)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponCategoryAdvancedLegendary)

// =====================================================================================================================
// Proficiency Ranks for Advanced Dwarf Weapons
// =====================================================================================================================
// From the Pathfinder 2E Core Rulebook, Chapter 2, page 36, "Dwarven Weapon Familiarity":
// "For the purpose of determining your proficiency, [...] advanced dwarf weapons are martial weapons."
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponCategoryAdvancedDwarf)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponCategoryAdvancedDwarfUntrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponCategoryAdvancedDwarfTrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponCategoryAdvancedDwarfExpert)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponCategoryAdvancedDwarfMaster)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponCategoryAdvancedDwarfLegendary)

// =====================================================================================================================
// Proficiency Ranks for Advanced Elf Weapons
// =====================================================================================================================
// From the Pathfinder 2E Core Rulebook, Chapter 2, page 40, "Elven Weapon Familiarity":
// "For the purpose of determining your proficiency, [...] advanced elf weapons are martial weapons."
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponCategoryAdvancedElf)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponCategoryAdvancedElfUntrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponCategoryAdvancedElfTrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponCategoryAdvancedElfExpert)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponCategoryAdvancedElfMaster)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponCategoryAdvancedElfLegendary)

// =====================================================================================================================
// Proficiency Ranks for Advanced Gnome Weapons
// =====================================================================================================================
// From the Pathfinder 2E Core Rulebook, Chapter 2, page 44, "Gnome Weapon Familiarity":
// "For the purpose of determining your proficiency, [...] advanced gnome weapons are martial weapons."
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponCategoryAdvancedGnome)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponCategoryAdvancedGnomeUntrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponCategoryAdvancedGnomeTrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponCategoryAdvancedGnomeExpert)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponCategoryAdvancedGnomeMaster)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponCategoryAdvancedGnomeLegendary)

// =====================================================================================================================
// Proficiency Ranks for Advanced Goblin Weapons
// =====================================================================================================================
// From the Pathfinder 2E Core Rulebook, Chapter 2, page 48, "Goblin Weapon Familiarity":
// "For the purpose of determining your proficiency, [...] advanced goblin weapons are martial weapons."
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponCategoryAdvancedGoblin)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponCategoryAdvancedGoblinUntrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponCategoryAdvancedGoblinTrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponCategoryAdvancedGoblinExpert)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponCategoryAdvancedGoblinMaster)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponCategoryAdvancedGoblinLegendary)

// =====================================================================================================================
// Proficiency Ranks for Advanced Halfling Weapons
// =====================================================================================================================
// From the Pathfinder 2E Core Rulebook, Chapter 2, page 52, "Halfling Weapon Familiarity":
// "For the purpose of determining your proficiency, [...] advanced halfling weapons are martial weapons."
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponCategoryAdvancedHalfling)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponCategoryAdvancedHalflingUntrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponCategoryAdvancedHalflingTrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponCategoryAdvancedHalflingExpert)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponCategoryAdvancedHalflingMaster)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponCategoryAdvancedHalflingLegendary)

// =====================================================================================================================
// Proficiency Ranks for Martial Weapons
// =====================================================================================================================
// Weapon type mentioned in Pathfinder 2E Core Rulebook under:
//	- Chapter 3, page 83, "Attacks" for "Barbarian"
//	- Chapter 3, page 105, "Attacks" for "Champion"
//	- Chapter 3, page 141, "Attacks" for "Fighter"
//	- Chapter 3, page 167, "Attacks" for "Ranger"
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponCategoryMartial)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponCategoryMartialUntrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponCategoryMartialTrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponCategoryMartialExpert)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponCategoryMartialMaster)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponCategoryMartialLegendary)

// =====================================================================================================================
// Proficiency Ranks for Martial Dwarf Weapons
// =====================================================================================================================
// From the Pathfinder 2E Core Rulebook, Chapter 2, page 36, "Dwarven Weapon Familiarity":
// "For the purpose of determining your proficiency, martial dwarf weapons are simple weapons..."
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponCategoryMartialDwarf)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponCategoryMartialDwarfUntrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponCategoryMartialDwarfTrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponCategoryMartialDwarfExpert)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponCategoryMartialDwarfMaster)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponCategoryMartialDwarfLegendary)

// =====================================================================================================================
// Proficiency Ranks for Martial Elf Weapons
// =====================================================================================================================
// From the Pathfinder 2E Core Rulebook, Chapter 2, page 40, "Elven Weapon Familiarity":
// "For the purpose of determining your proficiency, martial elf weapons are simple weapons..."
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponCategoryMartialElf)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponCategoryMartialElfUntrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponCategoryMartialElfTrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponCategoryMartialElfExpert)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponCategoryMartialElfMaster)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponCategoryMartialElfLegendary)

// =====================================================================================================================
// Proficiency Ranks for Martial Gnome Weapons
// =====================================================================================================================
// From the Pathfinder 2E Core Rulebook, Chapter 2, page 44, "Gnome Weapon Familiarity":
// "For the purpose of determining your proficiency, martial gnome weapons are simple weapons..."
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponCategoryMartialGnome)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponCategoryMartialGnomeUntrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponCategoryMartialGnomeTrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponCategoryMartialGnomeExpert)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponCategoryMartialGnomeMaster)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponCategoryMartialGnomeLegendary)

// =====================================================================================================================
// Proficiency Ranks for Martial Goblin Weapons
// =====================================================================================================================
// From the Pathfinder 2E Core Rulebook, Chapter 2, page 48, "Goblin Weapon Familiarity":
// "For the purpose of determining your proficiency, martial goblin weapons are simple weapons..."
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponCategoryMartialGoblin)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponCategoryMartialGoblinUntrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponCategoryMartialGoblinTrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponCategoryMartialGoblinExpert)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponCategoryMartialGoblinMaster)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponCategoryMartialGoblinLegendary)

// =====================================================================================================================
// Proficiency Ranks for Martial Halfling Weapons
// =====================================================================================================================
// From the Pathfinder 2E Core Rulebook, Chapter 2, page 52, "Halfling Weapon Familiarity":
// "For the purpose of determining your proficiency, martial halfling weapons are simple weapons..."
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponCategoryMartialHalfling)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponCategoryMartialHalflingUntrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponCategoryMartialHalflingTrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponCategoryMartialHalflingExpert)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponCategoryMartialHalflingMaster)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponCategoryMartialHalflingLegendary)

// =====================================================================================================================
// Proficiency Ranks for Alchemical Bombs
// =====================================================================================================================
// Weapon type mentioned in Pathfinder 2E Core Rulebook under:
//	- Chapter 3, page 71, "Attacks" for "Alchemist"
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponAlchemicalBomb)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponAlchemicalBombUntrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponAlchemicalBombTrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponAlchemicalBombExpert)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponAlchemicalBombMaster)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponAlchemicalBombLegendary)

// =====================================================================================================================
// Proficiency Ranks for Battle Axes
// =====================================================================================================================
// Weapon mentioned in Pathfinder 2E Core Rulebook, Chapter 2, page 36, "Dwarven Weapon Familiarity".
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponBattleAxe)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponBattleAxeUntrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponBattleAxeTrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponBattleAxeExpert)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponBattleAxeMaster)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponBattleAxeLegendary)

// =====================================================================================================================
// Proficiency Ranks for Clubs
// =====================================================================================================================
// Weapon mentioned in Pathfinder 2E Core Rulebook, under:
//	- Chapter 3, page 203, "Attacks" for "Wizard"
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponClub)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponClubUntrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponClubTrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponClubExpert)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponClubMaster)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponClubLegendary)

// =====================================================================================================================
// Proficiency Ranks for Composite Longbows
// =====================================================================================================================
// Weapon mentioned in Pathfinder 2E Core Rulebook, Chapter 2, page 40, "Elven Weapon Familiarity".
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponCompositeLongbow)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponCompositeLongbowUntrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponCompositeLongbowTrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponCompositeLongbowExpert)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponCompositeLongbowMaster)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponCompositeLongbowLegendary)

// =====================================================================================================================
// Proficiency Ranks for Composite Shortbows
// =====================================================================================================================
// Weapon mentioned in Pathfinder 2E Core Rulebook, Chapter 2, page 40, "Elven Weapon Familiarity".
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponCompositeShortbow)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponCompositeShortbowUntrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponCompositeShortbowTrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponCompositeShortbowExpert)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponCompositeShortbowMaster)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponCompositeShortbowLegendary)

// =====================================================================================================================
// Proficiency Ranks for Crossbows
// =====================================================================================================================
// Weapon mentioned in Pathfinder 2E Core Rulebook, under:
//	- Chapter 3, page 203, "Attacks" for "Wizard"
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponCrossbow)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponCrossbowUntrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponCrossbowTrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponCrossbowExpert)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponCrossbowMaster)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponCrossbowLegendary)

// =====================================================================================================================
// Proficiency Ranks for Daggers
// =====================================================================================================================
// Weapon mentioned in Pathfinder 2E Core Rulebook, under:
//	- Chapter 3, page 203, "Attacks" for "Wizard"
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponDagger)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponDaggerUntrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponDaggerTrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponDaggerExpert)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponDaggerMaster)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponDaggerLegendary)

// =====================================================================================================================
// Proficiency Ranks for Dogslicers
// =====================================================================================================================
// Weapon mentioned in Pathfinder 2E Core Rulebook, Chapter 2, page 48, "Goblin Weapon Familiarity".
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponDogslicer)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponDogslicerUntrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponDogslicerTrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponDogslicerExpert)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponDogslicerMaster)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponDogslicerLegendary)

// =====================================================================================================================
// Proficiency Ranks for Falchions
// =====================================================================================================================
// Weapon mentioned in Pathfinder 2E Core Rulebook, Chapter 2, page 58, "Orc Weapon Familiarity".
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponFalchion)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponFalchionUntrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponFalchionTrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponFalchionExpert)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponFalchionMaster)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponFalchionLegendary)

// =====================================================================================================================
// Proficiency Ranks for Glaives
// =====================================================================================================================
// Weapon mentioned in Pathfinder 2E Core Rulebook, Chapter 2, page 44, "Gnome Weapon Familiarity".
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponGlaive)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponGlaiveUntrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponGlaiveTrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponGlaiveExpert)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponGlaiveMaster)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponGlaiveLegendary)

// =====================================================================================================================
// Proficiency Ranks for Greataxes
// =====================================================================================================================
// Weapon mentioned in Pathfinder 2E Core Rulebook, Chapter 2, page 58, "Orc Weapon Familiarity".
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponGreataxe)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponGreataxeUntrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponGreataxeTrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponGreataxeExpert)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponGreataxeMaster)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponGreataxeLegendary)

// =====================================================================================================================
// Proficiency Ranks for Halfling Sling Staves
// =====================================================================================================================
// Weapon mentioned in Pathfinder 2E Core Rulebook, Chapter 2, page 52, "Halfling Weapon Familiarity".
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponHalflingSlingStaff)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponHalflingSlingStaffUntrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponHalflingSlingStaffTrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponHalflingSlingStaffExpert)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponHalflingSlingStaffMaster)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponHalflingSlingStaffLegendary)

// =====================================================================================================================
// Proficiency Ranks for Heavy Crossbows
// =====================================================================================================================
// Weapon mentioned in Pathfinder 2E Core Rulebook, under:
//	- Chapter 3, page 203, "Attacks" for "Wizard"
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponHeavyCrossbow)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponHeavyCrossbowUntrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponHeavyCrossbowTrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponHeavyCrossbowExpert)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponHeavyCrossbowMaster)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponHeavyCrossbowLegendary)

// =====================================================================================================================
// Proficiency Ranks for Horsechoppers
// =====================================================================================================================
// Weapon mentioned in Pathfinder 2E Core Rulebook, Chapter 2, page 48, "Goblin Weapon Familiarity".
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponHorsechopper)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponHorsechopperUntrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponHorsechopperTrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponHorsechopperExpert)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponHorsechopperMaster)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponHorsechopperLegendary)

// =====================================================================================================================
// Proficiency Ranks for Kukris
// =====================================================================================================================
// Weapon mentioned in Pathfinder 2E Core Rulebook, Chapter 2, page 44, "Gnome Weapon Familiarity".
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponKukri)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponKukriUntrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponKukriTrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponKukriExpert)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponKukriMaster)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponKukriLegendary)

// =====================================================================================================================
// Proficiency Ranks for Longbows
// =====================================================================================================================
// Weapon mentioned in Pathfinder 2E Core Rulebook, Chapter 2, page 40, "Elven Weapon Familiarity".
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponLongbow)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponLongbowUntrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponLongbowTrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponLongbowExpert)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponLongbowMaster)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponLongbowLegendary)

// =====================================================================================================================
// Proficiency Ranks for Longswords
// =====================================================================================================================
// Weapon mentioned in Pathfinder 2E Core Rulebook, under:
//	- Chapter 2, page 40, "Elven Weapon Familiarity"
//	- Chapter 3, page 95, "Attacks" for "Bard"
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponLongsword)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponLongswordUntrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponLongswordTrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponLongswordExpert)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponLongswordMaster)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponLongswordLegendary)

// =====================================================================================================================
// Proficiency Ranks for Picks
// =====================================================================================================================
// Weapon mentioned in Pathfinder 2E Core Rulebook, Chapter 2, page 36, "Dwarven Weapon Familiarity".
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponPick)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponPickUntrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponPickTrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponPickExpert)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponPickMaster)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponPickLegendary)

// =====================================================================================================================
// Proficiency Ranks for Rapiers
// =====================================================================================================================
// Weapon mentioned in Pathfinder 2E Core Rulebook, under:
//	- Chapter 2, page 40, "Elven Weapon Familiarity"
//	- Chapter 3, page 95, "Attacks" for "Bard"
//	- Chapter 3, page 179, "Attacks" for "Rogue"
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponRapier)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponRapierUntrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponRapierTrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponRapierExpert)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponRapierMaster)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponRapierLegendary)

// =====================================================================================================================
// Proficiency Ranks for Saps
// =====================================================================================================================
// Weapon mentioned in Pathfinder 2E Core Rulebook, under:
//	- Chapter 3, page 95, "Attacks" for "Bard"
//	- Chapter 3, page 179, "Attacks" for "Rogue"
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponSap)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponSapUntrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponSapTrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponSapExpert)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponSapMaster)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponSapLegendary)

// =====================================================================================================================
// Proficiency Ranks for Shortbows
// =====================================================================================================================
// Weapon mentioned in Pathfinder 2E Core Rulebook, under:
//	- Chapter 2, page 40, "Elven Weapon Familiarity"
//	- Chapter 3, page 95, "Attacks" for "Bard"
//	- Chapter 3, page 179, "Attacks" for "Rogue"
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponShortbow)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponShortbowUntrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponShortbowTrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponShortbowExpert)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponShortbowMaster)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponShortbowLegendary)

// =====================================================================================================================
// Proficiency Ranks for Shortswords
// =====================================================================================================================
// Weapon mentioned in Pathfinder 2E Core Rulebook, under:
//	- Chapter 2, page 52, "Halfling Weapon Familiarity"
//	- Chapter 3, page 95, "Attacks" for "Bard"
//	- Chapter 3, page 179, "Attacks" for "Rogue"
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponShortsword)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponShortswordUntrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponShortswordTrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponShortswordExpert)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponShortswordMaster)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponShortswordLegendary)

// =====================================================================================================================
// Proficiency Ranks for Slings
// =====================================================================================================================
// Weapon mentioned in Pathfinder 2E Core Rulebook, Chapter 2, page 52, "Halfling Weapon Familiarity".
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponSling)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponSlingUntrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponSlingTrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponSlingExpert)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponSlingMaster)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponSlingLegendary)

// =====================================================================================================================
// Proficiency Ranks for Staves
// =====================================================================================================================
// Weapon mentioned in Pathfinder 2E Core Rulebook, under:
//	- Chapter 3, page 203, "Attacks" for "Wizard"
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponStaff)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponStaffUntrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponStaffTrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponStaffExpert)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponStaffMaster)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponStaffLegendary)

// =====================================================================================================================
// Proficiency Ranks for Warhammers
// =====================================================================================================================
// Weapon mentioned in Pathfinder 2E Core Rulebook, Chapter 2, page 36, "Dwarven Weapon Familiarity".
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponWarhammer)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponWarhammerUntrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponWarhammerTrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponWarhammerExpert)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponWarhammerMaster)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponWarhammerLegendary)

// =====================================================================================================================
// Proficiency Ranks for Whips
// =====================================================================================================================
// Weapon mentioned in Pathfinder 2E Core Rulebook, under:
//	- Chapter 3, page 95, "Attacks" for "Bard"
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponWhip)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponWhipUntrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponWhipTrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponWhipExpert)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponWhipMaster)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencyWeaponWhipLegendary)

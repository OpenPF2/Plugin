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
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyCategoryUnarmedUntrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyCategoryUnarmedTrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyCategoryUnarmedExpert)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyCategoryUnarmedMaster)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyCategoryUnarmedLegendary)

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
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyCategorySimpleUntrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyCategorySimpleTrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyCategorySimpleExpert)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyCategorySimpleMaster)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyCategorySimpleLegendary)

// =====================================================================================================================
// Proficiency Ranks for Advanced Weapons
// =====================================================================================================================
// Weapon type mentioned in Pathfinder 2E Core Rulebook under:
//	- Chapter 3, page 141, "Attacks" for "Fighter"
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyCategoryAdvancedUntrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyCategoryAdvancedTrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyCategoryAdvancedExpert)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyCategoryAdvancedMaster)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyCategoryAdvancedLegendary)

// =====================================================================================================================
// Proficiency Ranks for Advanced Dwarf Weapons
// =====================================================================================================================
// From the Pathfinder 2E Core Rulebook, Chapter 2, page 36, "Dwarven Weapon Familiarity":
// "For the purpose of determining your proficiency, [...] advanced dwarf weapons are martial weapons."
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyCategoryAdvancedDwarfUntrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyCategoryAdvancedDwarfTrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyCategoryAdvancedDwarfExpert)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyCategoryAdvancedDwarfMaster)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyCategoryAdvancedDwarfLegendary)

// =====================================================================================================================
// Proficiency Ranks for Advanced Elf Weapons
// =====================================================================================================================
// From the Pathfinder 2E Core Rulebook, Chapter 2, page 40, "Elven Weapon Familiarity":
// "For the purpose of determining your proficiency, [...] advanced elf weapons are martial weapons."
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyCategoryAdvancedElfUntrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyCategoryAdvancedElfTrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyCategoryAdvancedElfExpert)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyCategoryAdvancedElfMaster)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyCategoryAdvancedElfLegendary)

// =====================================================================================================================
// Proficiency Ranks for Advanced Gnome Weapons
// =====================================================================================================================
// From the Pathfinder 2E Core Rulebook, Chapter 2, page 44, "Gnome Weapon Familiarity":
// "For the purpose of determining your proficiency, [...] advanced gnome weapons are martial weapons."
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyCategoryAdvancedGnomeUntrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyCategoryAdvancedGnomeTrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyCategoryAdvancedGnomeExpert)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyCategoryAdvancedGnomeMaster)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyCategoryAdvancedGnomeLegendary)

// =====================================================================================================================
// Proficiency Ranks for Advanced Goblin Weapons
// =====================================================================================================================
// From the Pathfinder 2E Core Rulebook, Chapter 2, page 48, "Goblin Weapon Familiarity":
// "For the purpose of determining your proficiency, [...] advanced goblin weapons are martial weapons."
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyCategoryAdvancedGoblinUntrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyCategoryAdvancedGoblinTrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyCategoryAdvancedGoblinExpert)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyCategoryAdvancedGoblinMaster)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyCategoryAdvancedGoblinLegendary)

// =====================================================================================================================
// Proficiency Ranks for Advanced Halfling Weapons
// =====================================================================================================================
// From the Pathfinder 2E Core Rulebook, Chapter 2, page 52, "Halfling Weapon Familiarity":
// "For the purpose of determining your proficiency, [...] advanced halfling weapons are martial weapons."
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyCategoryAdvancedHalflingUntrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyCategoryAdvancedHalflingTrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyCategoryAdvancedHalflingExpert)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyCategoryAdvancedHalflingMaster)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyCategoryAdvancedHalflingLegendary)

// =====================================================================================================================
// Proficiency Ranks for Martial Weapons
// =====================================================================================================================
// Weapon type mentioned in Pathfinder 2E Core Rulebook under:
//	- Chapter 3, page 83, "Attacks" for "Barbarian"
//	- Chapter 3, page 105, "Attacks" for "Champion"
//	- Chapter 3, page 141, "Attacks" for "Fighter"
//	- Chapter 3, page 167, "Attacks" for "Ranger"
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyCategoryMartialUntrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyCategoryMartialTrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyCategoryMartialExpert)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyCategoryMartialMaster)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyCategoryMartialLegendary)

// =====================================================================================================================
// Proficiency Ranks for Martial Dwarf Weapons
// =====================================================================================================================
// From the Pathfinder 2E Core Rulebook, Chapter 2, page 36, "Dwarven Weapon Familiarity":
// "For the purpose of determining your proficiency, martial dwarf weapons are simple weapons..."
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyCategoryMartialDwarfUntrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyCategoryMartialDwarfTrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyCategoryMartialDwarfExpert)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyCategoryMartialDwarfMaster)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyCategoryMartialDwarfLegendary)

// =====================================================================================================================
// Proficiency Ranks for Martial Elf Weapons
// =====================================================================================================================
// From the Pathfinder 2E Core Rulebook, Chapter 2, page 40, "Elven Weapon Familiarity":
// "For the purpose of determining your proficiency, martial elf weapons are simple weapons..."
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyCategoryMartialElfUntrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyCategoryMartialElfTrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyCategoryMartialElfExpert)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyCategoryMartialElfMaster)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyCategoryMartialElfLegendary)

// =====================================================================================================================
// Proficiency Ranks for Martial Gnome Weapons
// =====================================================================================================================
// From the Pathfinder 2E Core Rulebook, Chapter 2, page 44, "Gnome Weapon Familiarity":
// "For the purpose of determining your proficiency, martial gnome weapons are simple weapons..."
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyCategoryMartialGnomeUntrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyCategoryMartialGnomeTrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyCategoryMartialGnomeExpert)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyCategoryMartialGnomeMaster)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyCategoryMartialGnomeLegendary)

// =====================================================================================================================
// Proficiency Ranks for Martial Goblin Weapons
// =====================================================================================================================
// From the Pathfinder 2E Core Rulebook, Chapter 2, page 48, "Goblin Weapon Familiarity":
// "For the purpose of determining your proficiency, martial goblin weapons are simple weapons..."
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyCategoryMartialGoblinUntrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyCategoryMartialGoblinTrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyCategoryMartialGoblinExpert)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyCategoryMartialGoblinMaster)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyCategoryMartialGoblinLegendary)

// =====================================================================================================================
// Proficiency Ranks for Martial Halfling Weapons
// =====================================================================================================================
// From the Pathfinder 2E Core Rulebook, Chapter 2, page 52, "Halfling Weapon Familiarity":
// "For the purpose of determining your proficiency, martial halfling weapons are simple weapons..."
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyCategoryMartialHalflingUntrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyCategoryMartialHalflingTrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyCategoryMartialHalflingExpert)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyCategoryMartialHalflingMaster)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyCategoryMartialHalflingLegendary)

// =====================================================================================================================
// Proficiency Ranks for Alchemical Bombs
// =====================================================================================================================
// Weapon type mentioned in Pathfinder 2E Core Rulebook under:
//	- Chapter 3, page 71, "Attacks" for "Alchemist"
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyAlchemicalBombUntrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyAlchemicalBombTrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyAlchemicalBombExpert)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyAlchemicalBombMaster)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyAlchemicalBombLegendary)

// =====================================================================================================================
// Proficiency Ranks for Battle Axes
// =====================================================================================================================
// Weapon mentioned in Pathfinder 2E Core Rulebook, Chapter 2, page 36, "Dwarven Weapon Familiarity".
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyBattleAxeUntrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyBattleAxeTrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyBattleAxeExpert)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyBattleAxeMaster)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyBattleAxeLegendary)

// =====================================================================================================================
// Proficiency Ranks for Clubs
// =====================================================================================================================
// Weapon mentioned in Pathfinder 2E Core Rulebook, under:
//	- Chapter 3, page 203, "Attacks" for "Wizard"
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyClubUntrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyClubTrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyClubExpert)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyClubMaster)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyClubLegendary)

// =====================================================================================================================
// Proficiency Ranks for Composite Longbows
// =====================================================================================================================
// Weapon mentioned in Pathfinder 2E Core Rulebook, Chapter 2, page 40, "Elven Weapon Familiarity".
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyCompositeLongbowUntrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyCompositeLongbowTrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyCompositeLongbowExpert)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyCompositeLongbowMaster)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyCompositeLongbowLegendary)

// =====================================================================================================================
// Proficiency Ranks for Composite Shortbows
// =====================================================================================================================
// Weapon mentioned in Pathfinder 2E Core Rulebook, Chapter 2, page 40, "Elven Weapon Familiarity".
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyCompositeShortbowUntrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyCompositeShortbowTrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyCompositeShortbowExpert)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyCompositeShortbowMaster)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyCompositeShortbowLegendary)

// =====================================================================================================================
// Proficiency Ranks for Crossbows
// =====================================================================================================================
// Weapon mentioned in Pathfinder 2E Core Rulebook, under:
//	- Chapter 3, page 203, "Attacks" for "Wizard"
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyCrossbowUntrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyCrossbowTrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyCrossbowExpert)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyCrossbowMaster)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyCrossbowLegendary)

// =====================================================================================================================
// Proficiency Ranks for Daggers
// =====================================================================================================================
// Weapon mentioned in Pathfinder 2E Core Rulebook, under:
//	- Chapter 3, page 203, "Attacks" for "Wizard"
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyDaggerUntrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyDaggerTrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyDaggerExpert)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyDaggerMaster)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyDaggerLegendary)

// =====================================================================================================================
// Proficiency Ranks for Dogslicers
// =====================================================================================================================
// Weapon mentioned in Pathfinder 2E Core Rulebook, Chapter 2, page 48, "Goblin Weapon Familiarity".
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyDogslicerUntrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyDogslicerTrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyDogslicerExpert)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyDogslicerMaster)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyDogslicerLegendary)

// =====================================================================================================================
// Proficiency Ranks for Falchions
// =====================================================================================================================
// Weapon mentioned in Pathfinder 2E Core Rulebook, Chapter 2, page 58, "Orc Weapon Familiarity".
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyFalchionUntrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyFalchionTrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyFalchionExpert)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyFalchionMaster)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyFalchionLegendary)

// =====================================================================================================================
// Proficiency Ranks for Glaives
// =====================================================================================================================
// Weapon mentioned in Pathfinder 2E Core Rulebook, Chapter 2, page 44, "Gnome Weapon Familiarity".
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyGlaiveUntrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyGlaiveTrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyGlaiveExpert)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyGlaiveMaster)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyGlaiveLegendary)

// =====================================================================================================================
// Proficiency Ranks for Greataxes
// =====================================================================================================================
// Weapon mentioned in Pathfinder 2E Core Rulebook, Chapter 2, page 58, "Orc Weapon Familiarity".
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyGreataxeUntrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyGreataxeTrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyGreataxeExpert)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyGreataxeMaster)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyGreataxeLegendary)

// =====================================================================================================================
// Proficiency Ranks for Halfling Sling Staves
// =====================================================================================================================
// Weapon mentioned in Pathfinder 2E Core Rulebook, Chapter 2, page 52, "Halfling Weapon Familiarity".
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyHalflingSlingStaffUntrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyHalflingSlingStaffTrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyHalflingSlingStaffExpert)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyHalflingSlingStaffMaster)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyHalflingSlingStaffLegendary)

// =====================================================================================================================
// Proficiency Ranks for Heavy Crossbows
// =====================================================================================================================
// Weapon mentioned in Pathfinder 2E Core Rulebook, under:
//	- Chapter 3, page 203, "Attacks" for "Wizard"
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyHeavyCrossbowUntrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyHeavyCrossbowTrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyHeavyCrossbowExpert)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyHeavyCrossbowMaster)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyHeavyCrossbowLegendary)

// =====================================================================================================================
// Proficiency Ranks for Horsechoppers
// =====================================================================================================================
// Weapon mentioned in Pathfinder 2E Core Rulebook, Chapter 2, page 48, "Goblin Weapon Familiarity".
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyHorsechopperUntrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyHorsechopperTrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyHorsechopperExpert)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyHorsechopperMaster)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyHorsechopperLegendary)

// =====================================================================================================================
// Proficiency Ranks for Kukris
// =====================================================================================================================
// Weapon mentioned in Pathfinder 2E Core Rulebook, Chapter 2, page 44, "Gnome Weapon Familiarity".
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyKukriUntrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyKukriTrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyKukriExpert)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyKukriMaster)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyKukriLegendary)

// =====================================================================================================================
// Proficiency Ranks for Longbows
// =====================================================================================================================
// Weapon mentioned in Pathfinder 2E Core Rulebook, Chapter 2, page 40, "Elven Weapon Familiarity".
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyLongbowUntrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyLongbowTrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyLongbowExpert)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyLongbowMaster)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyLongbowLegendary)

// =====================================================================================================================
// Proficiency Ranks for Longswords
// =====================================================================================================================
// Weapon mentioned in Pathfinder 2E Core Rulebook, under:
//	- Chapter 2, page 40, "Elven Weapon Familiarity"
//	- Chapter 3, page 95, "Attacks" for "Bard"
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyLongswordUntrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyLongswordTrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyLongswordExpert)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyLongswordMaster)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyLongswordLegendary)

// =====================================================================================================================
// Proficiency Ranks for Picks
// =====================================================================================================================
// Weapon mentioned in Pathfinder 2E Core Rulebook, Chapter 2, page 36, "Dwarven Weapon Familiarity".
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyPickUntrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyPickTrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyPickExpert)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyPickMaster)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyPickLegendary)

// =====================================================================================================================
// Proficiency Ranks for Rapiers
// =====================================================================================================================
// Weapon mentioned in Pathfinder 2E Core Rulebook, under:
//	- Chapter 2, page 40, "Elven Weapon Familiarity"
//	- Chapter 3, page 95, "Attacks" for "Bard"
//	- Chapter 3, page 179, "Attacks" for "Rogue"
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyRapierUntrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyRapierTrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyRapierExpert)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyRapierMaster)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyRapierLegendary)

// =====================================================================================================================
// Proficiency Ranks for Saps
// =====================================================================================================================
// Weapon mentioned in Pathfinder 2E Core Rulebook, under:
//	- Chapter 3, page 95, "Attacks" for "Bard"
//	- Chapter 3, page 179, "Attacks" for "Rogue"
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencySapUntrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencySapTrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencySapExpert)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencySapMaster)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencySapLegendary)

// =====================================================================================================================
// Proficiency Ranks for Shortbows
// =====================================================================================================================
// Weapon mentioned in Pathfinder 2E Core Rulebook, under:
//	- Chapter 2, page 40, "Elven Weapon Familiarity"
//	- Chapter 3, page 95, "Attacks" for "Bard"
//	- Chapter 3, page 179, "Attacks" for "Rogue"
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyShortbowUntrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyShortbowTrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyShortbowExpert)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyShortbowMaster)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyShortbowLegendary)

// =====================================================================================================================
// Proficiency Ranks for Shortswords
// =====================================================================================================================
// Weapon mentioned in Pathfinder 2E Core Rulebook, under:
//	- Chapter 2, page 52, "Halfling Weapon Familiarity"
//	- Chapter 3, page 95, "Attacks" for "Bard"
//	- Chapter 3, page 179, "Attacks" for "Rogue"
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyShortswordUntrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyShortswordTrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyShortswordExpert)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyShortswordMaster)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyShortswordLegendary)

// =====================================================================================================================
// Proficiency Ranks for Slings
// =====================================================================================================================
// Weapon mentioned in Pathfinder 2E Core Rulebook, Chapter 2, page 52, "Halfling Weapon Familiarity".
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencySlingUntrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencySlingTrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencySlingExpert)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencySlingMaster)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencySlingLegendary)

// =====================================================================================================================
// Proficiency Ranks for Staves
// =====================================================================================================================
// Weapon mentioned in Pathfinder 2E Core Rulebook, under:
//	- Chapter 3, page 203, "Attacks" for "Wizard"
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyStaffUntrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyStaffTrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyStaffExpert)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyStaffMaster)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyStaffLegendary)

// =====================================================================================================================
// Proficiency Ranks for Warhammers
// =====================================================================================================================
// Weapon mentioned in Pathfinder 2E Core Rulebook, Chapter 2, page 36, "Dwarven Weapon Familiarity".
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyWarhammerUntrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyWarhammerTrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyWarhammerExpert)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyWarhammerMaster)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyWarhammerLegendary)

// =====================================================================================================================
// Proficiency Ranks for Whips
// =====================================================================================================================
// Weapon mentioned in Pathfinder 2E Core Rulebook, under:
//	- Chapter 3, page 95, "Attacks" for "Bard"
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyWhipUntrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyWhipTrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyWhipExpert)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyWhipMaster)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagWeaponProficiencyWhipLegendary)

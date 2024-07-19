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

#include "GameplayTags/Stats/Proficiencies/Skills.h"

// =====================================================================================================================
// Proficiency Ranks for Skills (training and experience at performing certain tasks).
// =====================================================================================================================
// Sources:
//	- Pathfinder 2E Core Rulebook, Chapter 1: "Introduction", page 11, "Playing the Game".
//	- Pathfinder 2E Core Rulebook, Chapter 1: "Introduction", page 13, "Proficiency".
//	- Pathfinder 2E Core Rulebook, Chapter 4: "Skills", pages 233-253.
//	- Pathfinder 2E Core Rulebook, Appendix, page 624, "Skills".

// === Acrobatics
UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencySkillAcrobatics,
	"PF2.Proficiency.Skill.Acrobatics",
	"Character proficiency ranks for Acrobatics."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencySkillAcrobaticsUntrained,
	"PF2.Proficiency.Skill.Acrobatics.Untrained",
	"Character is Untrained in Acrobatics."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencySkillAcrobaticsTrained,
	"PF2.Proficiency.Skill.Acrobatics.Trained",
	"Character is Trained in Acrobatics."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencySkillAcrobaticsExpert,
	"PF2.Proficiency.Skill.Acrobatics.Expert",
	"Character is Expert in Acrobatics."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencySkillAcrobaticsMaster,
	"PF2.Proficiency.Skill.Acrobatics.Master",
	"Character is Master in Acrobatics."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencySkillAcrobaticsLegendary,
	"PF2.Proficiency.Skill.Acrobatics.Legendary",
	"Character is Legendary in Acrobatics."
)

// === Arcana
UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencySkillArcana,
	"PF2.Proficiency.Skill.Arcana",
	"Character proficiency ranks for Arcana."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencySkillArcanaUntrained,
	"PF2.Proficiency.Skill.Arcana.Untrained",
	"Character is Untrained in Arcana."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencySkillArcanaTrained,
	"PF2.Proficiency.Skill.Arcana.Trained",
	"Character is Trained in Arcana."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencySkillArcanaExpert,
	"PF2.Proficiency.Skill.Arcana.Expert",
	"Character is Expert in Arcana."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencySkillArcanaMaster,
	"PF2.Proficiency.Skill.Arcana.Master",
	"Character is Master in Arcana."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencySkillArcanaLegendary,
	"PF2.Proficiency.Skill.Arcana.Legendary",
	"Character is Legendary in Arcana."
)

// === Athletics
UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencySkillAthletics,
	"PF2.Proficiency.Skill.Athletics",
	"Character proficiency ranks for Athletics."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencySkillAthleticsUntrained,
	"PF2.Proficiency.Skill.Athletics.Untrained",
	"Character is Untrained in Athletics."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencySkillAthleticsTrained,
	"PF2.Proficiency.Skill.Athletics.Trained",
	"Character is Trained in Athletics."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencySkillAthleticsExpert,
	"PF2.Proficiency.Skill.Athletics.Expert",
	"Character is Expert in Athletics."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencySkillAthleticsMaster,
	"PF2.Proficiency.Skill.Athletics.Master",
	"Character is Master in Athletics."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencySkillAthleticsLegendary,
	"PF2.Proficiency.Skill.Athletics.Legendary",
	"Character is Legendary in Athletics."
)

// === Crafting
UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencySkillCrafting,
	"PF2.Proficiency.Skill.Crafting",
	"Character proficiency ranks for Crafting."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencySkillCraftingUntrained,
	"PF2.Proficiency.Skill.Crafting.Untrained",
	"Character is Untrained in Crafting."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencySkillCraftingTrained,
	"PF2.Proficiency.Skill.Crafting.Trained",
	"Character is Trained in Crafting."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencySkillCraftingExpert,
	"PF2.Proficiency.Skill.Crafting.Expert",
	"Character is Expert in Crafting."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencySkillCraftingMaster,
	"PF2.Proficiency.Skill.Crafting.Master",
	"Character is Master in Crafting."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencySkillCraftingLegendary,
	"PF2.Proficiency.Skill.Crafting.Legendary",
	"Character is Legendary in Crafting."
)

// === Deception
UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencySkillDeception,
	"PF2.Proficiency.Skill.Deception",
	"Character proficiency ranks for Deception."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencySkillDeceptionUntrained,
	"PF2.Proficiency.Skill.Deception.Untrained",
	"Character is Untrained in Deception."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencySkillDeceptionTrained,
	"PF2.Proficiency.Skill.Deception.Trained",
	"Character is Trained in Deception."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencySkillDeceptionExpert,
	"PF2.Proficiency.Skill.Deception.Expert",
	"Character is Expert in Deception."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencySkillDeceptionMaster,
	"PF2.Proficiency.Skill.Deception.Master",
	"Character is Master in Deception."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencySkillDeceptionLegendary,
	"PF2.Proficiency.Skill.Deception.Legendary",
	"Character is Legendary in Deception."
)

// === Diplomacy
UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencySkillDiplomacy,
	"PF2.Proficiency.Skill.Diplomacy",
	"Character proficiency ranks for Diplomacy."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencySkillDiplomacyUntrained,
	"PF2.Proficiency.Skill.Diplomacy.Untrained",
	"Character is Untrained in Diplomacy."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencySkillDiplomacyTrained,
	"PF2.Proficiency.Skill.Diplomacy.Trained",
	"Character is Trained in Diplomacy."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencySkillDiplomacyExpert,
	"PF2.Proficiency.Skill.Diplomacy.Expert",
	"Character is Expert in Diplomacy."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencySkillDiplomacyMaster,
	"PF2.Proficiency.Skill.Diplomacy.Master",
	"Character is Master in Diplomacy."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencySkillDiplomacyLegendary,
	"PF2.Proficiency.Skill.Diplomacy.Legendary",
	"Character is Legendary in Diplomacy."
)

// === Intimidation
UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencySkillIntimidation,
	"PF2.Proficiency.Skill.Intimidation",
	"Character proficiency ranks for Intimidation."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencySkillIntimidationUntrained,
	"PF2.Proficiency.Skill.Intimidation.Untrained",
	"Character is Untrained in Intimidation."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencySkillIntimidationTrained,
	"PF2.Proficiency.Skill.Intimidation.Trained",
	"Character is Trained in Intimidation."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencySkillIntimidationExpert,
	"PF2.Proficiency.Skill.Intimidation.Expert",
	"Character is Expert in Intimidation."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencySkillIntimidationMaster,
	"PF2.Proficiency.Skill.Intimidation.Master",
	"Character is Master in Intimidation."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencySkillIntimidationLegendary,
	"PF2.Proficiency.Skill.Intimidation.Legendary",
	"Character is Legendary in Intimidation."
)

// === Lore1
UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencySkillLore1,
	"PF2.Proficiency.Skill.Lore1",
	"Character proficiency ranks for first lore specialization."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencySkillLore1Untrained,
	"PF2.Proficiency.Skill.Lore1.Untrained",
	"Character is Untrained in first lore specialization."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencySkillLore1Trained,
	"PF2.Proficiency.Skill.Lore1.Trained",
	"Character is Trained in first lore specialization."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencySkillLore1Expert,
	"PF2.Proficiency.Skill.Lore1.Expert",
	"Character is Expert in first lore specialization."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencySkillLore1Master,
	"PF2.Proficiency.Skill.Lore1.Master",
	"Character is Master in first lore specialization."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencySkillLore1Legendary,
	"PF2.Proficiency.Skill.Lore1.Legendary",
	"Character is Legendary in first lore specialization."
)

// === Lore2
UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencySkillLore2,
	"PF2.Proficiency.Skill.Lore2",
	"Character proficiency ranks for second lore specialization."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencySkillLore2Untrained,
	"PF2.Proficiency.Skill.Lore2.Untrained",
	"Character is Untrained in second lore specialization."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencySkillLore2Trained,
	"PF2.Proficiency.Skill.Lore2.Trained",
	"Character is Trained in second lore specialization."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencySkillLore2Expert,
	"PF2.Proficiency.Skill.Lore2.Expert",
	"Character is Expert in second lore specialization."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencySkillLore2Master,
	"PF2.Proficiency.Skill.Lore2.Master",
	"Character is Master in second lore specialization."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencySkillLore2Legendary,
	"PF2.Proficiency.Skill.Lore2.Legendary",
	"Character is Legendary in second lore specialization."
)

// === Medicine
UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencySkillMedicine,
	"PF2.Proficiency.Skill.Medicine",
	"Character proficiency ranks for Medicine."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencySkillMedicineUntrained,
	"PF2.Proficiency.Skill.Medicine.Untrained",
	"Character is Untrained in Medicine."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencySkillMedicineTrained,
	"PF2.Proficiency.Skill.Medicine.Trained",
	"Character is Trained in Medicine."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencySkillMedicineExpert,
	"PF2.Proficiency.Skill.Medicine.Expert",
	"Character is Expert in Medicine."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencySkillMedicineMaster,
	"PF2.Proficiency.Skill.Medicine.Master",
	"Character is Master in Medicine."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencySkillMedicineLegendary,
	"PF2.Proficiency.Skill.Medicine.Legendary",
	"Character is Legendary in Medicine."
)

// === Nature
UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencySkillNature,
	"PF2.Proficiency.Skill.Nature",
	"Character proficiency ranks for Nature."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencySkillNatureUntrained,
	"PF2.Proficiency.Skill.Nature.Untrained",
	"Character is Untrained in Nature."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencySkillNatureTrained,
	"PF2.Proficiency.Skill.Nature.Trained",
	"Character is Trained in Nature."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencySkillNatureExpert,
	"PF2.Proficiency.Skill.Nature.Expert",
	"Character is Expert in Nature."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencySkillNatureMaster,
	"PF2.Proficiency.Skill.Nature.Master",
	"Character is Master in Nature."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencySkillNatureLegendary,
	"PF2.Proficiency.Skill.Nature.Legendary",
	"Character is Legendary in Nature."
)

// === Occultism
UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencySkillOccultism,
	"PF2.Proficiency.Skill.Occultism",
	"Character proficiency ranks for Occultism."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencySkillOccultismUntrained,
	"PF2.Proficiency.Skill.Occultism.Untrained",
	"Character is Untrained in Occultism."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencySkillOccultismTrained,
	"PF2.Proficiency.Skill.Occultism.Trained",
	"Character is Trained in Occultism."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencySkillOccultismExpert,
	"PF2.Proficiency.Skill.Occultism.Expert",
	"Character is Expert in Occultism."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencySkillOccultismMaster,
	"PF2.Proficiency.Skill.Occultism.Master",
	"Character is Master in Occultism."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencySkillOccultismLegendary,
	"PF2.Proficiency.Skill.Occultism.Legendary",
	"Character is Legendary in Occultism."
)

// === Performance
UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencySkillPerformance,
	"PF2.Proficiency.Skill.Performance",
	"Character proficiency ranks for Performance."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencySkillPerformanceUntrained,
	"PF2.Proficiency.Skill.Performance.Untrained",
	"Character is Untrained in Performance."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencySkillPerformanceTrained,
	"PF2.Proficiency.Skill.Performance.Trained",
	"Character is Trained in Performance."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencySkillPerformanceExpert,
	"PF2.Proficiency.Skill.Performance.Expert",
	"Character is Expert in Performance."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencySkillPerformanceMaster,
	"PF2.Proficiency.Skill.Performance.Master",
	"Character is Master in Performance."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencySkillPerformanceLegendary,
	"PF2.Proficiency.Skill.Performance.Legendary",
	"Character is Legendary in Performance."
)

// === Religion
UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencySkillReligion,
	"PF2.Proficiency.Skill.Religion",
	"Character proficiency ranks for Religion."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencySkillReligionUntrained,
	"PF2.Proficiency.Skill.Religion.Untrained",
	"Character is Untrained in Religion."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencySkillReligionTrained,
	"PF2.Proficiency.Skill.Religion.Trained",
	"Character is Trained in Religion."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencySkillReligionExpert,
	"PF2.Proficiency.Skill.Religion.Expert",
	"Character is Expert in Religion."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencySkillReligionMaster,
	"PF2.Proficiency.Skill.Religion.Master",
	"Character is Master in Religion."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencySkillReligionLegendary,
	"PF2.Proficiency.Skill.Religion.Legendary",
	"Character is Legendary in Religion."
)

// === Society
UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencySkillSociety,
	"PF2.Proficiency.Skill.Society",
	"Character proficiency ranks for Society."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencySkillSocietyUntrained,
	"PF2.Proficiency.Skill.Society.Untrained",
	"Character is Untrained in Society."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencySkillSocietyTrained,
	"PF2.Proficiency.Skill.Society.Trained",
	"Character is Trained in Society."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencySkillSocietyExpert,
	"PF2.Proficiency.Skill.Society.Expert",
	"Character is Expert in Society."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencySkillSocietyMaster,
	"PF2.Proficiency.Skill.Society.Master",
	"Character is Master in Society."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencySkillSocietyLegendary,
	"PF2.Proficiency.Skill.Society.Legendary",
	"Character is Legendary in Society."
)

// === Stealth
UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencySkillStealth,
	"PF2.Proficiency.Skill.Stealth",
	"Character proficiency ranks for Stealth."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencySkillStealthUntrained,
	"PF2.Proficiency.Skill.Stealth.Untrained",
	"Character is Untrained in Stealth."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencySkillStealthTrained,
	"PF2.Proficiency.Skill.Stealth.Trained",
	"Character is Trained in Stealth."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencySkillStealthExpert,
	"PF2.Proficiency.Skill.Stealth.Expert",
	"Character is Expert in Stealth."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencySkillStealthMaster,
	"PF2.Proficiency.Skill.Stealth.Master",
	"Character is Master in Stealth."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencySkillStealthLegendary,
	"PF2.Proficiency.Skill.Stealth.Legendary",
	"Character is Legendary in Stealth."
)

// === Survival
UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencySkillSurvival,
	"PF2.Proficiency.Skill.Survival",
	"Character proficiency ranks for Survival."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencySkillSurvivalUntrained,
	"PF2.Proficiency.Skill.Survival.Untrained",
	"Character is Untrained in Survival."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencySkillSurvivalTrained,
	"PF2.Proficiency.Skill.Survival.Trained",
	"Character is Trained in Survival."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencySkillSurvivalExpert,
	"PF2.Proficiency.Skill.Survival.Expert",
	"Character is Expert in Survival."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencySkillSurvivalMaster,
	"PF2.Proficiency.Skill.Survival.Master",
	"Character is Master in Survival."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencySkillSurvivalLegendary,
	"PF2.Proficiency.Skill.Survival.Legendary",
	"Character is Legendary in Survival."
)

// === Thievery
UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencySkillThievery,
	"PF2.Proficiency.Skill.Thievery",
	"Character proficiency ranks for Thievery."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencySkillThieveryUntrained,
	"PF2.Proficiency.Skill.Thievery.Untrained",
	"Character is Untrained in Thievery."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencySkillThieveryTrained,
	"PF2.Proficiency.Skill.Thievery.Trained",
	"Character is Trained in Thievery."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencySkillThieveryExpert,
	"PF2.Proficiency.Skill.Thievery.Expert",
	"Character is Expert in Thievery."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencySkillThieveryMaster,
	"PF2.Proficiency.Skill.Thievery.Master",
	"Character is Master in Thievery."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencySkillThieveryLegendary,
	"PF2.Proficiency.Skill.Thievery.Legendary",
	"Character is Legendary in Thievery."
)

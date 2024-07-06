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

#include "GameplayTags/Stats/Proficiencies/SavingThrows.h"

// =====================================================================================================================
// Proficiency Ranks for Saving Throws (avoiding danger or otherwise withstanding an assault to mind or body).
// =====================================================================================================================
// Sources:
//	- Pathfinder 2E Core Rulebook, Chapter 1: "Introduction", page 11, "Playing the Game".
//	- Pathfinder 2E Core Rulebook, Chapter 1: "Introduction", page 13, "Saving Throw (Save)" and "Proficiency".
//	- Pathfinder 2E Core Rulebook, Appendix, page 624, "Saving Throws".

// === Fortitude
UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencySavingThrowFortitude,
	"PF2.Proficiency.SavingThrow.Fortitude",
	"Character proficiency ranks for Fortitude saving throws."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencySavingThrowFortitudeUntrained,
	"PF2.Proficiency.SavingThrow.Fortitude.Untrained",
	"Character is Untrained in Fortitude."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencySavingThrowFortitudeTrained,
	"PF2.Proficiency.SavingThrow.Fortitude.Trained",
	"Character is Trained in Fortitude."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencySavingThrowFortitudeExpert,
	"PF2.Proficiency.SavingThrow.Fortitude.Expert",
	"Character is Expert in Fortitude."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencySavingThrowFortitudeMaster,
	"PF2.Proficiency.SavingThrow.Fortitude.Master",
	"Character is Master in Fortitude."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencySavingThrowFortitudeLegendary,
	"PF2.Proficiency.SavingThrow.Fortitude.Legendary",
	"Character is Legendary in Fortitude."
)

// === Reflex
UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencySavingThrowReflex,
	"PF2.Proficiency.SavingThrow.Reflex",
	"Character proficiency ranks for Reflex saving throws."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencySavingThrowReflexUntrained,
	"PF2.Proficiency.SavingThrow.Reflex.Untrained",
	"Character is Untrained in Reflex."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencySavingThrowReflexTrained,
	"PF2.Proficiency.SavingThrow.Reflex.Trained",
	"Character is Trained in Reflex."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencySavingThrowReflexExpert,
	"PF2.Proficiency.SavingThrow.Reflex.Expert",
	"Character is Expert in Reflex."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencySavingThrowReflexMaster,
	"PF2.Proficiency.SavingThrow.Reflex.Master",
	"Character is Master in Reflex."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencySavingThrowReflexLegendary,
	"PF2.Proficiency.SavingThrow.Reflex.Legendary",
	"Character is Legendary in Reflex."
)

// === Will
UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencySavingThrowWill,
	"PF2.Proficiency.SavingThrow.Will",
	"Character proficiency ranks for Will saving throws."
)
UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencySavingThrowWillUntrained,
	"PF2.Proficiency.SavingThrow.Will.Untrained",
	"Character is Untrained in Will."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencySavingThrowWillTrained,
	"PF2.Proficiency.SavingThrow.Will.Trained",
	"Character is Trained in Will."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencySavingThrowWillExpert,
	"PF2.Proficiency.SavingThrow.Will.Expert",
	"Character is Expert in Will."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencySavingThrowWillMaster,
	"PF2.Proficiency.SavingThrow.Will.Master",
	"Character is Master in Will."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencySavingThrowWillLegendary,
	"PF2.Proficiency.SavingThrow.Will.Legendary",
	"Character is Legendary in Will."
)

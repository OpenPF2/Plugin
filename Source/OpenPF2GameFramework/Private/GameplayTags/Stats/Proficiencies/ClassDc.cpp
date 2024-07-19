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

#include "GameplayTags/Stats/Proficiencies/ClassDc.h"

// =====================================================================================================================
// Proficiency Ranks for Class DC (Difficulty Class).
// =====================================================================================================================
// Sources:
//	- Pathfinder 2E Core Rulebook, Chapter 1: "Introduction", page 11, "Playing the Game".
//	- Pathfinder 2E Core Rulebook, Chapter 1: "Introduction", page 13, "Proficiency".
//	- Pathfinder 2E Core Rulebook, Chapter 1: "Introduction", page 27, "Character Sheet".
//	- Pathfinder 2E Core Rulebook, Chapter 3: "Classes", page 69, "Initial Proficiencies".
//	- Pathfinder 2E Core Rulebook, Appendix, page 624, "Class DC".
UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyClassDc,
	"PF2.Proficiency.ClassDc",
	"Character proficiency ranks for Class Difficulty Class (Class DC)."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyClassDcUntrained,
	"PF2.Proficiency.ClassDc.Untrained",
	"Character is Untrained in Class Difficulty Class (Class DC)."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyClassDcTrained,
	"PF2.Proficiency.ClassDc.Trained",
	"Character is Trained in Class Difficulty Class (Class DC)."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyClassDcExpert,
	"PF2.Proficiency.ClassDc.Expert",
	"Character is Expert in Class Difficulty Class (Class DC)."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyClassDcMaster,
	"PF2.Proficiency.ClassDc.Master",
	"Character is Master in Class Difficulty Class (Class DC)."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencyClassDcLegendary,
	"PF2.Proficiency.ClassDc.Legendary",
	"Character is Legendary in Class Difficulty Class (Class DC)."
)

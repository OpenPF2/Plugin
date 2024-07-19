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

#include "GameplayTags/Stats/Proficiencies/SpellAttacks.h"

// =====================================================================================================================
// Proficiency Ranks for spell attacks (Spell Attack Roll).
// =====================================================================================================================
// Source: Pathfinder 2E Core Rulebook, Appendix, page 627, "Spell Attack Roll".
UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencySpellAttack,
	"PF2.Proficiency.SpellAttack",
	"Character proficiency ranks for spell attacks (Spell Attack Roll)."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencySpellAttackUntrained,
	"PF2.Proficiency.SpellAttack.Untrained",
	"Character is Untrained in spell attacks."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencySpellAttackTrained,
	"PF2.Proficiency.SpellAttack.Trained",
	"Character is Trained in spell attacks."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencySpellAttackExpert,
	"PF2.Proficiency.SpellAttack.Expert",
	"Character is Expert in spell attacks."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencySpellAttackMaster,
	"PF2.Proficiency.SpellAttack.Master",
	"Character is Master in spell attacks."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencySpellAttackLegendary,
	"PF2.Proficiency.SpellAttack.Legendary",
	"Character is Legendary in spell attacks."
)

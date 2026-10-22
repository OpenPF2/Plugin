// OpenPF2 Game Framework for Unreal Engine, Copyright 2024, Guy Elsmore-Paddock. All Rights Reserved.
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

#include "GameplayTags/Common.h"

// =====================================================================================================================
// Top-level tag category definitions.
// =====================================================================================================================
UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagRoot,
	"PF2",
	"Gameplay tags provided by the OpenPF2 Game Framework."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagEncounters,
	"PF2.Encounter",
	"Tags used by abilities during encounters."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagGameplayAbilities,
	"PF2.GameplayAbility",
	"Tags that apply to Gameplay Abilities in OpenPF2."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagGameplayEffects,
	"PF2.GameplayEffect",
	"Tags that apply to Gameplay Effects in OpenPF2."
)

// Source: Pathfinder 2E Core Rulebook, Appendix, page 635.
UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagProficiencies,
	"PF2.Proficiency",
	"Measures of a character’s aptitude at specific tasks or qualities."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagTriggerTagCategoryRoot,
	"TriggerTagCategory.PF2",
	"Tags that trigger Gameplay Abilities in OpenPF2."
)

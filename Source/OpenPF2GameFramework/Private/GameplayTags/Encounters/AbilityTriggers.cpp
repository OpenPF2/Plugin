// OpenPF2 Game Framework for Unreal Engine, Copyright 2022-2024, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "GameplayTags/Encounters/AbilityTriggers.h"

// The UE editor requires these tags to be under a root tag of `TriggerTagCategory` in order for them to be selectable
// in the UI.

// =====================================================================================================================
// Tags that trigger Encounter-related Gameplay Abilities.
// =====================================================================================================================
UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagTriggerTagCategoryEncounters,
	"TriggerTagCategory.PF2.Encounter",
	"Tags that trigger Encounter-related Gameplay Abilities."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagTriggerTagCategoryEncounterEnterEncounter,
	"TriggerTagCategory.PF2.Encounter.EnterEncounter",
	"Tag to trigger Gameplay Abilities appropriate for when a character enters an encounter."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagTriggerTagCategoryEncounterStartTurn,
	"TriggerTagCategory.PF2.Encounter.StartTurn",
	"Tag to trigger Gameplay Abilities appropriate for the start of a character's turn during an encounter."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagTriggerTagCategoryEncounterEndTurn,
	"TriggerTagCategory.PF2.Encounter.EndTurn",
	"Tag to trigger Gameplay Abilities appropriate for the end of a character's turn during an encounter."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagTriggerTagCategoryEncounterLeaveEncounter,
	"TriggerTagCategory.PF2.Encounter.LeaveEncounter",
	"Tag to trigger Gameplay Abilities appropriate for when a character leaves an encounter."
)

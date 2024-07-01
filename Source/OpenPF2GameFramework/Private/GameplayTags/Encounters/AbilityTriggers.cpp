// OpenPF2 Game Framework for Unreal Engine, Copyright 2022-2024, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "GameplayTags/Encounters/AbilityTriggers.h"

// =====================================================================================================================
// Tags that trigger Encounter-related Gameplay Abilities.
// =====================================================================================================================
UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagTriggerTagCategoryEncountersEnterEncounter,
	"TriggerTagCategory.Encounters.EnterEncounter",
	"Tag to trigger Gameplay Abilities appropriate for when a character enters an encounter."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagTriggerTagCategoryEncountersStartTurn,
	"TriggerTagCategory.Encounters.StartTurn",
	"Tag to trigger Gameplay Abilities appropriate for the start of a character's turn during an encounter."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagTriggerTagCategoryEncountersEndTurn,
	"TriggerTagCategory.Encounters.EndTurn",
	"Tag to trigger Gameplay Abilities appropriate for the end of a character's turn during an encounter."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagTriggerTagCategoryEncountersLeaveEncounter,
	"TriggerTagCategory.Encounters.LeaveEncounter",
	"Tag to trigger Gameplay Abilities appropriate for when a character leaves an encounter."
)

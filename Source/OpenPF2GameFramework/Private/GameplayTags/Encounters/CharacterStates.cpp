// OpenPF2 Game Framework for Unreal Engine, Copyright 2022-2024, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "GameplayTags/Encounters/CharacterStates.h"

// =====================================================================================================================
// Tags that apply to characters during encounters.
// =====================================================================================================================
UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagEncounterCharacterStates,
	"PF2.Encounter.CharacterState",
	"Tags that convey the state of a character during encounters."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagEncounterCharacterStateTurnActive,
	"PF2.Encounter.CharacterState.TurnActive",
	"Tag applied to a character whose turn is active."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagEncounterCharacterStatePointsRefreshFrozen,
	"PF2.Encounter.CharacterState.PointsRefreshFrozen",
	"Tag applied to a character who cannot presently accrue action points."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagEncounterCharacterStateCooldownNextTurn,
	"PF2.Encounter.CharacterState.Cooldown.NextTurn",
	"Tag applied to a character who is currently on a cooldown waiting for their next turn to start."
)

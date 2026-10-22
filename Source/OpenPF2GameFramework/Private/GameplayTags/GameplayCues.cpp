// OpenPF2 Game Framework for Unreal Engine, Copyright 2023-2024, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "GameplayTags/GameplayCues.h"

// =====================================================================================================================
// Gameplay Cues that provide visual FX and sound FX in response to PF2 effect activations.
// =====================================================================================================================
UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagGameplayCues,
	"GameplayCue.PF2",
	"Gameplay cues that provide visual and sound FX in response to PF2 effect activations."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagGameplayCueCharacters,
	"GameplayCue.PF2.Character",
	"Gameplay cues fired in response to actions taken by a character."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagGameplayCueCharacterInflictDamage,
	"GameplayCue.PF2.Character.InflictDamage",
	"Gameplay cue fired whenever one character inflicts damage on another."
)

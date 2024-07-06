// OpenPF2 Game Framework for Unreal Engine, Copyright 2021-2024, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "GameplayTags/GameplayAbilities/ActivationMetadata.h"

// =====================================================================================================================
// Tags that identify additional metadata that has been passed along for an ability activation.
// =====================================================================================================================
UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagGameplayAbilityActivationMetadata,
	"PF2.GameplayAbility.ActivationMetadata",
	"Tags that identify additional metadata that has been passed along for an ability activation."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagGameplayAbilityActivationMetadataHasTargetCharacter,
	"PF2.GameplayAbility.ActivationMetadata.HasTarget.Character",
	"Tag that a Gameplay Ability activation includes a target character (for healing or attack) chosen by the player."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagGameplayAbilityActivationMetadataHasTargetLocation,
	"PF2.GameplayAbility.ActivationMetadata.HasTarget.Location",
	"Tag that a Gameplay Ability activation includes a target map location chosen by the player."
)

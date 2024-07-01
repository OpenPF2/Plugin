// OpenPF2 Game Framework for Unreal Engine, Copyright 2021-2024, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "GameplayTags/GameplayAbilities/AbilityTypes.h"

// =====================================================================================================================
// Tags that Identify Gameplay Ability Types
// =====================================================================================================================
UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagGameplayAbilityTypeAbilityBoost,
	"GameplayAbility.Type.AbilityBoost",
	"Tag applied to Gameplay Abilities that offer a character the opportunity to boost an ability score."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagGameplayAbilityTypeDefaultMovement,
	"GameplayAbility.Type.DefaultMovement",
	"Tag applied to Gameplay Abilities that perform the default type of movement for a character."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagGameplayAbilityTypeDefaultFaceTarget,
	"GameplayAbility.Type.DefaultFaceTarget",
	"Tag applied to Gameplay Abilities that have a character rotate to face another actor."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagGameplayAbilityTypeQueueableAction,
	"GameplayAbility.Type.QueueableAction",
	"Tag applied to Gameplay Abilities that can be queued during encounters. This should also be used as a blocking tag to prevent it from being run concurrently with other actions at the time it is de-queued."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagGameplayAbilityTypeDirectlyInvokable,
	"GameplayAbility.Type.DirectlyInvokable",
	"Tag applied to Gameplay Abilities that can be directly invoked by the player (e.g., from an ability dialog or input binding)."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagGameplayAbilityTypeBlocksEndOfTurn,
	"GameplayAbility.Type.BlocksEndOfTurn",
	"Tag applied to Gameplay Abilities that prevent a character's turn from ending while they are active (e.g., an attack that is in progress)."
)

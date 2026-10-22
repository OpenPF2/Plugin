// OpenPF2 Game Framework for Unreal Engine, Copyright 2021-2024, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "GameplayTags/GameplayAbilities/AbilityTypes.h"

// =====================================================================================================================
// Tags that Identify Gameplay Ability Types
// =====================================================================================================================
UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagGameplayAbilityTypes,
	"PF2.GameplayAbility.Type",
	"Tags applied to Gameplay Abilities to indicate their type."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagGameplayAbilityTypeAbilityBoost,
	"PF2.GameplayAbility.Type.AbilityBoost",
	"Tag applied to Gameplay Abilities that offer a character the opportunity to boost an ability score."
)

/**
 * The name of the tag that designates an ability the default movement ability.
 *
 * This ability is used to move a character to a location, such as within range of another actor/character.
 */
UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagGameplayAbilityTypeDefaultMovement,
	"PF2.GameplayAbility.Type.DefaultMovement",
	"Tag applied to Gameplay Abilities that perform the default type of movement for a character."
)

/**
 * The name of the tag that designates an ability the default "face target" ability.
 *
 * This ability is used to rotate a character to face another actor/character.
 */
UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagGameplayAbilityTypeDefaultFaceTarget,
	"PF2.GameplayAbility.Type.DefaultFaceTarget",
	"Tag applied to Gameplay Abilities that have a character rotate to face another actor."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagGameplayAbilityTypeQueueableAction,
	"PF2.GameplayAbility.Type.QueueableAction",
	"Tag applied to Gameplay Abilities that can be queued during encounters. This should also be used as a blocking tag to prevent it from being run concurrently with other actions at the time it is de-queued."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagGameplayAbilityTypeDirectlyInvokable,
	"PF2.GameplayAbility.Type.DirectlyInvokable",
	"Tag applied to Gameplay Abilities that can be directly invoked by the player (e.g., from an ability dialog or input binding)."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagGameplayAbilityTypeBlocksEndOfTurn,
	"PF2.GameplayAbility.Type.BlocksEndOfTurn",
	"Tag applied to Gameplay Abilities that prevent a character's turn from ending while they are active (e.g., an attack that is in progress)."
)

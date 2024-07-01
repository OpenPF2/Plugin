// OpenPF2 Game Framework for Unreal Engine, Copyright 2021-2024, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "GameplayTags/GameplayAbilities/WaitForEvents.h"

// =====================================================================================================================
// Tags that identify events abilities can wait for during their activation.
// =====================================================================================================================
UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagGameplayAbilityGameplayEventDamageReceived,
	"GameplayAbility.GameplayEvent.DamageReceived",
	"Tag on a GameplayEvent sent to a character to notify passive condition check GAs that the character has received damage."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagGameplayAbilityGameplayEventFacingComplete,
	"GameplayAbility.GameplayEvent.FacingComplete",
	"Tag on a GameplayEvent sent to a character to notify the active ability that the character is now oriented properly for an attack to proceed against a target."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagGameplayAbilityGameplayEventHitPointsChanged,
	"GameplayAbility.GameplayEvent.HitPointsChanged",
	"Tag on a GameplayEvent sent to a character to notify passive condition check GAs that the character's hit points have changed."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagGameplayAbilityGameplayEventMontageWeaponHit,
	"GameplayAbility.GameplayEvent.Montage.WeaponHit",
	"Tag on a GameplayEvent emitted during an attack montage at the point that the weapon should make contact with an enemy."
)
// OpenPF2 Game Framework for Unreal Engine, Copyright 2021-2024, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "GameplayTags/GameplayEffects/SetByCallerParameters.h"

// =====================================================================================================================
// Parameters passed in to "Set by caller" GEs
// =====================================================================================================================
UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagGameplayEffectParameterDamage,
	"GameplayEffect.Parameter.Damage",
	"The parameter passed in to a dynamic damage GE, to control the amount of damage inflicted."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagGameplayEffectParameterResistance,
	"GameplayEffect.Parameter.Resistance",
	"The parameter passed in to a dynamic resistance GE, to control the amount of damage resistance."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagGameplayEffectParameterHealing,
	"GameplayEffect.Parameter.Healing",
	"The parameter passed in to a dynamic healing GE, to control the amount of hit points granted to the character."
)

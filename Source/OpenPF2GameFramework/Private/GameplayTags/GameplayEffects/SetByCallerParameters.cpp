// OpenPF2 Game Framework for Unreal Engine, Copyright 2021-2024, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "GameplayTags/GameplayEffects/SetByCallerParameters.h"

// =====================================================================================================================
// Parameters passed into "Set by caller" GEs.
// =====================================================================================================================
UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagGameplayEffectParameters,
	"PF2.GameplayEffect.Parameter",
	"Parameters passed into 'Set by caller' GEs."
)

/**
 * The tag for the parameter that is used to pass a dynamic damage amount into the calculation.
 *
 * The parameter is typically read from a set-by-caller tag-based value so that GAs can populate damage dynamically,
 * unless the GE is expected to hard-code a specific amount of damage or read it from a data table.
 */
UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagGameplayEffectParameterDamage,
	"PF2.GameplayEffect.Parameter.Damage",
	"The parameter passed in to a dynamic damage GE, to control the amount of damage inflicted."
)

/**
 * The tag that is used to pass a dynamic resistance amount into the calculation.
 *
 * The parameter should be provided via an attribute-based modifier that reads it from the appropriate resistance
 * attribute of the character's attribute set (e.g., typically an attribute having a name that starts with "Rst", such
 * as "RstPhysicalBludgeoning", "RstEnergyCold", etc.).
 */
UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagGameplayEffectParameterResistance,
	"PF2.GameplayEffect.Parameter.Resistance",
	"The parameter passed in to a dynamic resistance GE, to control the amount of damage resistance."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagGameplayEffectParameterHealing,
	"PF2.GameplayEffect.Parameter.Healing",
	"The parameter passed in to a dynamic healing GE, to control the amount of hit points granted to the character."
)

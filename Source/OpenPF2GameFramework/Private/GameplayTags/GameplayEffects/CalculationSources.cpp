// OpenPF2 Game Framework for Unreal Engine, Copyright 2021-2024, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "GameplayTags/GameplayEffects/CalculationSources.h"

// =====================================================================================================================
// "Source" tags passed in from Blueprints to calculate stats.
//
// These should not be used on weapons, characters, or other objects that appear in the world.
// =====================================================================================================================
UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagGameplayEffectCalculationSource,
	"PF2.GameplayEffect.CalculationSource",
	"'Source' tags passed in from Blueprints to calculate stats."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagGameplayEffectCalculationSourceInitiative,
	"PF2.GameplayEffect.CalculationSource.Initiative",
	"Source tag passed in when a character's initiative in an encounter is being determined."
)

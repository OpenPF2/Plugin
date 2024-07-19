// OpenPF2 Game Framework for Unreal Engine, Copyright 2021-2024, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "GameplayTags/GameplayEffects/WeightGroups.h"

// =====================================================================================================================
// Weights used to control the order that GEs are applied to an OpenPF2 character.
// =====================================================================================================================
UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagGameplayEffectWeightGroups,
	"PF2.GameplayEffect.WeightGroup",
	"[SOON TO BE DEPRECATED] Weights used to control the order that GEs are applied to an OpenPF2 character."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagGameplayEffectWeightGroup00_InitializeBaseStats,
	"PF2.GameplayEffect.WeightGroup.00_InitializeBaseStats",
	"The weight group used for GEs that initialize base stats."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagGameplayEffectWeightGroup05_PostInitializeBaseStats,
	"PF2.GameplayEffect.WeightGroup.05_PostInitializeBaseStats",
	"The weight group used for GEs provided by the game designer that have to run right after base stats."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagGameplayEffectWeightGroup10_ManagedEffects,
	"PF2.GameplayEffect.WeightGroup.10_ManagedEffects",
	"The weight group used for GEs generated from other values on this character (managed by ASC logic)."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagGameplayEffectWeightGroup15_PreAbilityBoosts,
	"PF2.GameplayEffect.WeightGroup.15_PreAbilityBoosts",
	"The default weight group for custom, passive GEs from a game designer; applied before ability boosts."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagGameplayEffectWeightGroup20_AbilityBoosts,
	"PF2.GameplayEffect.WeightGroup.20_AbilityBoosts",
	"The weight group used for ability boosts selected by the player or a game designer."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagGameplayEffectWeightGroup25_PreFinalizeStats,
	"PF2.GameplayEffect.WeightGroup.25_PreFinalizeStats",
	"The weight group used for custom GEs provided by the game designer that must run before the last group of stats GEs."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagGameplayEffectWeightGroup30_FinalizeStats,
	"PF2.GameplayEffect.WeightGroup.30_FinalizeStats",
	"The weight group used for GEs that need to run last because they heavily depend on the results of earlier GEs."
)

// OpenPF2 Game Framework for Unreal Engine, Copyright 2021-2024, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#pragma once

#include <NativeGameplayTags.h>

// =====================================================================================================================
// Weights used to control the order that GEs are applied to an OpenPF2 character.
//
// @todo Deprecate and replace with a simpler system in https://github.com/OpenPF2/Plugin/issues/61.
// =====================================================================================================================
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagGameplayEffectWeightGroups)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagGameplayEffectWeightGroup00_InitializeBaseStats)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagGameplayEffectWeightGroup05_PostInitializeBaseStats)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagGameplayEffectWeightGroup10_ManagedEffects)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagGameplayEffectWeightGroup15_PreAbilityBoosts)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagGameplayEffectWeightGroup20_AbilityBoosts)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagGameplayEffectWeightGroup25_PreFinalizeStats)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagGameplayEffectWeightGroup30_FinalizeStats)

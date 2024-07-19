// OpenPF2 Game Framework for Unreal Engine, Copyright 2022-2024, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#pragma once

#include <NativeGameplayTags.h>

// =====================================================================================================================
// Tags that trigger Gameplay Abilities that can be used at any time.
// =====================================================================================================================
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagTriggerTagCategoryAnytime)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagTriggerTagCategoryAnytimeAbilityBoost)

// =====================================================================================================================
// Tags that trigger Encounter-related Gameplay Abilities.
// =====================================================================================================================
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagTriggerTagCategoryEncounters)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagTriggerTagCategoryEncounterEnterEncounter)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagTriggerTagCategoryEncounterStartTurn)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagTriggerTagCategoryEncounterEndTurn)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagTriggerTagCategoryEncounterLeaveEncounter)

// OpenPF2 Game Framework for Unreal Engine, Copyright 2021-2024, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#pragma once

#include <NativeGameplayTags.h>

// =====================================================================================================================
// "Source" Tags passed in from Blueprints to calculate stats.
//
// These should not be used on weapons, characters, or other objects that appear in the world.
// =====================================================================================================================
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagGameplayEffectCalculationSourceInitiative)

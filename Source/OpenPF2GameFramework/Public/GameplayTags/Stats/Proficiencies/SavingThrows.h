// OpenPF2 Game Framework for Unreal Engine, Copyright 2021-2024, Guy Elsmore-Paddock. All Rights Reserved.
//
// Content from Pathfinder 2nd Edition is licensed under the Open Game License (OGL) v1.0a, subject to the following:
//	- Open Game License v 1.0a, Copyright 2000, Wizards of the Coast, Inc.
//	- System Reference Document, Copyright 2000, Wizards of the Coast, Inc.
//	- Pathfinder Core Rulebook (Second Edition), Copyright 2019, Paizo Inc.
//
// Except for material designated as Product Identity, the game mechanics and logic in this file are Open Game Content,
// as defined in the Open Game License version 1.0a, Section 1(d) (see accompanying LICENSE.TXT). No portion of this
// file other than the material designated as Open Game Content may be reproduced in any form without written
// permission.

#pragma once

#include <NativeGameplayTags.h>

// =====================================================================================================================
// Proficiency Ranks for Saving Throws (avoiding danger or otherwise withstanding an assault to mind or body).
// =====================================================================================================================
// Sources:
//	- Pathfinder 2E Core Rulebook, Chapter 1: "Introduction", page 11, "Playing the Game".
//	- Pathfinder 2E Core Rulebook, Chapter 1: "Introduction", page 13, "Saving Throw (Save)" and "Proficiency".
//	- Pathfinder 2E Core Rulebook, Appendix, page 624, "Saving Throws".


// === Fortitude
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencySavingThrowFortitude)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencySavingThrowFortitudeUntrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencySavingThrowFortitudeTrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencySavingThrowFortitudeExpert)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencySavingThrowFortitudeMaster)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencySavingThrowFortitudeLegendary)

// === Reflex
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencySavingThrowReflex)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencySavingThrowReflexUntrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencySavingThrowReflexTrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencySavingThrowReflexExpert)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencySavingThrowReflexMaster)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencySavingThrowReflexLegendary)

// === Will
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencySavingThrowWill)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencySavingThrowWillUntrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencySavingThrowWillTrained)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencySavingThrowWillExpert)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencySavingThrowWillMaster)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagProficiencySavingThrowWillLegendary)

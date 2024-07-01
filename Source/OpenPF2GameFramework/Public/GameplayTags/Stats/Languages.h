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
// Common Languages - Languages regularly encountered in most places, even among those who aren’t native speakers.
// =====================================================================================================================
// Source: Pathfinder 2E Core Rulebook, page 65, Table 2-1: Common Languages.
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagLanguageCommonCommon)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagLanguageCommonDraconic)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagLanguageCommonDwarven)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagLanguageCommonElven)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagLanguageCommonGnomish)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagLanguageCommonGoblin)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagLanguageCommonHalfling)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagLanguageCommonJotun)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagLanguageCommonOrcish)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagLanguageCommonSylvan)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagLanguageCommonUndercommon)

// =====================================================================================================================
// Uncommon Languages - Languages most frequently spoken by native speakers, but also by certain scholars and others
// interested in the associated cultures.
// =====================================================================================================================
// Source: Pathfinder 2E Core Rulebook, page 65, Table 2-2: Uncommon Languages.
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagLanguageUncommonAbyssal)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagLanguageUncommonAklo)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagLanguageUncommonAquan)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagLanguageUncommonAuran)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagLanguageUncommonCelestial)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagLanguageUncommonGnoll)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagLanguageUncommonIgnan)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagLanguageUncommonInfernal)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagLanguageUncommonNecril)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagLanguageUncommonShadowtongue)
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagLanguageUncommonTerran)

// =====================================================================================================================
// Secret Languages (e.g., "Druidic")
//
// Druidic is a secret language, and is available only to characters who are druids. In fact, druids are prohibited from
// teaching the language to non-druids.
// =====================================================================================================================
// Source: Pathfinder 2E Core Rulebook, page 65, Table 2-3: Secret Languages.
OPENPF2GAMEFRAMEWORK_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pf2TagLanguageSecretDruidic)

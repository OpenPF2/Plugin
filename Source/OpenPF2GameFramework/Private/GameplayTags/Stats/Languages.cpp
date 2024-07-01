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
// Common Languages - "Languages that are common are regularly encountered in most places, even among those who aren’t native speakers."
// Source: Pathfinder 2E Core Rulebook, page 65, Table 2-1: Common Languages.

#include "GameplayTags/Stats/Languages.h"

// =====================================================================================================================
// Common Languages - Languages regularly encountered in most places, even among those who aren’t native speakers.
// =====================================================================================================================
// Source: Pathfinder 2E Core Rulebook, page 65, Table 2-1: Common Languages.
UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagLanguageCommonCommon,
	"Language.Common.Common",
	"Language spoken by humans, dwarves, elves, halflings, and other common ancestries."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagLanguageCommonDraconic,
	"Language.Common.Draconic",
	"Language spoken by dragons, reptilian humanoids."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagLanguageCommonDwarven,
	"Language.Common.Dwarven",
	"Language spoken by dwarves."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagLanguageCommonElven,
	"Language.Common.Elven",
	"Language spoken by elves, half-elves."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagLanguageCommonGnomish,
	"Language.Common.Gnomish",
	"Language spoken by gnomes."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagLanguageCommonGoblin,
	"Language.Common.Goblin",
	"Language spoken by goblins, hobgoblins, bugbears."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagLanguageCommonHalfling,
	"Language.Common.Halfling",
	"Language spoken by halflings."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagLanguageCommonJotun,
	"Language.Common.Jotun",
	"Language spoken by giants, ogres, trolls, ettins, cyclopes."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagLanguageCommonOrcish,
	"Language.Common.Orcish",
	"Language spoken by orcs, half-orcs."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagLanguageCommonSylvan,
	"Language.Common.Sylvan",
	"Language spoken by fey, centaurs, plant creatures."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagLanguageCommonUndercommon,
	"Language.Common.Undercommon",
	"Language spoken by drow, duergars, xulgaths."
)

// =====================================================================================================================
// Uncommon Languages - Languages most frequently spoken by native speakers, but also by certain scholars and others
// interested in the associated cultures.
// =====================================================================================================================
// Source: Pathfinder 2E Core Rulebook, page 65, Table 2-2: Uncommon Languages.
UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagLanguageUncommonAbyssal,
	"Language.Uncommon.Abyssal",
	"Language spoken by demons."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagLanguageUncommonAklo,
	"Language.Uncommon.Aklo",
	"Language spoken by deros, evil fey, otherworldly monsters."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagLanguageUncommonAquan,
	"Language.Uncommon.Aquan",
	"Language spoken by aquatic creatures, water elemental creatures."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagLanguageUncommonAuran,
	"Language.Uncommon.Auran",
	"Language spoken by air elemental creatures, flying creatures."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagLanguageUncommonCelestial,
	"Language.Uncommon.Celestial",
	"Language spoken by angels."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagLanguageUncommonGnoll,
	"Language.Uncommon.Gnoll",
	"Language spoken by gnolls."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagLanguageUncommonIgnan,
	"Language.Uncommon.Ignan",
	"Language spoken by fire elemental creatures."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagLanguageUncommonInfernal,
	"Language.Uncommon.Infernal",
	"Language spoken by devils."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagLanguageUncommonNecril,
	"Language.Uncommon.Necril",
	"Language spoken by ghouls, intelligent undead."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagLanguageUncommonShadowtongue,
	"Language.Uncommon.Shadowtongue",
	"Language spoken by nidalese, Shadow Plane creatures."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagLanguageUncommonTerran,
	"Language.Uncommon.Terran",
	"Language spoken by earth elemental creatures."
)

// =====================================================================================================================
// Secret Languages (e.g., "Druidic")
//
// Druidic is a secret language, and is available only to characters who are druids. In fact, druids are prohibited from
// teaching the language to non-druids.
// =====================================================================================================================
// Source: Pathfinder 2E Core Rulebook, page 65, Table 2-3: Secret Languages.
UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagLanguageSecretDruidic,
	"Language.Secret.Druidic",
	"Language spoken by druids."
)

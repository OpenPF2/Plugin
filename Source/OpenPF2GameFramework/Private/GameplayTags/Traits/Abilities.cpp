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

#include "GameplayTags/Traits/Abilities.h"

// =====================================================================================================================
// Ability Traits - Keywords that convey information about rules elements that interact with abilities.
// =====================================================================================================================
// Source: Pathfinder 2E Core Rulebook, Glossary, pages 628-638.
UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagTraitAbilities,
	"PF2.Trait.Ability",
	"Keywords that convey information about rules elements that interact with abilities."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagTraitAbilityAlchemist,
	"PF2.Trait.Ability.Alchemist",
	"This indicates abilities from the alchemist class."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagTraitAbilityAttack,
	"PF2.Trait.Ability.Attack",
	"An ability with this trait involves an attack. For each attack you make beyond the first on your turn, you take a multiple attack penalty."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagTraitAbilityBarbarian,
	"PF2.Trait.Ability.Barbarian",
	"This indicates abilities from the barbarian class."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagTraitAbilityBard,
	"PF2.Trait.Ability.Bard",
	"This indicates abilities from the bard class."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagTraitAbilityChampion,
	"PF2.Trait.Ability.Champion",
	"This indicates abilities from the champion class."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagTraitAbilityCleric,
	"PF2.Trait.Ability.Cleric",
	"This indicates abilities from the cleric class."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagTraitAbilityCommon,
	"PF2.Trait.Ability.Common",
	"Anything that doesn't list another rarity trait (uncommon, rare, or unique) automatically has the common trait. This rarity indicates that an ability is available to all players who meet the prerequisites for it."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagTraitAbilityDruid,
	"PF2.Trait.Ability.Druid",
	"This indicates abilities from the druid class."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagTraitAbilityFighter,
	"PF2.Trait.Ability.Fighter",
	"This indicates abilities from the fighter class."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagTraitAbilityIncapacitation,
	"PF2.Trait.Ability.Incapacitation",
	"An ability with this trait can take a character completely out of the fight or even kill them, and it's harder to use on a more powerful character."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagTraitAbilityMonk,
	"PF2.Trait.Ability.Monk",
	"Abilities with this trait are from the monk class."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagTraitAbilityRanger,
	"PF2.Trait.Ability.Ranger",
	"This indicates abilities from the ranger class."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagTraitAbilityRogue,
	"PF2.Trait.Ability.Rogue",
	"This indicates abilities from the rogue class."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagTraitAbilitySecret,
	"PF2.Trait.Ability.Secret",
	"The GM rolls the check for this ability in secret."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagTraitAbilitySorcerer,
	"PF2.Trait.Ability.Sorcerer",
	"This indicates abilities from the sorcerer class."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagTraitAbilityWizard,
	"PF2.Trait.Ability.Wizard",
	"This indicates abilities from the wizard class."
)

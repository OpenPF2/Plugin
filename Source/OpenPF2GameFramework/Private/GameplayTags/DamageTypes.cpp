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

#include "GameplayTags/DamageTypes.h"

// =====================================================================================================================
// Damage types
// =====================================================================================================================
// Source: Pathfinder 2E Core Rulebook, Chapter 9, page 452, "Damage Types".
UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagDamageTypePhysical,
	"DamageType.Physical",
	"Damage dealt by weapons, many physical hazards, and a handful of spells is collectively called physical damage. The main types of physical damage are bludgeoning, piercing, and slashing."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagDamageTypePhysicalBludgeoning,
	"DamageType.Physical.Bludgeoning",
	"Bludgeoning (B) damage comes from weapons and hazards that deal blunt-force trauma, like a hit from a club or being dashed against rocks."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagDamageTypePhysicalPiercing,
	"DamageType.Physical.Piercing",
	"Piercing (P) damage is dealt from stabs and punctures, whether from a dragon's fangs or the thrust of a spear."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagDamageTypePhysicalSlashing,
	"DamageType.Physical.Slashing",
	"Slashing (S) damage is delivered by a cut, be it the swing of the sword or the blow from a scythe blades trap."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagDamageTypeEnergy,
	"DamageType.Energy",
	"Many spells and other magical effects deal energy damage. Energy damage is also dealt from effects in the world, such as the biting cold of a blizzard to a raging forest fire. The main types of energy damage are acid, cold, electricity, fire, and sonic."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagDamageTypeEnergyAcid,
	"DamageType.Energy.Acid",
	"Acid damage can be delivered by gases, liquids, and certain solids that dissolve flesh, and sometimes harder materials."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagDamageTypeEnergyCold,
	"DamageType.Energy.Cold",
	"Cold damage freezes material by way of contact with chilling gases and ice. Electricity damage comes from the discharge of powerful lightning and sparks."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagDamageTypeEnergyElectricity,
	"DamageType.Energy.Electricity",
	"Electricity comes from the discharge of powerful lightning and sparks."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagDamageTypeEnergyFire,
	"DamageType.Energy.Fire",
	"Fire damage burns through heat and combustion."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagDamageTypeEnergySonic,
	"DamageType.Energy.Sonic",
	"Sonic damage assaults matter with high-frequency vibration and sound waves."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagDamageTypeEnergyPositive,
	"DamageType.Energy.Positive",
	"Positive damage harms only undead creatures, withering undead bodies and disrupting incorporeal undead."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagDamageTypeEnergyNegative,
	"DamageType.Energy.Negative",
	"Negative damage saps life, damaging only living creatures."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagDamageTypeEnergyForce,
	"DamageType.Energy.Force",
	"Powerful and pure magical energy can manifest itself as force damage. Few things can resist this type of damage—not even incorporeal creatures such as ghosts and wraiths."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagDamageTypeAlignment,
	"DamageType.Alignment",
	"Weapons and effects keyed to a particular alignment can deal chaotic, evil, good, or lawful damage. These damage types apply only to creatures that have the opposing alignment trait."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagDamageTypeAlignmentChaotic,
	"DamageType.Alignment.Chaotic",
	"Chaotic damage harms only lawful creatures."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagDamageTypeAlignmentEvil,
	"DamageType.Alignment.Evil",
	"Evil damage harms only good creatures."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagDamageTypeAlignmentGood,
	"DamageType.Alignment.Good",
	"Good damage harms only evil creatures."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagDamageTypeAlignmentLawful,
	"DamageType.Alignment.Lawful",
	"Lawful damage harms only chaotic creatures."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagDamageTypeMental,
	"DamageType.Mental",
	"Sometimes an effect can target the mind with enough psychic force to actually deal damage to the creature. When it does, it deals mental damage. Mindless creatures and those with only programmed or rudimentary intelligence are often immune to mental damage and effects."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagDamageTypePoison,
	"DamageType.Poison",
	"Venoms, toxins and the like can deal poison damage, which affects creatures by way of contact, ingestion, inhalation, or injury. In addition to coming from monster attacks, alchemical items, and spells, poison damage is often caused by ongoing afflictions, which follow special rules."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagDamageTypeBleed,
	"DamageType.Bleed",
	"This is persistent damage that represents loss of blood. As such, it has no effect on nonliving creatures or living creatures that don't need blood to live."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagDamageTypePrecision,
	"DamageType.Precision",
	"When a character hits with an ability that grants precision damage, the character increase the attack's listed damage, using the same damage type, rather than tracking a separate pool of damage."
)

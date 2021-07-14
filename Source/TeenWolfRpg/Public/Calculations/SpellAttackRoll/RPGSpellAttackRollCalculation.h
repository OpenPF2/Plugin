// Teen Wolf RPG game logic, Copyright 2021, Teen Wolf RPG. All Rights Reserved.
// Content from Pathfinder 2nd Edition is licensed under the Open Game License (OGL) v1.0a, subject to the following:
//	 - Open Game License v 1.0a, Copyright 2000, Wizards of the Coast, Inc.
//	 - System Reference Document, Copyright 2000, Wizards of the Coast, Inc.
//	 - Pathfinder Core Rulebook (Second Edition), Copyright 2019, Paizo Inc.
// Except for material designated as Product Identity or External Tools, the game mechanics of this Teen Wolf RPG
// product are Open Game Content, as defined in the Open Game License version 1.0a, Section 1(d) (see accompanying
// LICENSE.TXT). No portion of this work other than the material designated as Open Game Content may be reproduced in
// any form without written permission.

#pragma once

#include <CoreMinimal.h>

#include "Calculations/RPGKeyAbilityCalculationBase.h"
#include "RPGSpellAttackRollCalculation.generated.h"

/**
 * MMC that calculates the "Spell Attack Roll" stat.
 *
 * From the Pathfinder 2E Core Rulebook, page 447:
 * "If you cast spells, you might be able to make a spell attack roll. These rolls are usually made when a spell makes
 * an attack against a creature’s AC."
 * ...
 * "Determine the spell attack roll with the following formula:
 * Spell attack roll result =
 * d20 roll + ability modifier used for spellcasting + proficiency bonus + other bonuses + penalties"
 *
 * TODO: Figure out if we need to accommodate this, and how:
 * "The ability modifier for a spell attack roll depends on how you gained access to your spells. If your class grants
 * you spellcasting, use your key ability modifier. Innate spells use your Charisma modifier unless the ability that
 * granted them states otherwise. Focus spells and other sources of spells specify which ability modifier you use for
 * spell attack rolls in the ability that granted them. If you have spells from multiple sources or traditions, you
 * might use different ability modifiers for spell attack rolls for these different sources of spells."
 */
UCLASS()
class TEENWOLFRPG_API URPGSpellAttackRollCalculation : public URPGKeyAbilityCalculationBase
{
	GENERATED_BODY()

public:
	/**
	 * Constructor for URPGSpellAttackRollCalculation.
	 */
	explicit URPGSpellAttackRollCalculation();
};

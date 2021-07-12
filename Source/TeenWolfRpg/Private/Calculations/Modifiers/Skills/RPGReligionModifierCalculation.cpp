// Teen Wolf RPG game logic, Copyright 2021, Teen Wolf RPG. All Rights Reserved.
// Content from Pathfinder 2nd Edition is licensed under the Open Game License (OGL) v1.0a, subject to the following:
//	 - Open Game License v 1.0a, Copyright 2000, Wizards of the Coast, Inc.
//	 - System Reference Document, Copyright 2000, Wizards of the Coast, Inc.
//	 - Pathfinder Core Rulebook (Second Edition), Copyright 2019, Paizo Inc.
// Except for material designated as Product Identity or External Tools, the game mechanics of this Teen Wolf RPG
// product are Open Game Content, as defined in the Open Game License version 1.0a, Section 1(d) (see accompanying
// LICENSE.TXT). No portion of this work other than the material designated as Open Game Content may be reproduced in
// any form without written permission.

#include "Abilities/RPGAttributeSet.h"
#include "Calculations/Modifiers/Skills/RPGReligionModifierCalculation.h"

URPGReligionModifierCalculation::URPGReligionModifierCalculation() :
	URPGModifierCalculationBase(
		URPGAttributeSet::GetAbWisdomModifierAttribute(),
		FString("Skill.Religion")
	)
{
}

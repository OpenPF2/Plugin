// OpenPF2 Game Framework for Unreal Engine, Copyright 2021-2024, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "CharacterStats/PF2SpellDifficultyClassCalculation.h"

#include "GameplayTags/Stats/KeyAbilities.h"
#include "GameplayTags/Stats/Proficiencies/SpellDc.h"

UPF2SpellDifficultyClassCalculation::UPF2SpellDifficultyClassCalculation() :
	UPF2KeyAbilityTemlCalculationBase(Pf2TagProficiencySpellDc, Pf2TagSpellcastingAbilities, 10.0f)
{
}

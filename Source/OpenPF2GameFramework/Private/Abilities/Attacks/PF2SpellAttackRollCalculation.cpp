// OpenPF2 Game Framework for Unreal Engine, Copyright 2021-2024, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "Abilities/Attacks/PF2SpellAttackRollCalculation.h"

#include "GameplayTags/Stats/KeyAbilities.h"
#include "GameplayTags/Stats/Proficiencies/SpellAttacks.h"

UPF2SpellAttackRollCalculation::UPF2SpellAttackRollCalculation() :
	UPF2KeyAbilityTemlCalculationBase(Pf2TagProficiencySpellAttack, Pf2TagSpellcastingAbilities)
{
}

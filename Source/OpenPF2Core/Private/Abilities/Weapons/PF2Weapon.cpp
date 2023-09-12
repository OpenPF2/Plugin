// OpenPF2 for UE Game Logic, Copyright 2021-2023, Guy Elsmore-Paddock. All Rights Reserved.
//
// Content from Pathfinder 2nd Edition is licensed under the Open Game License (OGL) v1.0a, subject to the following:
//   - Open Game License v 1.0a, Copyright 2000, Wizards of the Coast, Inc.
//   - System Reference Document, Copyright 2000, Wizards of the Coast, Inc.
//   - Pathfinder Core Rulebook (Second Edition), Copyright 2019, Paizo Inc.
//
// Except for material designated as Product Identity, the game mechanics and logic in this file are Open Game Content,
// as defined in the Open Game License version 1.0a, Section 1(d) (see accompanying LICENSE.TXT). No portion of this
// file other than the material designated as Open Game Content may be reproduced in any form without written
// permission.

#include "Abilities/Weapons/PF2Weapon.h"

#include "Abilities/PF2CharacterAbilitySystemInterface.h"
#include "Calculations/PF2TemlCalculation.h"
#include "Libraries/PF2DiceLibrary.h"

float UPF2Weapon::GetAbilityModifierValue(const IPF2CharacterAbilitySystemInterface* CharacterAsc,
                                          const EPF2CharacterAbilityScoreType        AbilityScoreType)
{
	const TMap<EPF2CharacterAbilityScoreType, FPF2AttributeModifierSnapshot> AbilityScoreValues =
		CharacterAsc->GetAbilityScoreValues();

	return AbilityScoreValues[AbilityScoreType].ModifierValue;
}

float UPF2Weapon::CalculateAttackRoll(const IPF2CharacterAbilitySystemInterface* CharacterAsc)
{
	const int32                 CharacterLevel = CharacterAsc->GetCharacterLevel();
	const FGameplayTagContainer CharacterTags  = CharacterAsc->GetActiveGameplayTags();
	const int32                 RollResult     = UPF2DiceLibrary::RollSum(1, 20);

	const float AttackAbilityModifier = GetAbilityModifierValue(CharacterAsc, this->AttackAbilityModifierType);

	float WeaponProficiencyBonus = 0;

	for (const FGameplayTag& ProficiencyTagPrefix : this->ProficiencyTagPrefixes)
	{
		const FPF2TemlCalculation* Calculation =
			new FPF2TemlCalculation(ProficiencyTagPrefix, &CharacterTags, CharacterLevel);

		WeaponProficiencyBonus = FMath::Max(WeaponProficiencyBonus, Calculation->GetValue());
	}

	// Melee attack modifier = Strength modifier (or optionally Dexterity for a finesse weapon) + proficiency bonus +
	// other bonuses + penalties
	//
	// Ranged attack modifier = Dexterity modifier + proficiency bonus + other bonuses + penalties
	//
	// Source: Pathfinder 2E Core Rulebook, Chapter 6, page 278, "Attack Rolls".
	return RollResult + AttackAbilityModifier + WeaponProficiencyBonus;
}

float UPF2Weapon::CalculateDamageRoll(const IPF2CharacterAbilitySystemInterface* CharacterAsc)
{
	const int32 RollResult            = UPF2DiceLibrary::RollStringSum(this->DamageDie);
	const float DamageAbilityModifier = GetAbilityModifierValue(CharacterAsc, this->DamageAbilityModifierType);

	// Melee damage roll = damage die of weapon or unarmed attack + Strength modifier + bonuses + penalties
	// Ranged damage roll = damage die of weapon + Strength modifier for thrown weapons + bonuses + penalties
	//
	// Source: Pathfinder 2E Core Rulebook, Chapter 6, page 278, "Damage Rolls".
	return RollResult + DamageAbilityModifier;
}

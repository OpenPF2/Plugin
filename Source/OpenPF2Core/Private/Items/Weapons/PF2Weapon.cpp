// OpenPF2 for UE Game Logic, Copyright 2021-2023, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "Items/Weapons/PF2Weapon.h"

#include "PF2DamageCauseWrapper.h"

#include "Abilities/PF2CharacterAbilitySystemInterface.h"

#include "Libraries/PF2AttackStatLibrary.h"

APF2DamageCauseWrapper* UPF2Weapon::ToDamageCauser()
{
	return APF2DamageCauseWrapper::Create(this->GetWorld(), this);
}

float UPF2Weapon::CalculateAttackRoll(const TScriptInterface<IPF2CharacterAbilitySystemInterface>& CharacterAsc)
{
	const int32                 CharacterLevel = CharacterAsc->GetCharacterLevel();
	const FGameplayTagContainer CharacterTags  = CharacterAsc->GetActiveGameplayTags();

	const float AttackAbilityModifier = this->GetAbilityModifierValue(CharacterAsc, this->AttackAbilityModifierType);

	return UPF2AttackStatLibrary::CalculateAttackRoll(
		CharacterLevel,
		CharacterTags,
		AttackAbilityModifier,
		this->ProficiencyTagPrefixes
	);
}

float UPF2Weapon::CalculateDamageRoll(const TScriptInterface<IPF2CharacterAbilitySystemInterface>& CharacterAsc)
{
	const float DamageAbilityModifier = this->GetAbilityModifierValue(CharacterAsc, this->DamageAbilityModifierType);

	return UPF2AttackStatLibrary::CalculateDamageRoll(
		this->DamageDie,
		DamageAbilityModifier
	);
}
float UPF2Weapon::GetAbilityModifierValue(const TScriptInterface<IPF2CharacterAbilitySystemInterface>& CharacterAsc,
                                          const EPF2CharacterAbilityScoreType                          AbilityScoreType)
{
	const TMap<EPF2CharacterAbilityScoreType, FPF2AttributeModifierSnapshot> AbilityScoreValues =
		CharacterAsc->GetAbilityScoreValues();

	return AbilityScoreValues[AbilityScoreType].ModifierValue;
}

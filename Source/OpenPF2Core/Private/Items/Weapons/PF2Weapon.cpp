// OpenPF2 for UE Game Logic, Copyright 2021-2023, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "Items/Weapons/PF2Weapon.h"

#include <GameplayEffectExecutionCalculation.h>

#include "PF2EffectCauseWrapper.h"

#include "Abilities/PF2CharacterAbilitySystemInterface.h"

APF2EffectCauseWrapper* UPF2Weapon::ToEffectCauser(AActor* OwningActor)
{
	return APF2EffectCauseWrapper::Create(OwningActor, this);
}

FGameplayTagContainer UPF2Weapon::GetProficiencyTagPrefixes() const
{
	return this->ProficiencyTagPrefixes;
}

EPF2CharacterAbilityScoreType UPF2Weapon::GetAttackAbilityModifierType() const
{
	return this->AttackAbilityModifierType;
}

EPF2CharacterAbilityScoreType UPF2Weapon::GetDamageAbilityModifierType() const
{
	return this->DamageAbilityModifierType;
}

FName UPF2Weapon::GetDamageDie() const
{
	return this->DamageDie;
}

float UPF2Weapon::CalculateDamageRoll(const FGameplayEffectCustomExecutionParameters& ExecutionParams) const
{
	UAbilitySystemComponent* SourceAsc = ExecutionParams.GetSourceAbilitySystemComponent();

	if (const IPF2CharacterAbilitySystemInterface* CharacterAsc = Cast<IPF2CharacterAbilitySystemInterface>(SourceAsc);
		CharacterAsc == nullptr)
	{
		UE_LOG(
			LogPf2CoreAbilities,
			Error,
			TEXT("Cannot determine damage roll because source ASC is not compatible with OpenPF2.")
		);

		return 0.0f;
	}
	else
	{
		// const float DamageAbilityModifier =
		// 	this->GetAbilityModifierValue(
		// 		PF2InterfaceUtilities::ToScriptInterface(CharacterAsc),
		// 		this->DamageAbilityModifierType
		// 	);
		//
		// return UPF2AttackStatLibrary::CalculateDamageRoll(
		// 	this->DamageDie,
		// 	DamageAbilityModifier
		// );
		return 0.0f;
	}
}

FPrimaryAssetId UPF2Weapon::GetPrimaryAssetId()
{
	return Super::GetPrimaryAssetId();
}

UDataAsset* UPF2Weapon::ToDataAsset()
{
	return Super::ToDataAsset();
}

bool UPF2Weapon::ShouldBeEquippedInAllLinkedSlots()
{
	return Super::ShouldBeEquippedInAllLinkedSlots();
}

FString UPF2Weapon::GetIdForLogs() const
{
	return Super::GetIdForLogs();
}

float UPF2Weapon::GetAbilityModifierValue(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
                                          const EPF2CharacterAbilityScoreType             AbilityScoreType)
{
	// ExecutionParams.AttemptCalculateCapturedAttributeMagnitude();
	return 0.0f;
}

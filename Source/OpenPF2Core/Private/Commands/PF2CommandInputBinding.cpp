// OpenPF2 for UE Game Logic, Copyright 2022, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "Commands/PF2CommandInputBinding.h"

#include "Commands/PF2CharacterCommand.h"

void FPF2CommandInputBinding::GiveAbilityToCharacter(IPF2CharacterInterface* Character)
{
	check(this->Ability != nullptr);

	checkf(
		!this->HasBeenGranted() || (this->GrantedCharacter == Character),
		TEXT("The ability for this binding has already been given to a different character.")
	);

	UAbilitySystemComponent* Asc = Character->GetAbilitySystemComponent();

	this->GrantedAbilitySpecHandle =
		Asc->GiveAbility(FGameplayAbilitySpec(this->Ability, Character->GetCharacterLevel()));

	this->GrantedCharacter = Character;
}

void FPF2CommandInputBinding::InvokeAbility()
{
	if (this->HasBeenGranted())
	{
		UPF2CharacterCommand* Command =
			UPF2CharacterCommand::Create(this->GrantedCharacter, this->GrantedAbilitySpecHandle);

		Command->AttemptExecuteOrQueue();
	}
	else
	{
		UE_LOG(
			LogPf2CoreAbilities,
			Warning,
			TEXT("FPF2CommandInputBinding::InvokeAbility() called on an ability that has not yet been granted ('%s')."),
			*(this->Ability->GetFullName())
		);
	}
}

void FPF2CommandInputBinding::ReleaseAbility()
{
	// Default implementation -- Do nothing.
}

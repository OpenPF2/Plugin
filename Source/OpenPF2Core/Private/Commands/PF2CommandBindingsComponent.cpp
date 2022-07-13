// OpenPF2 for UE Game Logic, Copyright 2022, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "Commands/PF2CommandBindingsComponent.h"

#include <AbilitySystemComponent.h>
#include <Components/InputComponent.h>

#include "Abilities/PF2GameplayAbilityInterface.h"

#include "Commands/PF2CommandInputBinding.h"

#include "Utilities/PF2InterfaceUtilities.h"

void UPF2CommandBindingsComponent::LoadAbilitiesFromCharacter(const TScriptInterface<IPF2CharacterInterface> Character)
{
	this->LoadAbilitiesFromCharacter(PF2InterfaceUtilities::FromScriptInterface(Character));
}

void UPF2CommandBindingsComponent::LoadAbilitiesFromCharacter(IPF2CharacterInterface* Character)
{
	checkf(
		this->Bindings.Num() == 0,
		TEXT("Abilities must be loaded from a character before custom bindings are added.")
	);

	UAbilitySystemComponent* AbilitySystemComponent = Character->GetAbilitySystemComponent();

	for (const FGameplayAbilitySpec& AbilitySpec : AbilitySystemComponent->GetActivatableAbilities())
	{
		const UGameplayAbility*             Ability       = AbilitySpec.Ability;
		const IPF2GameplayAbilityInterface* AbilityIntf   = Cast<IPF2GameplayAbilityInterface>(Ability);
		FName                               DefaultAction;

		if (AbilityIntf != nullptr)
		{
			DefaultAction = AbilityIntf->GetDefaultInputActionMapping();
		}
		else
		{
			// Fallback for interoperability with non-PF2 abilities.
			DefaultAction = FName();
		}

		this->Bindings.Add(FPF2CommandInputBinding(DefaultAction, AbilitySpec, Character));
	}
}

void UPF2CommandBindingsComponent::ConnectToInput(UInputComponent* InputComponent)
{
	for (FPF2CommandInputBinding& Binding : this->Bindings)
	{
		Binding.ConnectToInput(InputComponent);
	}
}

void UPF2CommandBindingsComponent::DisconnectFromInput(UInputComponent* InputComponent)
{
	for (FPF2CommandInputBinding& Binding : this->Bindings)
	{
		Binding.DisconnectFromInput(InputComponent);
	}
}

FString UPF2CommandBindingsComponent::GetIdForLogs() const
{
	// ReSharper disable CppRedundantParentheses
	return FString::Format(
		TEXT("{0}.{1}"),
		{
			*(this->GetOwner()->GetName()),
			*(this->GetName())
		}
	);
}

// OpenPF2 for UE Game Logic, Copyright 2022, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "Commands/PF2CommandBindingsComponent.h"

#include <AbilitySystemComponent.h>
#include <Components/InputComponent.h>

#include "Commands/PF2CommandInputBinding.h"
#include "Utilities/PF2InterfaceUtilities.h"

void UPF2CommandBindingsComponent::GiveAbilitiesToCharacter(const TScriptInterface<IPF2CharacterInterface> Character)
{
	this->GiveAbilitiesToCharacter(PF2InterfaceUtilities::FromScriptInterface(Character));
}

void UPF2CommandBindingsComponent::GiveAbilitiesToCharacter(IPF2CharacterInterface* Character)
{
	for (FPF2CommandInputBinding& Binding : this->Bindings)
	{
		if (!Binding.HasBeenGranted())
		{
			Binding.GiveAbilityToCharacter(Character);
		}
	}
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
		this->Bindings.Add(FPF2CommandInputBinding(FName(), AbilitySpec, Character));
	}
}

void UPF2CommandBindingsComponent::BindToInputComponent(UInputComponent* InputComponent)
{
	for (const FPF2CommandInputBinding& Binding : this->Bindings)
	{
		// Pressed event
 		{
			FInputActionBinding ActionBinding(Binding.ActionName, IE_Pressed);

			ActionBinding.ActionDelegate.GetDelegateForManualSet().BindUObject(
				this,
				&UPF2CommandBindingsComponent::LocalInputPressed,
				Binding
			);

			InputComponent->AddActionBinding(ActionBinding);
		}

		// Released event
		{
			FInputActionBinding ActionBinding(Binding.ActionName, IE_Released);

			ActionBinding.ActionDelegate.GetDelegateForManualSet().BindUObject(
				this,
				&UPF2CommandBindingsComponent::LocalInputReleased,
				Binding
			);

			InputComponent->AddActionBinding(ActionBinding);
		}
	}
}

// ReSharper disable once CppMemberFunctionMayBeStatic
void UPF2CommandBindingsComponent::LocalInputPressed(FPF2CommandInputBinding Binding)
{
	Binding.InvokeAbility();
}

// ReSharper disable once CppMemberFunctionMayBeStatic
void UPF2CommandBindingsComponent::LocalInputReleased(FPF2CommandInputBinding Binding)
{
	Binding.ReleaseAbility();
}

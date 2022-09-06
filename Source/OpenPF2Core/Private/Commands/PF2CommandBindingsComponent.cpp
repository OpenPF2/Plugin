// OpenPF2 for UE Game Logic, Copyright 2022, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "Commands/PF2CommandBindingsComponent.h"

#include <AbilitySystemComponent.h>

#include <Components/InputComponent.h>

#include "PF2CharacterInterface.h"
#include "PF2PlayerControllerInterface.h"

#include "Abilities/PF2GameplayAbilityInterface.h"

#include "Commands/PF2CharacterCommand.h"
#include "Commands/PF2CommandInputBinding.h"

#include "Utilities/PF2InterfaceUtilities.h"
#include "Utilities/PF2LogUtilities.h"

void UPF2CommandBindingsComponent::ClearBindings()
{
	if (this->IsConnectedToInput())
	{
		for (FPF2CommandInputBinding& Binding : this->Bindings)
		{
			Binding.DisconnectFromInput(this->GetInputComponent());
		}
	}

	this->Bindings.Empty();
}

void UPF2CommandBindingsComponent::LoadAbilitiesFromCharacter(const TScriptInterface<IPF2CharacterInterface> Character)
{
	this->LoadAbilitiesFromCharacter(PF2InterfaceUtilities::FromScriptInterface(Character));
}

void UPF2CommandBindingsComponent::LoadAbilitiesFromCharacter(IPF2CharacterInterface* Character)
{
	UAbilitySystemComponent*     AbilitySystemComponent = Character->GetAbilitySystemComponent();
	TArray<FGameplayAbilitySpec> ActivatableAbilities   = AbilitySystemComponent->GetActivatableAbilities();
	int32                        NumMappedAbilities     = 0;

	checkf(
		this->Bindings.Num() == 0,
		TEXT("Abilities must be loaded from a character before custom bindings are added.")
	);

	UE_LOG(
		LogPf2CoreKeyBindings,
		VeryVerbose,
		TEXT("[%s] Loading %d abilities from Character ('%s')."),
		*(PF2LogUtilities::GetHostNetId(this->GetWorld())),
		ActivatableAbilities.Num(),
		*(Character->GetIdForLogs())
	);

	for (const FGameplayAbilitySpec& AbilitySpec : ActivatableAbilities)
	{
		const UGameplayAbility*             Ability       = AbilitySpec.Ability;
		const IPF2GameplayAbilityInterface* AbilityIntf   = Cast<IPF2GameplayAbilityInterface>(Ability);
		FName                               DefaultAction;

		if (AbilityIntf != nullptr)
		{
			DefaultAction = AbilityIntf->GetDefaultInputActionMapping();
			++NumMappedAbilities;
		}
		else
		{
			// Fallback for interoperability with non-PF2 abilities.
			DefaultAction = FName();
		}

		this->Bindings.Add(FPF2CommandInputBinding(DefaultAction, AbilitySpec, Character, this));
	}

	UE_LOG(
		LogPf2CoreKeyBindings,
		VeryVerbose,
		TEXT("[%s] Loaded %d abilities with default action mappings from Character ('%s')."),
		*(PF2LogUtilities::GetHostNetId(this->GetWorld())),
		NumMappedAbilities,
		*(Character->GetIdForLogs())
	);

	if (this->IsConnectedToInput())
	{
		// Wire up all the new bindings.
		this->ConnectToInput(this->GetInputComponent());
	}
}

void UPF2CommandBindingsComponent::ConnectToInput(UInputComponent* NewInputComponent)
{
	checkf(
		!this->IsConnectedToInput() || (this->InputComponent == NewInputComponent),
		TEXT("Command bindings cannot be wired-up to two different input components at the same time.")
	);

	for (FPF2CommandInputBinding& Binding : this->Bindings)
	{
		Binding.ConnectToInput(NewInputComponent);
	}

	this->InputComponent = NewInputComponent;
}

void UPF2CommandBindingsComponent::DisconnectFromInput()
{
	if (this->IsConnectedToInput())
	{
		for (FPF2CommandInputBinding& Binding : this->Bindings)
		{
			Binding.DisconnectFromInput(this->InputComponent);
		}

		this->InputComponent = nullptr;
	}
}

bool UPF2CommandBindingsComponent::Server_ExecuteBoundAbility_Validate(
	const FGameplayAbilitySpecHandle AbilitySpecHandle,
	AActor*                          CharacterActor)
{
	TScriptInterface<IPF2CharacterInterface> Character;
	APawn*                                   CharacterPawn;

	if (!CharacterActor->Implements<UPF2CharacterInterface>())
	{
		UE_LOG(
			LogPf2CoreAbilities,
			Error,
			TEXT("Server_ExecuteBoundAbility(%s,%s): Character must implement PF2CharacterInterface."),
			*(AbilitySpecHandle.ToString()),
			*(CharacterActor->GetName())
		);

		return false;
	}

	Character = TScriptInterface<IPF2CharacterInterface>(CharacterActor);

	if (Character == nullptr)
	{
		UE_LOG(
			LogPf2CoreAbilities,
			Error,
			TEXT("Character is null, so ability ('%s') cannot be executed."),
			*(AbilitySpecHandle.ToString())
		);

		return false;
	}

	CharacterPawn = Character->ToPawn();

	if (CharacterPawn == nullptr)
	{
		UE_LOG(
			LogPf2CoreAbilities,
			Error,
			TEXT("Character ('%s') is not a pawn, so ability ('%s') cannot be executed."),
			*(Character->GetIdForLogs()),
			*(AbilitySpecHandle.ToString())
		);

		return false;
	}

	if (Cast<IPF2CharacterControllerInterface>(CharacterPawn->GetController()) == nullptr)
	{
		UE_LOG(
			LogPf2CoreAbilities,
			Error,
			TEXT("Character ('%s') is not currently possessed by an OpenPF2-compatible controller, so ability ('%s') cannot be executed."),
			*(Character->GetIdForLogs()),
			*(AbilitySpecHandle.ToString())
		);

		return false;
	}

	return true;
}

void UPF2CommandBindingsComponent::Server_ExecuteBoundAbility_Implementation(
	const FGameplayAbilitySpecHandle AbilitySpecHandle,
	AActor*                          CharacterActor)
{
	const TScriptInterface<IPF2CharacterInterface> Character = TScriptInterface<IPF2CharacterInterface>(CharacterActor);
	APawn*                                         CharacterPawn;
	IPF2CharacterControllerInterface*              CharacterController;

	check(Character != nullptr);

	CharacterPawn = Character->ToPawn();
	check(CharacterPawn != nullptr);

	CharacterController = Cast<IPF2CharacterControllerInterface>(CharacterPawn->GetController());
	check(CharacterController != nullptr)

	// Delegate to whichever player controller or AI controller is controlling this character.
	CharacterController->PerformAbilityOnControllableCharacter(AbilitySpecHandle, Character->ToActor());
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

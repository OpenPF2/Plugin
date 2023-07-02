// OpenPF2 for UE Game Logic, Copyright 2022-2023, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "Commands/PF2AbilityInputBinding.h"

#include <EnhancedInputComponent.h>

#include "OpenPF2Core.h"

#include "Commands/PF2AbilityBindingsInterface.h"
#include "Commands/PF2CharacterCommand.h"

#include "Utilities/PF2LogUtilities.h"

void UPF2AbilityInputBinding::Initialize(UInputAction*                 NewAction,
                                         const FGameplayAbilitySpec&   NewAbilitySpec,
                                         IPF2AbilityBindingsInterface* NewOwner)
{
	this->Action            = NewAction;
	this->AbilitySpecHandle = NewAbilitySpec.Handle;
	this->BindingsOwner     = NewOwner->ToActorComponent();

	UE_LOG(
		LogPf2CoreInput,
		VeryVerbose,
		TEXT("Creating an UPF2AbilityInputBinding for '%s' action (handle '%s') in command bindings component ('%s')."),
		*(this->GetActionName()),
		*(this->AbilitySpecHandle.ToString()),
		*(NewOwner->GetIdForLogs())
	);
}

void UPF2AbilityInputBinding::ConnectToInput(UEnhancedInputComponent* InputComponent)
{
	if (!this->IsConnectedToInput() && this->HasAction())
	{
		const UInputAction*               TargetAction = this->GetAction();
		FEnhancedInputActionEventBinding *PressedBinding,
		                                 *ReleasedBinding;
		TArray<int32>                     NewHandles;

		UE_LOG(
			LogPf2CoreInput,
			VeryVerbose,
			TEXT("[%s] Connecting binding for action ('%s') to input in component ('%s')."),
			*(PF2LogUtilities::GetHostNetId(Cast<UActorComponent>(this->GetBindingsOwner())->GetWorld())),
			*(this->GetActionName()),
			*(this->GetBindingsOwner()->GetIdForLogs())
		);

		// Pressed event.
		PressedBinding = &InputComponent->BindAction(
			TargetAction,
			ETriggerEvent::Started,
			this,
			&UPF2AbilityInputBinding::LocalInputPressed
		);

		NewHandles.Add(PressedBinding->GetHandle());

		// Released event.
		ReleasedBinding = &InputComponent->BindAction(
			TargetAction,
			ETriggerEvent::Completed,
			this,
			&UPF2AbilityInputBinding::LocalInputReleased
		);

		NewHandles.Add(ReleasedBinding->GetHandle());

		this->InputHandles = NewHandles;
	}
}

void UPF2AbilityInputBinding::DisconnectFromInput(UEnhancedInputComponent* InputComponent)
{
	if (this->IsConnectedToInput())
	{
		UE_LOG(
			LogPf2CoreInput,
			VeryVerbose,
			TEXT("[%s] Disconnecting binding for action ('%s') from input in component ('%s')."),
			*(PF2LogUtilities::GetHostNetId(Cast<UActorComponent>(this->GetBindingsOwner())->GetWorld())),
			*(this->GetActionName()),
			*(this->GetBindingsOwner()->GetIdForLogs())
		);

		for (const auto& Handle : this->InputHandles)
		{
			InputComponent->RemoveBindingByHandle(Handle);
		}

		this->InputHandles.Empty();
	}
}

FORCEINLINE IPF2AbilityBindingsInterface* UPF2AbilityInputBinding::GetBindingsOwner() const
{
	return Cast<IPF2AbilityBindingsInterface>(this->BindingsOwner);
}

void UPF2AbilityInputBinding::LocalInputPressed()
{
	IPF2AbilityBindingsInterface* Owner = this->GetBindingsOwner();

	UE_LOG(
		LogPf2CoreInput,
		VeryVerbose,
		TEXT("[%s] Input PRESSED for binding of action ('%s') in component ('%s')."),
		*(PF2LogUtilities::GetHostNetId(Cast<UActorComponent>(Owner)->GetWorld())),
		*(this->GetActionName()),
		*(Owner->GetIdForLogs())
	);

	this->ActivateAbility();
}

void UPF2AbilityInputBinding::LocalInputReleased()
{
	IPF2AbilityBindingsInterface* Owner = this->GetBindingsOwner();

	UE_LOG(
		LogPf2CoreInput,
		VeryVerbose,
		TEXT("[%s] Input RELEASED for binding of action ('%s') in component ('%s')."),
		*(PF2LogUtilities::GetHostNetId(Cast<UActorComponent>(Owner)->GetWorld())),
		*(this->GetActionName()),
		*(Owner->GetIdForLogs())
	);

	this->DeactivateAbility();
}

void UPF2AbilityInputBinding::ActivateAbility()
{
	this->GetBindingsOwner()->ExecuteBoundAbility(this->GetAction(), this->AbilitySpecHandle);
}

void UPF2AbilityInputBinding::DeactivateAbility()
{
	// Default implementation -- Do nothing.
}

// OpenPF2 for UE Game Logic, Copyright 2022, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "Commands/PF2CommandInputBinding.h"

#include "OpenPF2Core.h"

#include "Commands/PF2CharacterCommand.h"
#include "Commands/PF2CommandBindingsInterface.h"

#include "Utilities/PF2LogUtilities.h"

void FPF2CommandInputBinding::ConnectToInput(UInputComponent* InputComponent)
{
	if (!this->IsConnectedToInput() && !this->ActionName.IsNone())
	{
		TArray<int32> NewHandles;

		UE_LOG(
			LogPf2CoreInput,
			VeryVerbose,
			TEXT("[%s] Connecting binding for action ('%s') to input in component ('%s')."),
			*(PF2LogUtilities::GetHostNetId(Cast<UActorComponent>(this->GetBindingsOwner())->GetWorld())),
			*(this->ActionName.ToString()),
			*(this->GetBindingsOwner()->GetIdForLogs())
		);

		// Pressed event
		NewHandles.Add(
			this->AddActionBinding(
				InputComponent,
				IE_Pressed,
				&FPF2CommandInputBinding::LocalInputPressed
			)
		);

		// Released event
		NewHandles.Add(
			this->AddActionBinding(
				InputComponent,
				IE_Released,
				&FPF2CommandInputBinding::LocalInputReleased
			)
		);

		this->InputHandles = NewHandles;
	}
}

void FPF2CommandInputBinding::DisconnectFromInput(UInputComponent* InputComponent)
{
	if (this->IsConnectedToInput())
	{
		UE_LOG(
			LogPf2CoreInput,
			VeryVerbose,
			TEXT("[%s] Disconnecting binding for action ('%s') from input in component ('%s')."),
			*(PF2LogUtilities::GetHostNetId(Cast<UActorComponent>(this->GetBindingsOwner())->GetWorld())),
			*(this->ActionName.ToString()),
			*(this->GetBindingsOwner()->GetIdForLogs())
		);

		for (const auto& Handle : this->InputHandles)
		{
			InputComponent->RemoveActionBindingForHandle(Handle);
		}

		this->InputHandles.Empty();
	}
}

void FPF2CommandInputBinding::LocalInputPressed(FPF2CommandInputBinding* Binding)
{
	if (Binding == nullptr)
	{
		UE_LOG(
			LogPf2CoreInput,
			VeryVerbose,
			TEXT("[UNK] Input PRESSED for a null binding.")
		);
	}
	else
	{
		UE_LOG(
			LogPf2CoreInput,
			VeryVerbose,
			TEXT("[%s] Input PRESSED for binding of action ('%s') in component ('%s')."),
			*(PF2LogUtilities::GetHostNetId(Cast<UActorComponent>(Binding->GetBindingsOwner())->GetWorld())),
			*(Binding->ActionName.ToString()),
			*(Binding->GetBindingsOwner()->GetIdForLogs())
		);

		Binding->ActivateAbility();
	}
}

void FPF2CommandInputBinding::LocalInputReleased(FPF2CommandInputBinding* Binding)
{
	if (Binding == nullptr)
	{
		UE_LOG(
			LogPf2CoreInput,
			VeryVerbose,
			TEXT("[UNK] Input RELEASED for a null binding."),
		);
	}
	else
	{
		UE_LOG(
			LogPf2CoreInput,
			VeryVerbose,
			TEXT("[%s] Input RELEASED for binding of action ('%s') in component ('%s')."),
			*(PF2LogUtilities::GetHostNetId(Cast<UActorComponent>(Binding->GetBindingsOwner())->GetWorld())),
			*(Binding->ActionName.ToString()),
			*(Binding->GetBindingsOwner()->GetIdForLogs())
		);

		Binding->DeactivateAbility();
	}
}

int32 FPF2CommandInputBinding::AddActionBinding(UInputComponent*  InputComponent,
                                                const EInputEvent InKeyEvent,
                                                void              (*Callback)(FPF2CommandInputBinding*))
{
	FInputActionBinding  ActionBinding = FInputActionBinding(this->ActionName, InKeyEvent);
	FInputActionBinding* AddResult;

	ActionBinding.ActionDelegate.GetDelegateForManualSet().BindStatic(
		Callback,
		this
	);

	AddResult = &InputComponent->AddActionBinding(ActionBinding);

	AddResult->bConsumeInput = this->IsConsumingInput();

	return AddResult->GetHandle();
}

void FPF2CommandInputBinding::ActivateAbility()
{
	this->GetBindingsOwner()->ExecuteBoundAbility(this->ActionName, this->AbilitySpecHandle);
}

void FPF2CommandInputBinding::DeactivateAbility()
{
	// Default implementation -- Do nothing.
}

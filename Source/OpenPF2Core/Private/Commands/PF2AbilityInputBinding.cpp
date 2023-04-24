// OpenPF2 for UE Game Logic, Copyright 2022-2023, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "Commands/PF2AbilityInputBinding.h"

#include "OpenPF2Core.h"

#include "Commands/PF2AbilityBindingsInterface.h"
#include "Commands/PF2CharacterCommand.h"

#include "Utilities/PF2LogUtilities.h"

FPF2AbilityInputBinding::FPF2AbilityInputBinding(const FName&                  ActionName,
                                                 const FGameplayAbilitySpec&   AbilitySpec,
                                                 IPF2AbilityBindingsInterface* Owner,
                                                 const bool                    bConsumeInput):
	ActionName(ActionName),
	AbilitySpecHandle(AbilitySpec.Handle),
	BindingsOwner(Owner->ToActorComponent()),
	bConsumeInput(bConsumeInput)
{
	UE_LOG(
		LogPf2CoreInput,
		VeryVerbose,
		TEXT("Creating an FPF2AbilityInputBinding for '%s' action (handle '%s') in command bindings component ('%s')."),
		*(ActionName.ToString()),
		*(this->AbilitySpecHandle.ToString()),
		*(Owner->GetIdForLogs())
	);
}

void FPF2AbilityInputBinding::ConnectToInput(UInputComponent* InputComponent)
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
				&FPF2AbilityInputBinding::LocalInputPressed
			)
		);

		// Released event
		NewHandles.Add(
			this->AddActionBinding(
				InputComponent,
				IE_Released,
				&FPF2AbilityInputBinding::LocalInputReleased
			)
		);

		this->InputHandles = NewHandles;
	}
}

void FPF2AbilityInputBinding::DisconnectFromInput(UInputComponent* InputComponent)
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

void FPF2AbilityInputBinding::LocalInputPressed(FPF2AbilityInputBinding* Binding)
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

void FPF2AbilityInputBinding::LocalInputReleased(FPF2AbilityInputBinding* Binding)
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

FORCEINLINE IPF2AbilityBindingsInterface* FPF2AbilityInputBinding::GetBindingsOwner() const
{
	return Cast<IPF2AbilityBindingsInterface>(this->BindingsOwner);
}

int32 FPF2AbilityInputBinding::AddActionBinding(UInputComponent*  InputComponent,
                                                const EInputEvent InKeyEvent,
                                                void              (*Callback)(FPF2AbilityInputBinding*))
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

void FPF2AbilityInputBinding::ActivateAbility()
{
	this->GetBindingsOwner()->ExecuteBoundAbility(this->ActionName, this->AbilitySpecHandle);
}

void FPF2AbilityInputBinding::DeactivateAbility()
{
	// Default implementation -- Do nothing.
}

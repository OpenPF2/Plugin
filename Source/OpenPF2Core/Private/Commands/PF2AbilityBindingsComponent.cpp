// OpenPF2 for UE Game Logic, Copyright 2022-2023, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "Commands/PF2AbilityBindingsComponent.h"

#include <AbilitySystemComponent.h>

#include <Components/InputComponent.h>

#include "PF2CharacterInterface.h"
#include "PF2PlayerControllerInterface.h"

#include "Abilities/PF2GameplayAbilityInterface.h"

#include "Commands/PF2AbilityExecutionFilterContext.h"
#include "Commands/PF2AbilityExecutionFilterInterface.h"
#include "Commands/PF2AbilityInputBinding.h"
#include "Commands/PF2CharacterCommand.h"

#include "Utilities/PF2InterfaceUtilities.h"
#include "Utilities/PF2LogUtilities.h"
#include "Utilities/PF2MapUtilities.h"

UPF2AbilityBindingsInterfaceEvents* UPF2AbilityBindingsComponent::GetEvents() const
{
	check(this->Events != nullptr);
	return this->Events;
}

bool UPF2AbilityBindingsComponent::IsConsumingInput() const
{
	return this->bConsumeInput;
}

void UPF2AbilityBindingsComponent::SetConsumeInput(const bool bNewValue)
{
	if (this->bConsumeInput != bNewValue)
	{
		const int32 BindingsCount = this->Bindings.Num();

		if (BindingsCount == 0)
		{
			this->bConsumeInput = bNewValue;
		}
		else
		{
			UE_LOG(
				LogPf2CoreInput,
				Error,
				TEXT("Command bindings component ('%s') already has '%d' bindings. The 'consume input' setting can only be changed before bindings have been added."),
				*(this->GetIdForLogs()),
				BindingsCount
			);
		}
	}
}

void UPF2AbilityBindingsComponent::DisconnectBindingFromInput(FPF2AbilityInputBinding& Binding) const
{
	return Binding.DisconnectFromInput(this->GetInputComponent());
}

void UPF2AbilityBindingsComponent::Native_OnBindingsChanged()
{
	this->GetEvents()->OnAbilityBindingsChangedDelegate.Broadcast(this);
}

void UPF2AbilityBindingsComponent::ClearBindings()
{
	if (this->IsConnectedToInput())
	{
		for (auto PairIterator = this->Bindings.CreateIterator(); PairIterator; ++PairIterator)
		{
			FPF2AbilityInputBinding& Binding = PairIterator.Value();

			this->DisconnectBindingFromInput(Binding);
		}
	}

	this->Bindings.Empty();
	this->Native_OnBindingsChanged();
}

void UPF2AbilityBindingsComponent::ClearBinding(const FName& ActionName)
{
	if (this->Bindings.Contains(ActionName))
	{
		this->DisconnectBindingFromInput(this->Bindings[ActionName]);
		this->Bindings.Remove(ActionName);
		this->Native_OnBindingsChanged();
	}
}

void UPF2AbilityBindingsComponent::LoadAbilitiesFromCharacter()
{
	const IPF2CharacterInterface* Character              = this->GetOwningCharacter();
	UAbilitySystemComponent*      AbilitySystemComponent = Character->GetAbilitySystemComponent();
	TArray<FGameplayAbilitySpec>  ActivatableAbilities   = AbilitySystemComponent->GetActivatableAbilities();
	int32                         NumMappedAbilities     = 0;

	checkf(
		this->Bindings.Num() == 0,
		TEXT("Abilities must be loaded from a character before custom bindings are added.")
	);

	UE_LOG(
		LogPf2CoreInput,
		VeryVerbose,
		TEXT("[%s] Loading %d abilities from TargetCharacter ('%s')."),
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
			// Fallback for interoperability with non-OpenPF2 abilities.
			DefaultAction = FName();
		}

		this->SetBindingWithoutBroadcast(DefaultAction, AbilitySpec);
	}

	UE_LOG(
		LogPf2CoreInput,
		VeryVerbose,
		TEXT("[%s] Loaded %d abilities with default action mappings from TargetCharacter ('%s')."),
		*(PF2LogUtilities::GetHostNetId(this->GetWorld())),
		NumMappedAbilities,
		*(Character->GetIdForLogs())
	);

	if (this->IsConnectedToInput())
	{
		// Wire up all the new bindings.
		this->ConnectToInput(this->GetInputComponent());
	}

	this->Native_OnBindingsChanged();
}

void UPF2AbilityBindingsComponent::SetBinding(const FName& ActionName, const FGameplayAbilitySpec& AbilitySpec)
{
	this->SetBindingWithoutBroadcast(ActionName, AbilitySpec);
	this->Native_OnBindingsChanged();
}

void UPF2AbilityBindingsComponent::SetBindingWithoutBroadcast(const FName& ActionName,
	const FGameplayAbilitySpec& AbilitySpec)
{
	if (this->Bindings.Contains(ActionName))
	{
		// Disconnect the old binding before replacing it.
		this->DisconnectBindingFromInput(this->Bindings[ActionName]);
	}

	this->Bindings.Add(ActionName, FPF2AbilityInputBinding(ActionName, AbilitySpec, this, this->IsConsumingInput()));
}

TMap<FName, TScriptInterface<IPF2GameplayAbilityInterface>> UPF2AbilityBindingsComponent::GetBindingsMap() const
{
	UAbilitySystemComponent* Asc = this->GetOwningCharacter()->GetAbilitySystemComponent();

	return PF2ArrayUtilities::Reduce(
		PF2MapUtilities::GetValues(this->Bindings),
		TMap<FName, TScriptInterface<IPF2GameplayAbilityInterface>>(),
		[Asc](TMap<FName, TScriptInterface<IPF2GameplayAbilityInterface>> ResultMap,
		      const FPF2AbilityInputBinding&                              CurrentBinding)
		{
			const FGameplayAbilitySpec* AbilitySpec = Asc->FindAbilitySpecFromHandle(CurrentBinding.AbilitySpecHandle);

			if (AbilitySpec != nullptr)
			{
				IPF2GameplayAbilityInterface* Ability = Cast<IPF2GameplayAbilityInterface>(AbilitySpec->Ability);

				if (Ability != nullptr)
				{
					ResultMap.Add(
						CurrentBinding.ActionName,
						PF2InterfaceUtilities::ToScriptInterface<IPF2GameplayAbilityInterface>(Ability)
					);
				}
			}

			return ResultMap;
		}
	);
}

void UPF2AbilityBindingsComponent::ConnectToInput(UInputComponent* NewInputComponent)
{
	checkf(
		!this->IsConnectedToInput() || (this->InputComponent == NewInputComponent),
		TEXT("Command bindings cannot be wired-up to two different input components at the same time.")
	);

	for (auto PairIterator = this->Bindings.CreateIterator(); PairIterator; ++PairIterator)
	{
		FPF2AbilityInputBinding& Binding = PairIterator.Value();

		Binding.ConnectToInput(NewInputComponent);
	}

	this->InputComponent = NewInputComponent;

	this->Native_OnInputConnected();
}

void UPF2AbilityBindingsComponent::DisconnectFromInput()
{
	if (this->IsConnectedToInput())
	{
		for (auto PairIterator = this->Bindings.CreateIterator(); PairIterator; ++PairIterator)
		{
			FPF2AbilityInputBinding& Binding = PairIterator.Value();

			Binding.DisconnectFromInput(this->InputComponent);
		}

		this->InputComponent = nullptr;

		this->Native_OnInputDisconnected();
	}
}

bool UPF2AbilityBindingsComponent::FilterAbilityActivation(
	const FName                                    InActionName,
	const TScriptInterface<IPF2CharacterInterface> InCharacter,
	FGameplayAbilitySpecHandle&                    InOutAbilitySpecHandle,
	FGameplayEventData&                            InOutAbilityPayload)
{
	FPF2AbilityExecutionFilterContext FilterContext =
		FPF2AbilityExecutionFilterContext(InActionName, InCharacter, InOutAbilitySpecHandle, InOutAbilityPayload);

	for (const TSubclassOf<UObject> FilterType : this->Filters)
	{
		TSubclassOf<UObject>::TBaseType*           RawFilter = FilterType.GetDefaultObject();
		const IPF2AbilityExecutionFilterInterface* Filter    = Cast<IPF2AbilityExecutionFilterInterface>(RawFilter);

		if (Filter == nullptr)
		{
			UE_LOG(
				LogPf2CoreInput,
				Error,
				TEXT("Command bindings component ('%s') has a null ability execution filter."),
				*(this->GetIdForLogs())
			);
		}
		else
		{
			UE_LOG(
				LogPf2CoreInput,
				VeryVerbose,
				TEXT("[%s] [%s] BEFORE applying filter ('%s') - Ability handle: %s."),
				*(PF2LogUtilities::GetHostNetId(this->GetWorld())),
				*(this->GetIdForLogs()),
				*(Filter->GetIdForLogs()),
				*(FilterContext.GetHandleOfAbilityToExecute().ToString())
			);

			FilterContext = Filter->Execute_FilterCommandActivation(RawFilter, FilterContext);

			UE_LOG(
				LogPf2CoreInput,
				VeryVerbose,
				TEXT("[%s] [%s] AFTER applying filter ('%s') - Proceed: %s, Ability handle: %s."),
				*(PF2LogUtilities::GetHostNetId(this->GetWorld())),
				*(this->GetIdForLogs()),
				*(Filter->GetIdForLogs()),
				(FilterContext.ShouldProceed() ? TEXT("true") : TEXT("false")),
				*(FilterContext.GetHandleOfAbilityToExecute().ToString())
			);

			if (!FilterContext.ShouldProceed())
			{
				// The last filter vetoed execution, so let's call the whole thing off.
				return false;
			}
		}
	}

	InOutAbilitySpecHandle = FilterContext.GetHandleOfAbilityToExecute();
	InOutAbilityPayload    = FilterContext.GetAbilityPayload();

	return true;
}

void UPF2AbilityBindingsComponent::ExecuteBoundAbility(const FName                      ActionName,
                                                       const FGameplayAbilitySpecHandle AbilitySpecHandle)
{
	IPF2CharacterInterface*                         CharacterIntf         = this->GetOwningCharacter();
	TScriptInterface<IPF2CharacterInterface>        Character;
	TScriptInterface<IPF2PlayerControllerInterface> PlayerController;
	FGameplayAbilitySpecHandle                      FilteredAbilityHandle = AbilitySpecHandle;
	FGameplayEventData                              FilteredAbilityPayload;

	check(CharacterIntf != nullptr);

	Character        = PF2InterfaceUtilities::ToScriptInterface(CharacterIntf);
	PlayerController = CharacterIntf->GetPlayerController();

	check(PlayerController.GetInterface() != nullptr);

	if (this->FilterAbilityActivation(ActionName, Character, FilteredAbilityHandle, FilteredAbilityPayload))
	{
		PlayerController->Server_ExecuteAbilitySpecAsCharacterCommandWithPayload(
			FilteredAbilityHandle,
			CharacterIntf->ToActor(),
			FilteredAbilityPayload
		);
	}
}

UActorComponent* UPF2AbilityBindingsComponent::ToActorComponent()
{
	return this;
}

FString UPF2AbilityBindingsComponent::GetIdForLogs() const
{
	// ReSharper disable CppRedundantParentheses
	return FString::Format(
		TEXT("{0}.{1}"),
		{
			*(GetNameSafe(this->GetOwner())),
			*(this->GetName())
		}
	);
}

IPF2CharacterInterface* UPF2AbilityBindingsComponent::GetOwningCharacter() const
{
	AActor*                 OwningActor;
	IPF2CharacterInterface* OwningCharacter;

	OwningActor = this->GetOwner();
	check(OwningActor != nullptr);

	OwningCharacter = Cast<IPF2CharacterInterface>(OwningActor);
	checkf(OwningCharacter != nullptr, TEXT("Owning character must implement IPF2CharacterInterface."));

	return OwningCharacter;
}

void UPF2AbilityBindingsComponent::Native_OnInputConnected()
{
	UE_LOG(
		LogPf2CoreInput,
		Verbose,
		TEXT("[%s] Command bindings component ('%s') connected to input."),
		*(PF2LogUtilities::GetHostNetId(this->GetWorld())),
		*(this->GetIdForLogs())
	);

	this->OnInputConnected.Broadcast();
}

void UPF2AbilityBindingsComponent::Native_OnInputDisconnected()
{
	UE_LOG(
		LogPf2CoreInput,
		Verbose,
		TEXT("[%s] Command bindings component ('%s') disconnected from input."),
		*(PF2LogUtilities::GetHostNetId(this->GetWorld())),
		*(this->GetIdForLogs())
	);

	this->OnInputDisconnected.Broadcast();
}

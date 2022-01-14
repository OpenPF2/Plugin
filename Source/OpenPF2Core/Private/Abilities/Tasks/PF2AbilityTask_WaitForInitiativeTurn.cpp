// OpenPF2 for UE Game Logic, Copyright 2021, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "Abilities/Tasks/PF2AbilityTask_WaitForInitiativeTurn.h"

#include "OpenPF2Core.h"
#include "PF2CharacterInterface.h"
#include "GameModes/PF2GameModeInterface.h"
#include "Utilities/PF2InterfaceUtilities.h"
#include "Utilities/PF2LogUtilities.h"

UPF2AbilityTask_WaitForInitiativeTurn* UPF2AbilityTask_WaitForInitiativeTurn::CreateWaitMovementModeChange(
	UGameplayAbility* OwningAbility,
	const FName       TaskInstanceName,
	const FText       ActionName,
	const FSlateBrush ActionIcon)
{
	UPF2AbilityTask_WaitForInitiativeTurn* Task =
		NewAbilityTask<UPF2AbilityTask_WaitForInitiativeTurn>(OwningAbility, TaskInstanceName);

	Task->ActionName = ActionName;
	Task->ActionIcon = ActionIcon;

	return Task;
}

void UPF2AbilityTask_WaitForInitiativeTurn::Activate()
{
	IPF2CharacterInterface* PF2Character = Cast<IPF2CharacterInterface>(this->GetOwnerActor());

	if ((PF2Character != nullptr) && this->HasAbility())
	{
		this->WaitingCharacter = PF2Character;

		if (this->IsPredictingClient())
		{
			this->Activate_Client();
		}
		else
		{
			this->Activate_Server(PF2Character);
		}
	}
}

void UPF2AbilityTask_WaitForInitiativeTurn::ExternalCancel()
{
	if (!this->WasActivated())
	{
		if (this->ShouldBroadcastAbilityTaskDelegates())
		{
			this->OnCancelled.Broadcast();
		}

		Super::ExternalCancel();
	}
}

void UPF2AbilityTask_WaitForInitiativeTurn::OnDestroy(bool AbilityEnded)
{
	if ((this->WaitingCharacter != nullptr) && (this->GameMode != nullptr) && !this->WasActivated())
	{
		TScriptInterface<IPF2CharacterInterface> CharacterScriptInterface = this->WaitingCharacter.ToScriptInterface();

		TScriptInterface<IPF2QueuedActionInterface> ThisScriptInterface =
			PF2InterfaceUtilities::ToScriptInterface<IPF2QueuedActionInterface>(this);

		this->GameMode->CancelActionQueuedForInitiativeTurn(CharacterScriptInterface, ThisScriptInterface);
	}
}

FText UPF2AbilityTask_WaitForInitiativeTurn::GetActionName()
{
	return this->ActionName;
}

FSlateBrush UPF2AbilityTask_WaitForInitiativeTurn::GetActionIcon()
{
	return this->ActionIcon;
}

EPF2AbilityActivationOutcomeType UPF2AbilityTask_WaitForInitiativeTurn::PerformAction()
{
	if (this->HasAbility() && !this->IsPendingKill() && !this->WasActivated())
	{
		UE_LOG(
			LogPf2CoreEncounters,
			VeryVerbose,
			TEXT("[%s] Performing action ('%s') for character ('%s')."),
			*(PF2LogUtilities::GetHostNetId(this->GetWorld())),
			*(this->GetActionName().ToString()),
			*((this->WaitingCharacter != nullptr) ? this->WaitingCharacter->GetCharacterName().ToString() : TEXT("UNK"))
		);

		if (this->ShouldBroadcastAbilityTaskDelegates())
		{
			this->OnReadyToAct.Broadcast();
		}

		if (this->IsForRemoteClient() && this->HasAsc())
		{
			// Allow the client to proceed with its predicted copy of the ability.
			this->AbilitySystemComponent->ClientSetReplicatedEvent(
				EAbilityGenericReplicatedEvent::GenericSignalFromServer,
				this->GetAbilitySpecHandle(),
				this->GetActivationPredictionKey()
			);
		}

		this->ActivationOutcome = EPF2AbilityActivationOutcomeType::Activated;

		this->EndTask();
	}

	return this->ActivationOutcome;
}

void UPF2AbilityTask_WaitForInitiativeTurn::CancelAction()
{
	this->ExternalCancel();
}

void UPF2AbilityTask_WaitForInitiativeTurn::Activate_Client()
{
	if (this->HasAsc())
	{
		FScopedPredictionWindow ScopedPrediction(this->AbilitySystemComponent, true);

		this->CallOrAddReplicatedDelegate(
			EAbilityGenericReplicatedEvent::GenericSignalFromServer,
			FSimpleMulticastDelegate::FDelegate::CreateUObject(
				this,
				&UPF2AbilityTask_WaitForInitiativeTurn::OnServerActionCallback
			)
		);
	}
}

void UPF2AbilityTask_WaitForInitiativeTurn::Activate_Server(IPF2CharacterInterface* PF2Character)
{
	const UWorld* const World = this->GetWorld();

	if (World != nullptr)
	{
		IPF2GameModeInterface* PF2GameMode = Cast<IPF2GameModeInterface>(World->GetAuthGameMode());

		if (PF2GameMode != nullptr)
		{
			TScriptInterface<IPF2CharacterInterface> CharacterScriptInterface =
				PF2InterfaceUtilities::ToScriptInterface<IPF2CharacterInterface>(PF2Character);

			TScriptInterface<IPF2QueuedActionInterface> ThisScriptInterface =
				PF2InterfaceUtilities::ToScriptInterface<IPF2QueuedActionInterface>(this);

			this->GameMode = PF2GameMode;

			PF2GameMode->QueueActionForInitiativeTurn(CharacterScriptInterface, ThisScriptInterface);

			this->SetWaitingOnRemotePlayerData();
		}
	}
}

void UPF2AbilityTask_WaitForInitiativeTurn::OnServerActionCallback()
{
	if (this->HasAsc())
	{
		this->AbilitySystemComponent->ConsumeGenericReplicatedEvent(
			EAbilityGenericReplicatedEvent::GenericSignalFromServer,
			this->GetAbilitySpecHandle(),
			this->GetActivationPredictionKey()
		);
	}

	this->PerformAction();
}

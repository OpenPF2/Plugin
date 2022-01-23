// OpenPF2 for UE Game Logic, Copyright 2021, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "Abilities/Tasks/PF2AbilityTask_WaitForInitiativeTurn.h"

#include "OpenPF2Core.h"
#include "PF2CharacterInterface.h"

#include "Abilities/PF2ActionQueueResult.h"

#include "GameModes/PF2GameModeInterface.h"

#include "Utilities/PF2InterfaceUtilities.h"
#include "Utilities/PF2LogUtilities.h"

UPF2AbilityTask_WaitForInitiativeTurn* UPF2AbilityTask_WaitForInitiativeTurn::CreateWaitInitiativeTurn(
	UGameplayAbility*            OwningAbility,
	const FName                  TaskInstanceName,
	const FText                  ActionName,
	const FSlateBrush            ActionIcon)
{
	UPF2AbilityTask_WaitForInitiativeTurn* Task =
		NewAbilityTask<UPF2AbilityTask_WaitForInitiativeTurn>(OwningAbility, TaskInstanceName);

	Task->ActionName = ActionName;
	Task->ActionIcon = ActionIcon;

	return Task;
}

UPF2AbilityTask_WaitForInitiativeTurn* UPF2AbilityTask_WaitForInitiativeTurn::CreateWaitInitiativeTurnWithTags(
	UGameplayAbility*            OwningAbility,
	const FName                  TaskInstanceName,
	const FText                  ActionName,
	const FSlateBrush            ActionIcon,
	const FGameplayTagContainer& SourceTags,
	const FGameplayTagContainer& TargetTags)
{
	UPF2AbilityTask_WaitForInitiativeTurn* Task =
		NewAbilityTask<UPF2AbilityTask_WaitForInitiativeTurn>(OwningAbility, TaskInstanceName);

	Task->ActionName = ActionName;
	Task->ActionIcon = ActionIcon;
	Task->SourceTags = &SourceTags;
	Task->TargetTags = &TargetTags;

	return Task;
}

void UPF2AbilityTask_WaitForInitiativeTurn::Activate()
{
	IPF2CharacterInterface* PF2Character = Cast<IPF2CharacterInterface>(this->GetOwnerActor());

	checkf(
		this->Ability->GetInstancingPolicy() == EGameplayAbilityInstancingPolicy::InstancedPerExecution,
		TEXT("WaitForInitiativeTurn can only be used on abilites 'Instanced per Execution'.")
	)

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
	if (!this->WasActivatedOrCanceled())
	{
		if (this->ShouldBroadcastAbilityTaskDelegates())
		{
			this->OnCancelled.Broadcast();
		}

		Super::ExternalCancel();
	}
}

void UPF2AbilityTask_WaitForInitiativeTurn::OnDestroy(bool bAbilityEnded)
{
	if ((this->WaitingCharacter != nullptr) && (this->GameMode != nullptr) && !this->WasActivatedOrCanceled())
	{
		const TScriptInterface<IPF2CharacterInterface> CharacterScriptInterface =
			this->WaitingCharacter.ToScriptInterface();

		const TScriptInterface<IPF2QueuedActionInterface> ThisScriptInterface =
			PF2InterfaceUtilities::ToScriptInterface<IPF2QueuedActionInterface>(this);

		this->GameMode->CancelActionQueuedForInitiativeTurn(CharacterScriptInterface, ThisScriptInterface);
	}
}

FText UPF2AbilityTask_WaitForInitiativeTurn::GetActionName() const
{
	return this->ActionName;
}

FSlateBrush UPF2AbilityTask_WaitForInitiativeTurn::GetActionIcon() const
{
	return this->ActionIcon;
}

bool UPF2AbilityTask_WaitForInitiativeTurn::CanAbilityProceed() const
{
	const FGameplayAbilitySpecHandle AbilitySpecHandle = this->Ability->GetCurrentAbilitySpecHandle();
	const FGameplayAbilityActorInfo  ActorInfo         = this->Ability->GetActorInfo();

	// Prevent blocking ourselves.
	this->Ability->SetShouldBlockOtherAbilities(false);

	return this->Ability->CanActivateAbility(AbilitySpecHandle, &ActorInfo, this->SourceTags, this->TargetTags);
}

EPF2AbilityActivationResult UPF2AbilityTask_WaitForInitiativeTurn::PerformAction()
{
	EPF2AbilityActivationResult Result = this->ActivationOutcome;

	if (this->HasAbility() && !this->IsPendingKill() && !this->WasActivatedOrCanceled())
	{
		if (this->CanAbilityProceed())
		{
			UE_LOG(
				LogPf2CoreEncounters,
				VeryVerbose,
				TEXT("[%s] Performing action ('%s') for character ('%s')."),
				*(PF2LogUtilities::GetHostNetId(this->GetWorld())),
				*(this->GetActionName().ToString()),
				*((this->WaitingCharacter != nullptr) ?
					this->WaitingCharacter->GetCharacterName().ToString() :
					TEXT("UNK"))
			);

			this->Ability->SetShouldBlockOtherAbilities(true);

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

			Result = EPF2AbilityActivationResult::Activated;

			this->EndTask();
		}
		else
		{
			UE_LOG(
				LogPf2CoreEncounters,
				VeryVerbose,
				TEXT("[%s] Action ('%s') blocked for character ('%s')."),
				*(PF2LogUtilities::GetHostNetId(this->GetWorld())),
				*(this->GetActionName().ToString()),
				*((this->WaitingCharacter != nullptr) ?
					this->WaitingCharacter->GetCharacterName().ToString() :
					TEXT("UNK"))
			);

			Result = EPF2AbilityActivationResult::Blocked;
		}

		this->ActivationOutcome = Result;
	}

	return Result;
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

		this->Ability->SetShouldBlockOtherAbilities(false);

		this->CallOrAddReplicatedDelegate(
			EAbilityGenericReplicatedEvent::GenericSignalFromServer,
			FSimpleMulticastDelegate::FDelegate::CreateUObject(
				this,
				&UPF2AbilityTask_WaitForInitiativeTurn::OnPerformAction_Client
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

			EPF2ActionQueueResult QueueResult;

			this->GameMode = PF2GameMode;

			PF2GameMode->QueueActionForInitiativeTurn(CharacterScriptInterface, ThisScriptInterface, QueueResult);

			switch (QueueResult)
			{
			case EPF2ActionQueueResult::Refused:
				// The MoPRS refused to allow this action at all (rare).
				this->CancelAction();
				break;

			case EPF2ActionQueueResult::ExecutedImmediately:
				// The MoPRS already executed the action without any queueing, so we have nothing left to do.
				break;

			default:
			case EPF2ActionQueueResult::Queued:
				// The MoPRS queued the action for later execution. Notify the ability and temporarily unblock this
				// ability from blocking other abilities that would otherwise be incompatible.
				this->OnQueued.Broadcast();
				this->Ability->SetShouldBlockOtherAbilities(false);

				this->SetWaitingOnRemotePlayerData();
				break;
			}
		}
	}
}

void UPF2AbilityTask_WaitForInitiativeTurn::OnPerformAction_Client()
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

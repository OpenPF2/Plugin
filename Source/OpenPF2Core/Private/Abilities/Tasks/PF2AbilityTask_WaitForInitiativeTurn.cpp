// OpenPF2 for UE Game Logic, Copyright 2021, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "Abilities/Tasks/PF2AbilityTask_WaitForInitiativeTurn.h"

#include "OpenPF2Core.h"
#include "PF2CharacterInterface.h"
#include "PF2InterfaceUtilities.h"

#include "GameModes/PF2GameModeInterface.h"

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
	const UWorld* const     World        = this->GetWorld();
	IPF2CharacterInterface* PF2Character = Cast<IPF2CharacterInterface>(this->GetOwnerActor());

	if ((World != nullptr) && (PF2Character != nullptr) && this->HasAbility())
	{
		IPF2GameModeInterface* PF2GameMode = Cast<IPF2GameModeInterface>(World->GetAuthGameMode());

		if (PF2GameMode != nullptr)
		{
			TScriptInterface<IPF2CharacterInterface> CharacterScriptInterface =
				PF2InterfaceUtilities::ToScriptInterface<IPF2CharacterInterface>(PF2Character);

			TScriptInterface<IPF2QueuedActionInterface> ThisScriptInterface =
				PF2InterfaceUtilities::ToScriptInterface<IPF2QueuedActionInterface>(this);

			this->WaitingCharacter = PF2Character;
			this->GameMode         = PF2GameMode;

			PF2GameMode->QueueActionForInitiativeTurn(CharacterScriptInterface, ThisScriptInterface);

			this->SetWaitingOnRemotePlayerData();
		}
	}
}

void UPF2AbilityTask_WaitForInitiativeTurn::ExternalCancel()
{
	if (this->HasAbility())
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
	if ((this->WaitingCharacter != nullptr) && (this->GameMode != nullptr))
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

void UPF2AbilityTask_WaitForInitiativeTurn::PerformAction()
{
	if (this->HasAbility())
	{
		UE_LOG(
			LogPf2CoreAbilities,
			VeryVerbose,
			TEXT("Performing action ('%s') for character ('%s')."),
			*(this->GetActionName().ToString()),
			*(this->WaitingCharacter->GetCharacterName().ToString())
		);

		if (this->ShouldBroadcastAbilityTaskDelegates())
		{
			this->OnReadyToAct.Broadcast();
		}

		this->EndTask();
	}
}

void UPF2AbilityTask_WaitForInitiativeTurn::CancelAction()
{
	this->ExternalCancel();
}

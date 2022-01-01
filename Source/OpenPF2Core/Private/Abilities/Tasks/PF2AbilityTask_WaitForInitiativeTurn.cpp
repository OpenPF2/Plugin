// OpenPF2 for UE Game Logic, Copyright 2021, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "Abilities/Tasks/PF2AbilityTask_WaitForInitiativeTurn.h"

#include "PF2CharacterInterface.h"

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
		IPF2GameStateInterface* PF2GameState = Cast<IPF2GameStateInterface>(World->GetGameState());

		if (PF2GameState != nullptr)
		{
			this->WaitingCharacter = PF2Character;
			this->GameState        = PF2GameState;

			PF2GameState->QueueActionForInitiativeTurn(PF2Character, this);
			this->SetWaitingOnRemotePlayerData();
		}
	}
}

void UPF2AbilityTask_WaitForInitiativeTurn::OnDestroy(bool AbilityEnded)
{
	if ((this->WaitingCharacter != nullptr) && (this->GameState != nullptr))
	{
		this->GameState->CancelActionQueuedForInitiativeTurn(this->WaitingCharacter.Get(), this);
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

void UPF2AbilityTask_WaitForInitiativeTurn::PerformQueuedAction()
{
	if (this->HasAbility())
	{
		if (this->ShouldBroadcastAbilityTaskDelegates())
		{
			this->OnReadyToAct.Broadcast();
		}

		this->EndTask();
	}
}

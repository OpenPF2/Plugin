// OpenPF2 for UE Game Logic, Copyright 2022-2023, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "Abilities/Tasks/PF2AbilityTask_AcquireTargetFromPlayerController.h"

#include <AbilitySystemComponent.h>

#include "PF2CharacterInterface.h"
#include "PF2PlayerControllerInterface.h"

#include "Abilities/PF2CharacterAbilitySystemInterface.h"

#include "Utilities/PF2GameplayAbilityUtilities.h"

UPF2AbilityTask_AcquireTargetFromPlayerController* UPF2AbilityTask_AcquireTargetFromPlayerController::CreateAcquireTargetFromPlayerController(
	UGameplayAbility*                           OwningAbility,
	const FName                                 TaskInstanceName,
	const EPF2AbilityAllowedTargetSelectionType AllowedTargetType,
	const FGameplayTagContainer&                RequiredTargetCharacterTags)
{
	UPF2AbilityTask_AcquireTargetFromPlayerController* Task =
		NewAbilityTask<UPF2AbilityTask_AcquireTargetFromPlayerController>(OwningAbility, TaskInstanceName);

	Task->AllowedTargetType           = AllowedTargetType;
	Task->RequiredTargetCharacterTags = RequiredTargetCharacterTags;

	return Task;
}

void UPF2AbilityTask_AcquireTargetFromPlayerController::Activate()
{
	Super::Activate();

	if (!this->HasAbility())
	{
		return;
	}

	if (this->IsLocallyControlled())
	{
		TScriptInterface<IPF2CharacterAbilitySystemInterface> CharacterAscIntf;
		TScriptInterface<IPF2CharacterInterface>              CharacterIntf;
		TScriptInterface<IPF2PlayerControllerInterface>       PlayerController;

		CharacterAscIntf = this->GetCharacterAbilitySystemComponent();

		if (CharacterAscIntf != nullptr)
		{
			CharacterIntf = CharacterAscIntf->GetCharacter();
		}

		if (CharacterIntf != nullptr)
		{
			PlayerController = CharacterIntf->GetPlayerController();
		}

		if (PlayerController == nullptr)
		{
			// No player controller to interrogate.
			this->EndTask();
		}
		else
		{
			const FHitResult TargetLocation = PlayerController->GetTargetLocation();

			this->NotifyListenersAboutTarget(
				MakeTargetData(TargetLocation),
				PF2GameplayAbilityUtilities::GetTag(
					FName("GameplayAbility.Event.TargetReceived.Location")
				)
			);
		}
	}
	else
	{
		this->WaitForTargetFromClient();
	}
}

void UPF2AbilityTask_AcquireTargetFromPlayerController::ExternalCancel()
{
	if (this->TaskState != EGameplayTaskState::Finished)
	{
		this->Native_OnAbilityCancelled();
	}

	Super::ExternalCancel();
}

void UPF2AbilityTask_AcquireTargetFromPlayerController::WaitForTargetFromClient()
{
	const FGameplayAbilitySpecHandle SpecHandle              = this->GetAbilitySpecHandle();
	const FPredictionKey             ActivationPredictionKey = this->GetActivationPredictionKey();
	UAbilitySystemComponent*         Asc                     = this->GetNativeAbilitySystemComponent();

	if (!IsValid(this))
	{
		return;
	}

	check(this->Ability != nullptr);
	check(Asc);

	Asc->AbilityTargetDataSetDelegate(SpecHandle, ActivationPredictionKey).AddUObject(
		this,
		&UPF2AbilityTask_AcquireTargetFromPlayerController::Native_OnTargetDataReplicatedFromClient
	);

	Asc->AbilityTargetDataCancelledDelegate(SpecHandle, ActivationPredictionKey).AddUObject(
		this,
		&UPF2AbilityTask_AcquireTargetFromPlayerController::Native_OnTargetDataNotAvailableFromClient
	);

	Asc->CallReplicatedTargetDataDelegatesIfSet(SpecHandle, ActivationPredictionKey);

	this->SetWaitingOnRemotePlayerData();
}

void UPF2AbilityTask_AcquireTargetFromPlayerController::NotifyListenersAboutTarget(
	const FGameplayAbilityTargetDataHandle& Data,
	const FGameplayTag TargetTypeTag) const
{
	if (this->ShouldBroadcastAbilityTaskDelegates())
	{
		const FGameplayTag ReceivedCharacterTag =
			PF2GameplayAbilityUtilities::GetTag(FName("GameplayAbility.Event.TargetReceived.Character"));

		const FGameplayTag ReceivedLocationTag =
			PF2GameplayAbilityUtilities::GetTag(FName("GameplayAbility.Event.TargetReceived.Location"));

		if (TargetTypeTag.MatchesTagExact(ReceivedCharacterTag))
		{
			this->OnCharacterSelected.Broadcast(Data);
		}
		else if (TargetTypeTag.MatchesTagExact(ReceivedLocationTag))
		{
			this->OnLocationSelected.Broadcast(Data);
		}
	}
}

FGameplayAbilityTargetDataHandle UPF2AbilityTask_AcquireTargetFromPlayerController::MakeTargetData(
	const FHitResult& HitResult)
{
	FGameplayAbilityTargetDataHandle            ReturnDataHandle;
	FGameplayAbilityTargetData_SingleTargetHit* ReturnData;

	/** The ReturnData is cleaned up by the FGameplayAbilityTargetDataHandle (via an internal TSharedPtr) */
	ReturnData            = new FGameplayAbilityTargetData_SingleTargetHit();
	ReturnData->HitResult = HitResult;

	ReturnDataHandle.Add(ReturnData);

	return ReturnDataHandle;
}

void UPF2AbilityTask_AcquireTargetFromPlayerController::Native_OnAbilityCancelled() const
{
	if (this->ShouldBroadcastAbilityTaskDelegates())
	{
		this->OnCancelled.Broadcast(FGameplayAbilityTargetDataHandle());
	}
}

void UPF2AbilityTask_AcquireTargetFromPlayerController::Native_OnTargetDataReady(
	const FGameplayAbilityTargetDataHandle& Data,
	const FGameplayTag TargetTypeTag)
{
	UAbilitySystemComponent* NativeAsc = this->GetNativeAbilitySystemComponent();

	if (!this->HasAbility())
	{
		return;
	}

	FScopedPredictionWindow	ScopedPrediction(NativeAsc, true);

	// Notify the server we have data!
	if (this->IsPredictingClient())
	{
		NativeAsc->CallServerSetReplicatedTargetData(
			this->GetAbilitySpecHandle(),
			this->GetActivationPredictionKey(),
			Data,
			TargetTypeTag,
			NativeAsc->ScopedPredictionKey
		);
	}

	this->NotifyListenersAboutTarget(Data, TargetTypeTag);
	this->EndTask();
}

void UPF2AbilityTask_AcquireTargetFromPlayerController::Native_OnTargetDataNotAvailable()
{
	// TODO for later tickets: Implement.
}

void UPF2AbilityTask_AcquireTargetFromPlayerController::Native_OnTargetDataReplicatedFromClient(
	const FGameplayAbilityTargetDataHandle& Data,
	const FGameplayTag                      TargetTypeTag)
{
	UAbilitySystemComponent* Asc = this->GetNativeAbilitySystemComponent();

	// TODO for later tickets: Validate that the target is acceptable by server rules in order to prevent cheating.

	Asc->ConsumeClientReplicatedTargetData(
		this->GetAbilitySpecHandle(),
		this->GetActivationPredictionKey()
	);

	this->NotifyListenersAboutTarget(Data, TargetTypeTag);
	this->EndTask();
}

void UPF2AbilityTask_AcquireTargetFromPlayerController::Native_OnTargetDataNotAvailableFromClient()
{
	// TODO for later tickets: Implement.
}

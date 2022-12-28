// OpenPF2 for UE Game Logic, Copyright 2022, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
//
// Portions of this code were adapted from or inspired by the "Real-Time Strategy Plugin for Unreal Engine 4" by Nick
// Pruehs, provided under the MIT License. Copyright (c) 2017 Nick Pruehs.
//

#include <Net/UnrealNetwork.h>

#include "PF2CharacterInterface.h"
#include "PF2Party.h"
#include "PF2PlayerControllerInterface.h"
#include "PF2PlayerStateInterface.h"

#include "Utilities/PF2ArrayUtilities.h"
#include "Utilities/PF2InterfaceUtilities.h"

APF2Party::APF2Party()
{
	this->bReplicates        = true;
	this->bAlwaysRelevant    = true;
	this->NetUpdateFrequency = 1.0f;
}

void APF2Party::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APF2Party, PartyName);
	DOREPLIFETIME(APF2Party, PartyIndex);
	DOREPLIFETIME(APF2Party, MemberStates);
	DOREPLIFETIME(APF2Party, MemberCharacters);
}

inline FText APF2Party::GetPartyName() const
{
	return this->PartyName;
}

int32 APF2Party::GetPartyIndex() const
{
	return this->PartyIndex;
}

TArray<TScriptInterface<IPF2PlayerControllerInterface>> APF2Party::GetMemberControllers() const
{
	return PF2ArrayUtilities::Map<TScriptInterface<IPF2PlayerControllerInterface>>(
		this->GetMemberStates(),
		[](const TScriptInterface<IPF2PlayerStateInterface> PlayerState)
		{
			return PlayerState->GetPlayerController();
		}
	);
}

TArray<TScriptInterface<IPF2PlayerStateInterface>> APF2Party::GetMemberStates() const
{
	return PF2ArrayUtilities::Map<TScriptInterface<IPF2PlayerStateInterface>>(
		this->MemberStates,
		[](APlayerState* PlayerState)
		{
			IPF2PlayerStateInterface* PlayerStateIntf = Cast<IPF2PlayerStateInterface>(PlayerState);
			check(PlayerStateIntf != nullptr);

			return PF2InterfaceUtilities::ToScriptInterface(PlayerStateIntf);
		}
	);
}

TArray<TScriptInterface<IPF2CharacterInterface>> APF2Party::GetMemberCharacters() const
{
	return PF2ArrayUtilities::Map<TScriptInterface<IPF2CharacterInterface>>(
		this->MemberCharacters,
		[](AActor* CharacterActor)
		{
			IPF2CharacterInterface* CharacterIntf = Cast<IPF2CharacterInterface>(CharacterActor);
			check(CharacterIntf != nullptr);

			return PF2InterfaceUtilities::ToScriptInterface(CharacterIntf);
		}
	);
}

void APF2Party::AddPlayerToPartyByController(const TScriptInterface<IPF2PlayerControllerInterface>& Controller)
{
	check(Controller != nullptr);
	this->AddPlayerToPartyByState(Controller->GetPlayerState());
}

void APF2Party::AddPlayerToPartyByState(const TScriptInterface<IPF2PlayerStateInterface>& PlayerState)
{
	APlayerState* PlayerStateActor;

	check(PlayerState != nullptr);

	PlayerStateActor = PlayerState->ToPlayerState();

	if (!this->MemberStates.Contains(PlayerStateActor))
	{
		const TScriptInterface<IPF2PlayerControllerInterface> PlayerController = PlayerState->GetPlayerController();

		this->MemberStates.AddUnique(PlayerStateActor);

		check(PlayerController != nullptr);

		for (const auto& Character : PlayerController->GetControllableCharacters())
		{
			this->MemberCharacters.AddUnique(Character->ToActor());
		}

		this->Native_OnPlayerAdded(PlayerState);
	}
}

void APF2Party::RemovePlayerFromPartyByController(const TScriptInterface<IPF2PlayerControllerInterface>& Controller)
{
	check(Controller != nullptr);
	this->RemovePlayerFromPartyByState(Controller->GetPlayerState());
}

void APF2Party::RemovePlayerFromPartyByState(const TScriptInterface<IPF2PlayerStateInterface>& PlayerState)
{
	APlayerState* PlayerStateActor;

	check(PlayerState != nullptr);

	PlayerStateActor = PlayerState->ToPlayerState();

	if (this->MemberStates.Contains(PlayerStateActor))
	{
		this->MemberStates.Remove(PlayerStateActor);

		for (const auto& Character : PlayerState->GetPlayerController()->GetControllableCharacters())
		{
			this->MemberCharacters.Remove(Character->ToActor());
		}

		this->Native_OnPlayerRemoved(PlayerState);
	}
}

FString APF2Party::GetIdForLogs() const
{
	// ReSharper disable twice CppRedundantParentheses
	return FString::Format(
		TEXT("{0}[{1}]"),
		{
			*(this->GetPartyName().ToString()),
			this->GetPartyIndex()
		}
	);
}

void APF2Party::Native_OnPlayerAdded(const TScriptInterface<IPF2PlayerStateInterface>& PlayerState)
{
	check(PlayerState != nullptr);

	// Notify listeners.
	this->BP_OnPlayerAdded(PlayerState);
	this->OnPlayerAdded.Broadcast(this, PlayerState);
}

void APF2Party::Native_OnPlayerRemoved(const TScriptInterface<IPF2PlayerStateInterface>& PlayerState)
{
	check(PlayerState != nullptr);

	// Notify listeners.
	this->BP_OnPlayerRemoved(PlayerState);
	this->OnPlayerRemoved.Broadcast(this, PlayerState);
}

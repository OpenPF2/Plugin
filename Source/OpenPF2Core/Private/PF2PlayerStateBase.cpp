// OpenPF2 for UE Game Logic, Copyright 2022, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
//
// This code is adapted from the "Real-Time Strategy Plugin for Unreal Engine 4" by Nick Pruehs, provided under the MIT
// License. Copyright (c) 2017 Nick Pruehs.
//

#include "PF2PlayerStateBase.h"

#include "PF2CharacterInterface.h"
#include "PF2Party.h"

#include "Utilities/PF2ArrayUtilities.h"
#include "Utilities/PF2InterfaceUtilities.h"

void APF2PlayerStateBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

uint8 APF2PlayerStateBase::GetPlayerIndex() const
{
	return this->PlayerIndex;
}

TScriptInterface<IPF2Party> APF2PlayerStateBase::GetParty() const
{
	return this->Party;
}

TScriptInterface<IPF2PlayerControllerInterface> APF2PlayerStateBase::GetPlayerController() const
{
	IPF2PlayerControllerInterface* PlayerControllerIntf = Cast<IPF2PlayerControllerInterface>(this->GetOwner());

	return PF2InterfaceUtilities::ToScriptInterface(PlayerControllerIntf);
}

bool APF2PlayerStateBase::IsSamePartyAsPlayerWithController(
	const TScriptInterface<IPF2PlayerControllerInterface>& OtherPlayerController) const
{
	return this->IsSamePartyAsPlayerWithState(OtherPlayerController->GetPlayerState());
}

bool APF2PlayerStateBase::IsSamePartyAsPlayerWithState(
	const TScriptInterface<IPF2PlayerStateInterface>& OtherPlayerState) const
{
	const TScriptInterface<IPF2Party> ThisParty  = this->GetParty(),
	                                  OtherParty = OtherPlayerState->GetParty();

	return ThisParty->GetPartyIndex() == OtherParty->GetPartyIndex();
}

TArray<TScriptInterface<IPF2CharacterInterface>> APF2PlayerStateBase::GetControllableCharacters() const
{
	return PF2ArrayUtilities::Reduce<TArray<TScriptInterface<IPF2CharacterInterface>>>(
		this->ControllableCharacters,
		TArray<TScriptInterface<IPF2CharacterInterface>>(),
		[](TArray<TScriptInterface<IPF2CharacterInterface>> Characters,
		   const TWeakInterfacePtr<IPF2CharacterInterface>  CurrentCharacter)
		{
			if (CurrentCharacter.IsValid())
			{
				Characters.Add(PF2InterfaceUtilities::ToScriptInterface(CurrentCharacter.Get()));
			}

			return Characters;
		});
}

APlayerState* APF2PlayerStateBase::ToPlayerState()
{
	return this;
}

void APF2PlayerStateBase::NotifyOnPartyChanged(TScriptInterface<IPF2Party> NewParty)
{
	UE_LOG(
		LogPf2Core,
		Log,
		TEXT("Player %s added to party %d."),
		*this->GetIdForLogs(),
		NewParty->GetPartyIndex()
	);

	// Notify listeners.
	this->OnPartyChanged(NewParty);
}

void APF2PlayerStateBase::NotifyOnActorOwnershipChanged(AActor* Actor,
                                                        const TScriptInterface<IPF2PlayerStateInterface>& PreviousOwner,
                                                        const TScriptInterface<IPF2PlayerStateInterface>& NewOwner)
{
	IPF2CharacterInterface* CharacterActor = Cast<IPF2CharacterInterface>(Actor);

	if (CharacterActor != nullptr)
	{
		const TWeakInterfacePtr<IPF2CharacterInterface> WeakCharacterActor(CharacterActor);

		if (NewOwner == this)
		{
			this->ControllableCharacters.AddUnique(WeakCharacterActor);
		}
		else
		{
			this->ControllableCharacters.Remove(WeakCharacterActor);
		}
	}
}

FString APF2PlayerStateBase::GetIdForLogs() const
{
	return this->GetName();
}

void APF2PlayerStateBase::ReceivedParty(TScriptInterface<IPF2Party> NewParty)
{
	this->NotifyOnPartyChanged(NewParty);
}

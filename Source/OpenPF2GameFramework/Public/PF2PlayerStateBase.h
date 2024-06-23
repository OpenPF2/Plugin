// OpenPF2 for UE Game Logic, Copyright 2022-2024, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
//
// Portions of this code were adapted from or inspired by the "Real-Time Strategy Plugin for Unreal Engine 4" by Nick
// Pruehs, provided under the MIT License. Copyright (c) 2017 Nick Pruehs.

#pragma once

#include <GameFramework/PlayerState.h>

#include <UObject/WeakInterfacePtr.h>

#include "PF2PlayerStateInterface.h"

#include "PF2PlayerStateBase.generated.h"

// =====================================================================================================================
// Forward Declarations (to minimize header dependencies)
// =====================================================================================================================
class IPF2CharacterInterface;

// =====================================================================================================================
// Normal Declarations
// =====================================================================================================================
/**
 * Default base class for OpenPF2 Player States.
 *
 * @see IPF2PlayerStateInterface
*/
UCLASS(Abstract)
// ReSharper disable once CppClassCanBeFinal
class OPENPF2GAMEFRAMEWORK_API APF2PlayerStateBase : public APlayerState, public IPF2PlayerStateInterface
{
	GENERATED_BODY()

	// =================================================================================================================
	// Private Fields
	// =================================================================================================================
	/**
	 * The zero-based index of this player.
	 *
	 * This is assigned by the server upon the player joining the game.
	 */
	UPROPERTY(Replicated)
	uint8 PlayerIndex;

	/**
	 * The party to which this player is affiliated.
	 */
	UPROPERTY(ReplicatedUsing=OnRep_Party)
	TScriptInterface<IPF2PartyInterface> Party;

	/**
	 * The cached player controller for this player state.
	 *
	 * This is memoized by APF2PlayerStateBase::GetPlayerController().
	 */
	UPROPERTY()
	mutable TScriptInterface<IPF2PlayerControllerInterface> CachedPlayerController;

public:
	/**
	 * Default constructor for APF2PlayerStateBase.
	 */
	APF2PlayerStateBase(): PlayerIndex(0)
	{
	}

	// =================================================================================================================
	// Public Methods - APlayerState Overrides
	// =================================================================================================================
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	// =================================================================================================================
	// Public Methods - IPF2PlayerStateInterface Implementation
	// =================================================================================================================
	virtual int32 GetPlayerIndex() const override;

	virtual void SetPlayerIndex(int32 NewPlayerIndex) override;

	virtual TScriptInterface<IPF2PartyInterface> GetParty() const override;

	virtual void SetParty(const TScriptInterface<IPF2PartyInterface> NewParty) override;

	virtual TScriptInterface<IPF2PlayerControllerInterface> GetPlayerControllerIntf() const override;

	virtual bool IsSamePartyAsPlayerWithController(
		const TScriptInterface<IPF2PlayerControllerInterface>& OtherPlayerController
	) const override;

	virtual bool IsSamePartyAsPlayerWithState(
		const TScriptInterface<IPF2PlayerStateInterface>& OtherPlayerState
	) const override;

	virtual APlayerState* ToPlayerState() override;

	// =================================================================================================================
	// Public Methods - IPF2LogIdentifiableInterface Implementation
	// =================================================================================================================
	virtual FString GetIdForLogs() const override;

protected:
	// =================================================================================================================
	// Protected Replication Callbacks
	// =================================================================================================================
	/**
	 * Notifies this component that party information has been replicated.
	 *
	 * @param OldParty
	 *	The previous party to which the player was affiliated.
	 */
	UFUNCTION()
	void OnRep_Party(const TScriptInterface<IPF2PartyInterface> OldParty);

	// =================================================================================================================
	// Protected Native Event Callbacks
	// =================================================================================================================
	/**
	 * Notifies this player state that the player who owns it is now a member of a different party.
	 *
	 * This is invoked after the party of the player has been updated.
	 *
	 * @param OldParty
	 *	The previous party to which the player was affiliated.
	 * @param NewParty
	 *	The new party to which the player is affiliated.
	 */
	void Native_OnPartyChanged(
		const TScriptInterface<IPF2PartyInterface> OldParty,
		const TScriptInterface<IPF2PartyInterface> NewParty
	);

	// =================================================================================================================
	// Blueprint Implementable Events
	// =================================================================================================================
	/**
	 * BP event invoked when this player has changed party affiliation.
	 *
	 * @param OldParty
	 *	The old party to which the player was affiliated.
	 * @param NewParty
	 *	The party to which the player is now affiliated.
	 */
	UFUNCTION(
		BlueprintImplementableEvent,
		Category="OpenPF2|Player States",
		meta=(DisplayName="On Party Changed")
	)
	void BP_OnPartyChanged(
		const TScriptInterface<IPF2PartyInterface>& OldParty,
		const TScriptInterface<IPF2PartyInterface>& NewParty
	);
};

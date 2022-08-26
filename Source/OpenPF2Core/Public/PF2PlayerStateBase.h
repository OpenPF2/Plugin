// OpenPF2 for UE Game Logic, Copyright 2022, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
//
// Portions of this code were adapted from or inspired by the "Real-Time Strategy Plugin for Unreal Engine 4" by Nick
// Pruehs, provided under the MIT License. Copyright (c) 2017 Nick Pruehs.

#pragma once

#include <UObject/WeakInterfacePtr.h>
#include <GameFramework/PlayerState.h>

#include "PF2PlayerStateInterface.h"

#include "PF2PlayerStateBase.generated.h"

// =====================================================================================================================
// Forward Declarations (to break recursive dependencies)
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
class OPENPF2CORE_API APF2PlayerStateBase : public APlayerState, public IPF2PlayerStateInterface
{
	GENERATED_BODY()

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
	UFUNCTION(BlueprintCallable)
	virtual uint8 GetPlayerIndex() const override;

	virtual void SetPlayerIndex(uint8 NewPlayerIndex) override;

	UFUNCTION(BlueprintCallable)
	virtual TScriptInterface<IPF2Party> GetParty() const override;

	UFUNCTION(BlueprintCallable)
	virtual TScriptInterface<IPF2PlayerControllerInterface> GetPlayerController() const override;

	UFUNCTION(BlueprintCallable)
	virtual bool IsSamePartyAsPlayerWithController(
		const TScriptInterface<IPF2PlayerControllerInterface>& OtherPlayerController
	) const override;

	UFUNCTION(BlueprintCallable)
	virtual bool IsSamePartyAsPlayerWithState(
		const TScriptInterface<IPF2PlayerStateInterface>& OtherPlayerState
	) const override;

	UFUNCTION(BlueprintCallable)
	virtual TArray<TScriptInterface<IPF2CharacterInterface>> GetControllableCharacters() const override;

	UFUNCTION(BlueprintCallable)
	virtual APlayerState* ToPlayerState() override;

	virtual void Native_OnPartyChanged(TScriptInterface<IPF2Party> NewParty) override;

	virtual void Native_OnActorOwnershipChanged(
		AActor*                                           Actor,
		const TScriptInterface<IPF2PlayerStateInterface>& PreviousOwner,
		const TScriptInterface<IPF2PlayerStateInterface>& NewOwner
	) override;

	// =================================================================================================================
	// Public Methods - IPF2LogIdentifiableInterface Overrides
	// =================================================================================================================
	UFUNCTION(BlueprintCallable)
	virtual FString GetIdForLogs() const override;

protected:
	// =================================================================================================================
	// Blueprint Implementable Events
	// =================================================================================================================
	/**
	 * BP event invoked when this player has changed party affiliation.
	 *
	 * @param NewParty
	 *	The new party to which the player is affiliated.
	 */
	UFUNCTION(
		BlueprintImplementableEvent,
		Category="OpenPF2|Player States",
		meta=(
			DisplayName="On Party Changed"
		)
	)
	void BP_OnPartyChanged(const TScriptInterface<IPF2Party>& NewParty);

private:
	// =================================================================================================================
	// Private Properties
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
	UPROPERTY(ReplicatedUsing=ReceivedParty)
	TScriptInterface<IPF2Party> Party;

	/**
	 * The characters that can be controlled by this player.
	 *
	 * Depending on the game, this may represent some or all of the characters in this player's party.
	 */
	TArray<TWeakInterfacePtr<IPF2CharacterInterface>> ControllableCharacters;

	// =================================================================================================================
	// Private Replication Callbacks
	// =================================================================================================================
	/**
	 * Notifies this component that party information has been replicated.
	 *
	 * @param NewParty
	 *	The new party to which the player is affiliated.
	 */
	UFUNCTION()
	void ReceivedParty(TScriptInterface<IPF2Party> NewParty);
};

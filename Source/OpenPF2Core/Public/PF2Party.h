// OpenPF2 for UE Game Logic, Copyright 2022, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
//
// Portions of this code were adapted from or inspired by the "Real-Time Strategy Plugin for Unreal Engine 4" by Nick
// Pruehs, provided under the MIT License. Copyright (c) 2017 Nick Pruehs.
//
#pragma once

#include <GameFramework/Info.h>

#include "PF2PartyInterface.h"

#include "PF2Party.generated.h"

// =====================================================================================================================
// Forward Declarations (to break recursive dependencies)
// =====================================================================================================================
class IPF2CharacterInterface;
class IPF2PlayerStateInterface;

// =====================================================================================================================
// Delegate Types
// =====================================================================================================================
/**
 * Delegate for Blueprints to react to a change in player membership.
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(
	FPF2PartyMemberChangedDelegate,
	TScriptInterface<IPF2PartyInterface>,       Party,
	TScriptInterface<IPF2PlayerStateInterface>, PlayerState
);

// =====================================================================================================================
// Normal Declarations
// =====================================================================================================================
/**
 * Default implementation of a PF2-compatible party.
 */
UCLASS(BlueprintType, Blueprintable)
// ReSharper disable once CppClassCanBeFinal
class OPENPF2CORE_API APF2Party : public AInfo, public IPF2PartyInterface
{
	GENERATED_BODY()

protected:
	/**
	 * The player-readable name of this party.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Replicated, Category="OpenPF2 Party")
	FText PartyName;

	/**
	 * The index of this party.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Replicated, Category="OpenPF2 Party")
	int32 PartyIndex;

	/**
	 * Player state for all players belonging to this party.
	 *
	 * This is an array of player state actors (instead of interfaces) for replication. UE will not replicate actors if
	 * they are declared/referenced through an interface property.
	 */
	UPROPERTY(Replicated)
	TArray<APlayerState*> MemberStates;

	/**
	 * The characters belonging to this party.
	 *
	 * This is an array of character actors (instead of interfaces) for replication. UE will not replicate actors if
	 * they are declared/referenced through an interface property.
	 */
	UPROPERTY(Replicated)
	TArray<AActor*> MemberCharacters;

public:
	APF2Party();

	// =================================================================================================================
	// Public Methods - AActor Overrides
	// =================================================================================================================
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	// =================================================================================================================
	// Public Methods - IPF2PartyInterface Overrides
	// =================================================================================================================
	UFUNCTION(BlueprintCallable)
	virtual FText GetPartyName() const override;

	UFUNCTION(BlueprintCallable)
	virtual int32 GetPartyIndex() const override;

	UFUNCTION(BlueprintCallable)
	virtual TArray<TScriptInterface<IPF2PlayerControllerInterface>> GetMemberControllers() const override;

	UFUNCTION(BlueprintCallable)
	virtual TArray<TScriptInterface<IPF2PlayerStateInterface>> GetMemberStates() const override;

	UFUNCTION(BlueprintCallable)
	virtual TArray<TScriptInterface<IPF2CharacterInterface>> GetMemberCharacters() const override;

	UFUNCTION(BlueprintCallable)
	virtual void AddPlayerToPartyByController(const TScriptInterface<IPF2PlayerControllerInterface>& Controller) override;

	UFUNCTION(BlueprintCallable)
	virtual void AddPlayerToPartyByState(const TScriptInterface<IPF2PlayerStateInterface>& PlayerState) override;

	UFUNCTION(BlueprintCallable)
	virtual void RemovePlayerFromPartyByController(const TScriptInterface<IPF2PlayerControllerInterface>& Controller) override;

	UFUNCTION(BlueprintCallable)
	virtual void RemovePlayerFromPartyByState(const TScriptInterface<IPF2PlayerStateInterface>& PlayerState) override;

	// =================================================================================================================
	// Public Methods - IPF2LogIdentifiableInterface Overrides
	// =================================================================================================================
	UFUNCTION(BlueprintCallable)
	virtual FString GetIdForLogs() const override;

	// =================================================================================================================
	// Public Properties - Multicast Delegates
	// =================================================================================================================
	/**
	 * Event fired when a player is added to this party.
	 */
	UPROPERTY(BlueprintAssignable, Category="OpenPF2|Parties")
	FPF2PartyMemberChangedDelegate OnPlayerAdded;

	/**
	 * Event fired when a player is removed from this party.
	 */
	UPROPERTY(BlueprintAssignable, Category="OpenPF2|Parties")
	FPF2PartyMemberChangedDelegate OnPlayerRemoved;

protected:
	// =================================================================================================================
	// Protected Native Event Callbacks
	// =================================================================================================================
	/**
	 * Notifies this party that a player has been added to this party.
	 *
	 * @param PlayerState
	 *	The state of the player that corresponds to the player that was added to the party.
	 */
	void Native_OnPlayerAdded(const TScriptInterface<IPF2PlayerStateInterface>& PlayerState);

	/**
	 * Notifies this party that a player has been removed from this party.
	 *
	 * @param PlayerState
	 *	The state of the player that corresponds to the player that was removed from this party.
	 */
	void Native_OnPlayerRemoved(const TScriptInterface<IPF2PlayerStateInterface>& PlayerState);

	// =================================================================================================================
	// Blueprint Implementable Events
	// =================================================================================================================
	/**
	 * BP event invoked when a player has been added to this party.
	 *
	 * @param PlayerState
	 *	The state of the player that corresponds to the player that was added to this party.
	 */
	UFUNCTION(
		BlueprintImplementableEvent,
		Category="OpenPF2|Parties",
		meta=(DisplayName="On Player Added")
	)
	void BP_OnPlayerAdded(const TScriptInterface<IPF2PlayerStateInterface>& PlayerState);

	/**
	 * BP event invoked when a player has been removed from this party.
	 *
	 * @param PlayerState
	 *	The state of the player that corresponds to the player that was removed from this party.
	 */
	UFUNCTION(
		BlueprintImplementableEvent,
		Category="OpenPF2|Parties",
		meta=(DisplayName="On Player Removed")
	)
	void BP_OnPlayerRemoved(const TScriptInterface<IPF2PlayerStateInterface>& PlayerState);
};

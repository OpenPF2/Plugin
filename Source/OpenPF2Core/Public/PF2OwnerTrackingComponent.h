// OpenPF2 for UE Game Logic, Copyright 2022, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
//
// Portions of this code were adapted from or inspired by the "Real-Time Strategy Plugin for Unreal Engine 4" by Nick
// Pruehs, provided under the MIT License. Copyright (c) 2017 Nick Pruehs.

#pragma once

#include <Components/ActorComponent.h>

#include <GameFramework/Controller.h>
#include <GameFramework/Info.h>

#include "PF2OwnerTrackingInterface.h"

#include "PF2OwnerTrackingComponent.generated.h"

// =====================================================================================================================
// Forward Declarations (to break recursive dependencies)
// =====================================================================================================================
class IPF2PlayerControllerInterface;
class IPF2PlayerStateInterface;

// =====================================================================================================================
// Delegate Declarations
// =====================================================================================================================
/**
 * Delegate for Blueprints to react to a change in owning player state.
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(
	FPF2OwnerComponentOwningPlayerStateChangedDelegate,
	AActor*,                                    Actor,
	TScriptInterface<IPF2PlayerStateInterface>, OldOwner,
	TScriptInterface<IPF2PlayerStateInterface>, NewOwner
);

/**
 * Delegate for Blueprints to react to a change in party affiliation.
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(
	FPF2OwnerComponentPartyChangedDelegate,
	AActor*,                              Actor,
	TScriptInterface<IPF2PartyInterface>, OldParty,
	TScriptInterface<IPF2PartyInterface>, NewParty
);

// =====================================================================================================================
// Normal Declarations
// =====================================================================================================================
UCLASS(ClassGroup="OpenPF2-Characters", meta=(BlueprintSpawnableComponent))
// ReSharper disable once CppClassCanBeFinal
class OPENPF2CORE_API UPF2OwnerTrackingComponent : public UActorComponent, public IPF2OwnerTrackingInterface
{
	GENERATED_BODY()

public:
	// =================================================================================================================
	// Constructors
	// =================================================================================================================
	UPF2OwnerTrackingComponent();

	// =================================================================================================================
	// Public Methods - UActorComponent Overrides
	// =================================================================================================================
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	// =================================================================================================================
	// Public Methods - IPF2OwnerTrackingInterface Implementation
	// =================================================================================================================
	UFUNCTION(BlueprintCallable)
	virtual TScriptInterface<IPF2PartyInterface> GetParty() const override;

	UFUNCTION(BlueprintCallable)
	virtual void SetParty(const TScriptInterface<IPF2PartyInterface> NewParty) override;

	UFUNCTION(BlueprintCallable)
	virtual TScriptInterface<IPF2PlayerStateInterface> GetStateOfOwningPlayer() const override;

	UFUNCTION(BlueprintCallable)
	virtual void SetOwningPlayerByController(const TScriptInterface<IPF2PlayerControllerInterface> NewController) override;

	UFUNCTION(BlueprintCallable)
	virtual void SetOwningPlayerByState(const TScriptInterface<IPF2PlayerStateInterface> NewPlayerState) override;

	UFUNCTION(BlueprintCallable)
	virtual bool IsSamePartyAsActor(AActor* OtherActor) const override;

	UFUNCTION(BlueprintCallable)
	virtual bool IsSamePartyAsPlayerWithController(
		const TScriptInterface<IPF2PlayerControllerInterface> OtherController
	) const override;

	// =================================================================================================================
	// Public Methods - IPF2ActorComponentInterface Implementation
	// =================================================================================================================
	UFUNCTION(BlueprintCallable)
	virtual UActorComponent* ToActorComponent() override;

	// =================================================================================================================
	// Public Methods - IPF2LogIdentifiableInterface Implementation
	// =================================================================================================================
	UFUNCTION(BlueprintCallable)
	virtual FString GetIdForLogs() const override;

	// =================================================================================================================
	// Public Fields - Multicast Delegates
	// =================================================================================================================
	/**
	 * Event fired when the containing actor is owned by a different player.
	 */
	UPROPERTY(BlueprintAssignable, Category="OpenPF2|Components|Characters|Owner Tracking")
	FPF2OwnerComponentOwningPlayerStateChangedDelegate OnOwnerChanged;

	/**
	 * Event fired when the containing actor changes party affiliations.
	 */
	UPROPERTY(BlueprintAssignable, Category="OpenPF2|Components|Characters|Owner Tracking")
	FPF2OwnerComponentPartyChangedDelegate OnPartyChanged;

protected:
	// =================================================================================================================
	// Protected Replication Callbacks
	// =================================================================================================================
	/**
	 * Notifies this component that the player state for the player who owns the containing actor has been replicated.
	 *
	 * @param OldOwner
	 *	The previous owner of the containing actor.
	 */
	UFUNCTION()
	void OnRep_OwningPlayerState(APlayerState* OldOwner) const;

	/**
	 * Notifies this component that the party to which the containing actor is affiliated has been replicated.
	 *
	 * @param OldParty
	 *	The previous party affiliation of the containing actor.
	 */
	UFUNCTION()
	void OnRep_Party(AInfo* OldParty) const;

	// =================================================================================================================
	// Protected Native Event Notifications
	// =================================================================================================================
	/**
	 * Notifies all event listeners that the player state that own the containing actor has changed.
	 *
	 * @param OldOwner
	 *	The player state corresponding to the player who was the previous owner of this actor. Can be null if there was
	 *	no prior owner.
	 * @param NewOwner
	 *	The player state corresponding to the player who is now the owner of this actor. Can be null if there is no
	 *	new owner (containing actor does not belong to anyone/is an orphan).
	 */
	void Native_OnOwningPlayerStateChanged(
		const TScriptInterface<IPF2PlayerStateInterface> OldOwner,
		const TScriptInterface<IPF2PlayerStateInterface> NewOwner
	) const;

	/**
	 * Notifies all event listeners that the party to which the containing actor is affiliated has changed.
	 *
	 * @param OldParty
	 *	The previous party affiliation, if any. Can be null if there was no prior party affiliation.
	 * @param NewParty
	 *	The new party affiliation, if any. Can be null if the containing actor should no longer be affiliated with a
	 *	party.
	 */
	void Native_OnPartyChanged(
		const TScriptInterface<IPF2PartyInterface> OldParty,
		const TScriptInterface<IPF2PartyInterface> NewParty
	) const;

private:
	// =================================================================================================================
	// Private Fields
	// =================================================================================================================
	/**
	 * The state of the player who owns the containing actor.
	 *
	 * This is a standard player state (instead of an interface) for replication. UE will not replicate actors if they
	 * are declared/referenced through an interface property. The value of this property MUST implement
	 * IPF2PlayerStateInterface.
	 */
	UPROPERTY(ReplicatedUsing=OnRep_OwningPlayerState)
	APlayerState* OwningPlayerState;

	/**
	 * The party to which the containing actor is affiliated, if any.
	 *
	 * This is an info actor (instead of an interface) for replication. UE will not replicate actors if they are
	 * declared/referenced through an interface property. The value of this property MUST implement IPF2PartyInterface.
	 */
	UPROPERTY(ReplicatedUsing=OnRep_Party)
	AInfo* Party;
};

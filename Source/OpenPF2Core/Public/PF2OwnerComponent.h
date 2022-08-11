// OpenPF2 for UE Game Logic, Copyright 2022, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
//
// This code is adapted from the "Real-Time Strategy Plugin for Unreal Engine 4" by Nick Pruehs, provided under the MIT
// License. Copyright (c) 2017 Nick Pruehs.
//
#pragma once

#include <Components/ActorComponent.h>

#include <GameFramework/Controller.h>

#include "PF2OwnerInterface.h"

#include "PF2OwnerComponent.generated.h"

// =====================================================================================================================
// Forward Declarations (to break recursive dependencies)
// =====================================================================================================================
class IPF2PlayerControllerInterface;
class IPF2PlayerStateInterface;

// =====================================================================================================================
// Delegate Types
// =====================================================================================================================
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(
	FPF2OwnerComponentOwnerChangedDelegate,
	AActor*,      Actor,
	AController*, NewOwner
);

// =====================================================================================================================
// Normal Declarations
// =====================================================================================================================
UCLASS(ClassGroup="OpenPF2|Characters", meta=(BlueprintSpawnableComponent))
// ReSharper disable once CppClassCanBeFinal
class OPENPF2CORE_API UPF2OwnerComponent : public UActorComponent, public IPF2OwnerInterface
{
	GENERATED_BODY()

public:
	// =================================================================================================================
	// Constructors
	// =================================================================================================================
	UPF2OwnerComponent();

	// =================================================================================================================
	// Public Methods - UActorComponent Overrides
	// =================================================================================================================
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	// =================================================================================================================
	// Public Methods - IPF2OwnerInterface Implementation
	// =================================================================================================================
	UFUNCTION(BlueprintPure)
	virtual uint8 GetIndexOfInitialOwningPlayer() const override;

	UFUNCTION(BlueprintPure)
	virtual TScriptInterface<IPF2PlayerStateInterface> GetStateOfOwningPlayer() const override;

	UFUNCTION(BlueprintCallable)
	virtual void SetOwningPlayerByController(TScriptInterface<IPF2PlayerControllerInterface> Controller) override;

	UFUNCTION(BlueprintCallable)
    virtual void SetOwningPlayerByState(TScriptInterface<IPF2PlayerStateInterface> PlayerState) override;

	UFUNCTION(BlueprintPure)
	virtual bool IsSamePartyAsActor(AActor* OtherActor) const override;

	UFUNCTION(BlueprintPure)
	virtual bool IsSamePartyAsPlayerWithController(AController* OtherController) const override;

	// =================================================================================================================
	// Public Methods - IPF2LogIdentifiableInterface Overrides
	// =================================================================================================================
	UFUNCTION(BlueprintCallable)
	virtual FString GetIdForLogs() const override;

	// =================================================================================================================
	// Public Methods
	// =================================================================================================================
	/**
	 * Event when the actor is owned by a different player.
	 */
	UPROPERTY(BlueprintAssignable, Category = "OpenPF2|Components|Characters|Owner")
	FPF2OwnerComponentOwnerChangedDelegate OnOwnerChanged;

private:
	// =================================================================================================================
	// Private Properties
	// =================================================================================================================
	/**
     * The index of the player that should initially own the containing actor.
     */
    UPROPERTY(EditInstanceOnly, Category = "OpenPF2|Components|Characters|Owner")
    uint8 IndexOfInitialOwningPlayer;

	/**
	 * Gets the state of the player who owns the containing actor.
	 */
	UPROPERTY(ReplicatedUsing=ReceivedOwningPlayerState)
	TScriptInterface<IPF2PlayerStateInterface> OwningPlayerState;

	// =================================================================================================================
	// Private Replication Callbacks
	// =================================================================================================================
	/**
	 * Notifies this component that the player state for the player who owns the containing actor has been replicated.
	 *
	 * @param Owner
	 *	The new owner of the containing actor.
	 */
	UFUNCTION()
    void ReceivedOwningPlayerState(const TScriptInterface<IPF2PlayerStateInterface> Owner);

	// =================================================================================================================
	// Private Event Notifications
	// =================================================================================================================
	/**
	 * Notifies all event listeners that the player state that own the containing actor has changed.
	 *
	 * @param PreviousOwner
	 *	The player state corresponding to the player who was the previous owner of this actor. Can be null.
	 * @param NewOwner
	 *	The player state corresponding to the player who is now the owner of this actor. Can be null.
	 */
	void NotifyOnOwningPlayerStateChanged(
		const TScriptInterface<IPF2PlayerStateInterface> PreviousOwner,
		const TScriptInterface<IPF2PlayerStateInterface> NewOwner
	) const;
};

// OpenPF2 for UE Game Logic, Copyright 2022, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#pragma once

#include <Components/ActorComponent.h>

#include <Containers/CircularQueue.h>

#include <GameFramework/Info.h>

#include "PF2CommandQueueInterface.h"

#include "Commands/PF2CharacterCommandInterface.h"

#include "PF2CommandQueueComponent.generated.h"

// =====================================================================================================================
// Delegate Types
// =====================================================================================================================
/**
 * Delegate for Blueprints to react to commands being added to the queue.
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(
	FPF2CommandAddedToQueueDelegate,
	const TScriptInterface<IPF2CharacterCommandInterface>&, Command
);

/**
 * Delegate for Blueprints to react to commands being removed from the queue.
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(
	FPF2CommandRemovedFromQueueDelegate,
	const TScriptInterface<IPF2CharacterCommandInterface>&, Command
);

/**
 * Delegate for Blueprints to react to the queue changing in any way (commands added or removed, or queue cleared).
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(
	FPF2CommandQueueChangedDelegate,
	const TArray<TScriptInterface<IPF2CharacterCommandInterface>>&, Commands
);

// =====================================================================================================================
// Normal Declarations
// =====================================================================================================================
/**
 * A component for managing commands/actions that have been queued for a particular character.
 *
 * (The inspiration for this approach -- of wrapping Gameplay Abilities in a command that can be invoked at any time --
 * came from "ue4-orders-abilities" by Daedalic Entertainment,
 * https://github.com/DaedalicEntertainment/ue4-orders-abilities).
 */
UCLASS(ClassGroup="OpenPF2-Characters", meta=(BlueprintSpawnableComponent))
// ReSharper disable once CppClassCanBeFinal
class OPENPF2CORE_API UPF2CommandQueueComponent : public UActorComponent, public IPF2CommandQueueInterface
{
	GENERATED_BODY()

public:
	// =================================================================================================================
	// Public Constants
	// =================================================================================================================
	/**
	 * Special constant value that signifies that there is no limit to the number of commands that can be enqueued.
	 */
	static const uint8 CommandLimitNone;

protected:
	/**
	 * The queue of commands for the owning character.
	 *
	 * This is an array of actors (instead of interfaces) for replication. UE will not replicate actors if they are
	 * declared/referenced through an interface property.
	 */
	UPROPERTY(ReplicatedUsing=OnRep_Queue)
	TArray<AInfo*> Queue;

	/**
	 * The maximum number of commands that can be in the queue at one time.
	 *
	 * Once the queue reaches this size, no additional commands will be accepted until at least one command already in
	 * the queue has been executed or removed.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	uint8 SizeLimit;

public:
	// =================================================================================================================
	// Public Fields - Multicast Delegates
	// =================================================================================================================
	/**
	 * Event fired when the commands in the queue have changed (commands added, commands removed, or queue cleared).
	 */
	UPROPERTY(BlueprintAssignable)
	FPF2CommandQueueChangedDelegate OnCommandsChanged;

	/**
	 * Event fired when a command has been added to this queue.
	 */
	UPROPERTY(BlueprintAssignable)
	FPF2CommandAddedToQueueDelegate OnCommandAdded;

	/**
	 * Event fired when a command has been removed from this queue.
	 */
	UPROPERTY(BlueprintAssignable)
	FPF2CommandRemovedFromQueueDelegate OnCommandRemoved;

	// =================================================================================================================
	// Public Constructors
	// =================================================================================================================
	/**
	 * Default constructor for UPF2CommandQueueComponent.
	 */
	UPF2CommandQueueComponent();

	// =================================================================================================================
	// Public Methods - AActorComponent Overrides
	// =================================================================================================================
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	// =================================================================================================================
	// Public Methods - IPF2CommandQueueInterface Implementation
	// =================================================================================================================
	UFUNCTION(BlueprintCallable)
	virtual void Enqueue(TScriptInterface<IPF2CharacterCommandInterface> Command) override;

	UFUNCTION(BlueprintCallable)
	virtual void PeekNext(TScriptInterface<IPF2CharacterCommandInterface>& NextCommand) override;

	UFUNCTION(BlueprintCallable)
	virtual void PopNext(TScriptInterface<IPF2CharacterCommandInterface>& NextCommand) override;

	UFUNCTION(BlueprintCallable)
	virtual void DropNext() override;

	UFUNCTION(BlueprintCallable)
	virtual EPF2CommandExecuteImmediatelyResult PopAndExecuteNext() override;

	UFUNCTION(BlueprintCallable)
	virtual bool Remove(TScriptInterface<IPF2CharacterCommandInterface> Command) override;

	UFUNCTION(BlueprintCallable)
	virtual int Count() override;

	UFUNCTION(BlueprintCallable)
	virtual void Clear() override;

	// =================================================================================================================
	// Public Methods - IPF2LogIdentifiableInterface Implementation
	// =================================================================================================================
	UFUNCTION(BlueprintCallable)
	virtual FString GetIdForLogs() const override;

protected:
	// =================================================================================================================
	// Protected Replication Callbacks
	// =================================================================================================================
	/**
	 * Replication callback for the "Queue" property.
	 *
	 * This notifies all event listeners that the contents of the queue has changed, as well as separately notifying
	 * listeners about each command that was added or removed.
	 */
	UFUNCTION()
	virtual void OnRep_Queue(const TArray<AInfo*>& OldQueue);

	// =================================================================================================================
	// Protected Event Notifications
	// =================================================================================================================
	/**
	 * Callback invoked when commands in this queue have changed (commands added, commands removed, or queue cleared).
	 */
	void Native_OnCommandsChanged() const;

	/**
	 * Callback invoked when a command has been added to this queue.
	 *
	 * @param CommandAdded
	 *	The command that was added.
	 */
	void Native_OnCommandAdded(const TScriptInterface<IPF2CharacterCommandInterface>& CommandAdded) const;

	/**
	 * Callback invoked when a command has been removed from this queue.
	 *
	 * @param CommandRemoved
	 *	The command that was removed.
	 */
	void Native_OnCommandRemoved(const TScriptInterface<IPF2CharacterCommandInterface>& CommandRemoved) const;
};

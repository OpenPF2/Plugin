﻿// OpenPF2 for UE Game Logic, Copyright 2022, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#pragma once

#include <Components/ActorComponent.h>

#include "PF2CharacterQueueInterface.h"

#include "PF2CharacterQueueComponent.generated.h"

// =====================================================================================================================
// Forward Declarations (to minimize header dependencies)
// =====================================================================================================================
class IPF2CharacterInterface;
class IPF2PlayerControllerInterface;

// =====================================================================================================================
// Delegate Declarations
// =====================================================================================================================
/**
 * Delegate for Blueprints to react to characters being added or removed from the queue.
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(
	FPF2CharacterAddedOrRemovedDelegate,
	const TScriptInterface<IPF2CharacterInterface>&, Character
);

/**
 * Delegate for Blueprints to react to the queue changing in any way (characters added or removed, or queue cleared).
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(
	FPF2CharacterQueueChangedDelegate,
	const TArray<TScriptInterface<IPF2CharacterInterface>>&, Characters
);

/**
 * Delegate for Blueprints to react to a change in active character.
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(
	FPF2ActiveCharacterChangedDelegate,
	const TScriptInterface<IPF2CharacterInterface>&, OldCharacter,
	const TScriptInterface<IPF2CharacterInterface>&, NewCharacter
);

// =====================================================================================================================
// Normal Declarations
// =====================================================================================================================
/**
 * A component for managing a ring buffer of characters.
 *
 * This is typically used by player controllers to manage what characters the player can control, and to advance through
 * them, similar to how BioWare games like Dragon Age allow you to assume control of different party members.
 */
UCLASS(ClassGroup="OpenPF2-PlayerControllers", meta=(BlueprintSpawnableComponent))
class OPENPF2CORE_API UPF2CharacterQueueComponent final :
	public UActorComponent,
	public IPF2CharacterQueueInterface
{
	GENERATED_BODY()

protected:
	// =================================================================================================================
	// Protected Fields
	// =================================================================================================================
	/**
	 * The character(s) in this queue.
	 *
	 * This is an array of actors (instead of interfaces) for replication. UE will not replicate actors if they are
	 * declared/referenced through an interface property.
	 */
	UPROPERTY(ReplicatedUsing=OnRep_CharacterQueue)
	TArray<AActor*> Queue;

	/**
	 * The index of the character that is currently active/selected in this queue.
	 *
	 * This is often referred to as the "cursor" for this queue.
	 */
	UPROPERTY(ReplicatedUsing=OnRep_ActiveCharacterIndex)
	uint8 ActiveCharacterIndex;

	/**
	 * A locally cached copy of which character is currently active.
	 *
	 * This is NOT replicated; instead, it is derived from the value of ActiveCharacterIndex, which is replicated, and
	 * gets updated by UpdateActiveCharacter().
	 *
	 * @see UpdateActiveCharacter()
	 */
	UPROPERTY()
	TScriptInterface<IPF2CharacterInterface> ActiveCharacter;

public:
	// =================================================================================================================
	// Public Fields - Multicast Delegates
	// =================================================================================================================
	/**
	 * Event fired when the characters in the queue have changed (characters added, commands removed, or queue cleared).
	 *
	 * If replication is enabled for this component, this is invoked on both the owning client and the server.
	 */
	UPROPERTY(BlueprintAssignable)
	FPF2CharacterQueueChangedDelegate OnCharactersChanged;

	/**
	 * Event fired when a character is added to the queue.
	 *
	 * If replication is enabled for this component, this is invoked on both the owning client and the server.
	 */
	UPROPERTY(BlueprintAssignable)
	FPF2CharacterAddedOrRemovedDelegate OnCharacterAdded;

	/**
	 * Event fired when a character is removed from the queue.
	 *
	 * If replication is enabled for this component, this is invoked on both the owning client and the server.
	 */
	UPROPERTY(BlueprintAssignable)
	FPF2CharacterAddedOrRemovedDelegate OnCharacterRemoved;

	/**
	 * Event fired when a change in active character occurs.
	 *
	 * If replication is enabled for this component, this is invoked on both the owning client and the server.
	 */
	UPROPERTY(BlueprintAssignable)
	FPF2ActiveCharacterChangedDelegate OnActiveCharacterChanged;

	// =================================================================================================================
	// Public Constructors
	// =================================================================================================================
	/**
	 * Default constructor for UPF2CharacterQueueComponent.
	 */
	explicit UPF2CharacterQueueComponent();

	// =================================================================================================================
	// Public Methods - UActorComponent Overrides
	// =================================================================================================================
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	// =================================================================================================================
	// Public Methods - IPF2CharacterQueueInterface Implementation
	// =================================================================================================================
	UFUNCTION(BlueprintCallable)
	virtual TScriptInterface<IPF2CharacterInterface> GetActiveCharacter() const override;

	UFUNCTION(BlueprintCallable)
	virtual void Add(TScriptInterface<IPF2CharacterInterface> Character) override;

	UFUNCTION(BlueprintCallable)
	virtual bool Remove(TScriptInterface<IPF2CharacterInterface> Character) override;

	UFUNCTION(BlueprintCallable)
	virtual int Count() const override;

	UFUNCTION(BlueprintCallable)
	virtual void Clear() override;

	UFUNCTION(BlueprintCallable)
	virtual TScriptInterface<IPF2CharacterInterface> PreviousCharacter() override;

	UFUNCTION(BlueprintCallable)
	virtual TScriptInterface<IPF2CharacterInterface> NextCharacter() override;

	UFUNCTION(BlueprintCallable)
	virtual TArray<TScriptInterface<IPF2CharacterInterface>> ToArray() const override;

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

protected:
	// =================================================================================================================
	// Protected Methods
	// =================================================================================================================
	/**
	 * Gets the highest zero-based index available within the character queue.
	 *
	 * In the special case in which the queue is empty, this returns "0" even though it is not a valid index, as this
	 * will be the index of the first character added to the queue once the character has been added.
	 *
	 * @return
	 *	- If the queue is not empty: The highest valid, zero-based index available in the character queue (for example,
	 *	  if there are 10 items in the queue, this will return a value of "9").
	 *	- If the queue is empty: a value of "0".
	 */
	FORCEINLINE uint8 GetMaxIndex() const
	{
		return FMath::Max(this->Count() - 1, 0);
	}

	/**
	 * Sets the active character index to the specified value, notifying listeners in the process.
	 *
	 * @param NewActiveCharacterIndex
	 *   The new value for the active character index.
	 */
	void SetActiveCharacterIndex(const uint8 NewActiveCharacterIndex);

	/**
	 * Updates the locally cached active character reference.
	 *
	 * If this actually results in a change to the reference, event listeners are notified.
	 */
	void UpdateActiveCharacter();

	// =================================================================================================================
	// Protected Replication Callbacks
	// =================================================================================================================
	/**
	 * Notifies this component that the list of character(s) in the queue has been replicated.
	 *
	 * @param OldCharacters
	 *	The previous array of characters in the queue.
	 */
	UFUNCTION()
	void OnRep_CharacterQueue(const TArray<AActor*> OldCharacters);

	/**
	 * Notifies this component that which character is active has been replicated.
	 */
	UFUNCTION()
	void OnRep_ActiveCharacterIndex();

	// =================================================================================================================
	// Protected Native Event Callbacks
	// =================================================================================================================
	/**
	 * Callback invoked when characters in this queue have changed (characters added or removed, or queue cleared).
	 *
	 * If replication is enabled for this component, this is invoked on both the owning client and the server.
	 */
	void Native_OnCharactersChanged();

	/**
	 * Callback invoked when a character has been added to the queue.
	 *
	 * If replication is enabled for this component, this is invoked on both the owning client and the server.
	 *
	 * @param AddedCharacter
	 *	The character that is now in the queue.
	 */
	void Native_OnCharacterAdded(const TScriptInterface<IPF2CharacterInterface>& AddedCharacter);

	/**
	 * Callback invoked when a character has been removed from the queue.
	 *
	 * If replication is enabled for this component, this is invoked on both the owning client and the server.
	 *
	 * @param RemovedCharacter
	 *	The character that is no longer in the queue.
	 * @param RemovedIndex
	 *	The index of the character that was removed.
	 */
	void Native_OnCharacterRemoved(const TScriptInterface<IPF2CharacterInterface>& RemovedCharacter,
	                               const uint8                                     RemovedIndex);

	/**
	 * Callback invoked when there is a change to which character in the queue is active.
	 *
	 * If replication is enabled for this component, this is invoked on both the owning client and the server.
	 *
	 * @param OldCharacter
	 *	The character that was previously active in the queue, if any.
	 * @param NewCharacter
	 *	The character that is now active in the queue.
	 */
	void Native_OnActiveCharacterChanged(const TScriptInterface<IPF2CharacterInterface>& OldCharacter,
	                                     const TScriptInterface<IPF2CharacterInterface>& NewCharacter);
};
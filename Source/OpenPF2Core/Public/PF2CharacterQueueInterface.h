// OpenPF2 for UE Game Logic, Copyright 2022-2023, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#pragma once

#include "PF2ActorComponentInterface.h"

#include "PF2CharacterQueueInterface.generated.h"

// =====================================================================================================================
// Forward Declarations (to minimize header dependencies)
// =====================================================================================================================
class IPF2CharacterInterface;

// =====================================================================================================================
// Normal Declarations - Delegates
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
	FPF2ControlledCharacterChangedDelegate,
	const TScriptInterface<IPF2CharacterInterface>&, OldCharacter,
	const TScriptInterface<IPF2CharacterInterface>&, NewCharacter
);

// =====================================================================================================================
// Normal Declarations - Types
// =====================================================================================================================
UCLASS()
class OPENPF2CORE_API UPF2CharacterQueueInterfaceEvents : public UObject
{
	GENERATED_BODY()

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
	FPF2ControlledCharacterChangedDelegate OnControlledCharacterChanged;
};

/**
 * An interface for objects that maintain queues of characters in a ring buffer/circular buffer.
 */
UINTERFACE(MinimalAPI, BlueprintType, meta=(CannotImplementInterfaceInBlueprint))
class UPF2CharacterQueueInterface : public UPF2ActorComponentInterface
{
	GENERATED_BODY()
};

class OPENPF2CORE_API IPF2CharacterQueueInterface : public IPF2ActorComponentInterface
{
	GENERATED_BODY()

public:
	/**
	 * Gets the events object used for binding Blueprint callbacks to events from this component.
	 *
	 * @return
	 *	The events object for this interface.
	 */
	UFUNCTION(BlueprintCallable, Category="OpenPF2|Components|Player Controllers|Character Queues")
	virtual UPF2CharacterQueueInterfaceEvents* GetEvents() const = 0;

	/**
	 * Gets the character that the cursor is currently pointing at.
	 *
	 * The active character starts out as the first character in the queue. It is advanced by the NextCharacter()
	 * method and rewound by the PreviousCharacter() command.
	 *
	 * @return
	 *	The active character, as follows:
	 *		- If the queue is empty: a reference to nullptr is returned.
	 *		- If the queue is not empty: a valid character reference.
	 */
	UFUNCTION(BlueprintCallable, Category="OpenPF2|Components|Player Controllers|Character Queues")
	virtual TScriptInterface<IPF2CharacterInterface> GetControlledCharacter() const = 0;

	/**
	 * Adds a character to the end of the queue.
	 *
	 * If this is the first character added to the queue, it will become the active character automatically.
	 *
	 * @param Character
	 *	The character to add to the queue.
	 */
	UFUNCTION(BlueprintCallable, Category="OpenPF2|Components|Player Controllers|Character Queues")
	virtual void Add(TScriptInterface<IPF2CharacterInterface> Character) = 0;

	/**
	 * Removes a character from the queue.
	 *
	 * If the character is not in the queue, nothing happens (this method is idempotent).
	 *
	 * @param Character
	 *	The character to remove, if it exists in the queue.
	 *
	 * @return
	 *	- true if the character was removed from the queue.
	 *	- false if the character was not in the queue.
	 */
	UFUNCTION(BlueprintCallable, Category="OpenPF2|Components|Player Controllers|Character Queues")
	virtual bool Remove(TScriptInterface<IPF2CharacterInterface> Character) = 0;

	/**
	 * Gets the count of how many characters are in the queue.
	 *
	 * @return
	 *	How many items are in the queue.
	 */
	UFUNCTION(BlueprintCallable, Category="OpenPF2|Components|Player Controllers|Character Queues")
	virtual int Count() const = 0;

	/**
	 * Removes all characters from the queue.
	 */
	UFUNCTION(BlueprintCallable, Category="OpenPF2|Components|Player Controllers|Character Queues")
	virtual void Clear() = 0;

	/**
	 * Rewinds the active character cursor to the previous character in the queue, and then returns that character.
	 *
	 * If the active character is the first character in the queue, the active character becomes the last character in
	 * the queue.
	 *
	 * @return
	 *	The active character, as follows:
	 *		- If the queue is empty: a reference to nullptr is returned.
	 *		- If the queue contains only one item: the same character as was previously active.
	 *		- If the queue contains more than one item: the character that is now active.
	 */
	UFUNCTION(BlueprintCallable, Category="OpenPF2|Components|Player Controllers|Character Queues")
	virtual TScriptInterface<IPF2CharacterInterface> PreviousCharacter() = 0;

	/**
	 * Advances the active character cursor to the next character in the queue, and then returns that character.
	 *
	 * If the active character is the last character in the queue, the active character becomes the first character in
	 * the queue.
	 *
	 * @return
	 *	The active character, as follows:
	 *		- If the queue is empty: a reference to nullptr is returned.
	 *		- If the queue contains only one item: the same character as was previously active.
	 *		- If the queue contains more than one item: the character that is now active.
	 */
	UFUNCTION(BlueprintCallable, Category="OpenPF2|Components|Player Controllers|Character Queues")
	virtual TScriptInterface<IPF2CharacterInterface> NextCharacter() = 0;

	/**
	 * Converts the contents of this queue into an array of characters.
	 *
	 * Changes to the resulting array have no effect on the contents of this queue.
	 *
	 * @return
	 *	The array of characters contained in this queue, in the order they appear in the queue.
	 */
	UFUNCTION(BlueprintCallable, Category="OpenPF2|Components|Player Controllers|Character Queues")
	virtual TArray<TScriptInterface<IPF2CharacterInterface>> ToArray() const = 0;
};

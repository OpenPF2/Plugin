// OpenPF2 for UE Game Logic, Copyright 2022, Guy Elsmore-Paddock. All Rights Reserved.
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
// Normal Declarations
// =====================================================================================================================
UINTERFACE(MinimalAPI, BlueprintType, meta=(CannotImplementInterfaceInBlueprint))
class UPF2CharacterQueueInterface : public UPF2ActorComponentInterface
{
	GENERATED_BODY()
};

// =====================================================================================================================
// Normal Declarations
// =====================================================================================================================
/**
 * An interface for objects that maintain queues of characters in a ring buffer/circular buffer.
 */
class OPENPF2CORE_API IPF2CharacterQueueInterface : public IPF2ActorComponentInterface
{
	GENERATED_BODY()

public:
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
	virtual TScriptInterface<IPF2CharacterInterface> GetActiveCharacter() const = 0;

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

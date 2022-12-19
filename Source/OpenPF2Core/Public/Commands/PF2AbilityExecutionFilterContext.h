// OpenPF2 for UE Game Logic, Copyright 2022, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#pragma once

#include "PF2CharacterInterface.h"
#include "PF2AbilityExecutionFilterContext.generated.h"

// =====================================================================================================================
// Forward Declarations (to minimize header dependencies)
// =====================================================================================================================
class IPF2CharacterCommandInterface;

// =====================================================================================================================
// Normal Declarations
// =====================================================================================================================
/**
 * Context used by an ability execution filter to control which ability gets executed (if any).
 *
 * This acts as both the information passed in to an ability filter as well as the result of that filter. A filter can
 * exercise control over the ability being executed by manipulating this context, as follows:
 * 1. The filter can proceed to activate the ability by leaving the ability pointer untouched and leaving the "proceed"
 *    flag set to "true" (the default).
 * 2. The filter can activate an alternate ability rather than the ability that would have normally been invoked by
 *    changing the ability spec handle to the handle of the desired ability.
 * 3. The filter can drop execution of the ability (and all remaining filters) by setting the "proceed" flag to "false".
 *
 * If there are multiple filters in the chain, they will continue to be invoked as long as "proceed" is "true". If a
 * filter sets "proceed" to "false", it is the last filter executed.
 */
USTRUCT(BlueprintType)
struct FPF2AbilityExecutionFilterContext
{
	GENERATED_BODY()

	// =================================================================================================================
	// Public Fields
	// =================================================================================================================
	/**
	 * Whether any ability should be executed after all filters have been invoked.
	 */
	UPROPERTY(BlueprintReadWrite)
	bool bProceed;

	/**
	 * The ability that should be executed after all filters have been invoked.
	 */
	UPROPERTY(BlueprintReadWrite)
	FGameplayAbilitySpecHandle AbilityToExecute;

	/**
	 * The payload to provide when invoking the ability.
	 *
	 * Not all abilities use the payload; this is only useful for those that do.
	 */
	UPROPERTY(BlueprintReadWrite)
	FGameplayEventData AbilityPayload;

protected:
	// =================================================================================================================
	// Protected Fields
	// =================================================================================================================
	/**
	 * The name of the input action that was invoked, if the ability was invoked by input from the player.
	 */
	UPROPERTY(BlueprintReadOnly)
	FName TriggeredInputActionName;

	/**
	 * The character on which the ability will be executed.
	 */
	UPROPERTY(BlueprintReadOnly)
	TScriptInterface<IPF2CharacterInterface> Character;

public:
	// =================================================================================================================
	// Public Constructors
	// =================================================================================================================
	/**
	 * Constructs a new instance.
	 */
	explicit FPF2AbilityExecutionFilterContext() :
		bProceed(true),
		TriggeredInputActionName(FName()),
		Character(TScriptInterface<IPF2CharacterInterface>(nullptr))
	{
	}

	/**
	 * Constructs a new instance.
	 *
	 * Commands are typically invoked by input from a player. If the ability being activated was triggered by input, the
	 * TriggeredInputActionName should be equal to the name of the input; otherwise, this should be equal to an empty
	 * FName.
	 *
	 * @param Character
	 *	The character on which the ability will be invoked.
	 * @param AbilityToExecute
	 *	The ability that is expected to be executed unless a filter changes it.
	 */
	explicit FPF2AbilityExecutionFilterContext(
			const TScriptInterface<IPF2CharacterInterface> Character,
			const FGameplayAbilitySpecHandle               AbilityToExecute) :
		bProceed(true),
		AbilityToExecute(AbilityToExecute),
		TriggeredInputActionName(FName()),
		Character(Character)
	{
	}

	/**
	 * Constructs a new instance.
	 *
	 * This constructor is used for abilities invoked by input from a player. The TriggeredInputActionName should be
	 * equal to the name of the input that triggered the ability.
	 *
	 * @param TriggeredInputActionName
	 *	The name of the input that was invoked by the player.
	 * @param Character
	 *	The character on which the ability will be invoked.
	 * @param AbilityToExecute
	 *	The ability that is expected to be executed unless a filter changes it.
	 */
	explicit FPF2AbilityExecutionFilterContext(
			const FName                                    TriggeredInputActionName,
			const TScriptInterface<IPF2CharacterInterface> Character,
			const FGameplayAbilitySpecHandle               AbilityToExecute) :
		bProceed(true),
		AbilityToExecute(AbilityToExecute),
		TriggeredInputActionName(TriggeredInputActionName),
		Character(Character)
	{
	}

	/**
	 * Constructs a new instance.
	 *
	 * This constructor is used for abilities, invoked by input from a player, that accept a payload. The
	 * TriggeredInputActionName should be equal to the name of the input that triggered the ability.
	 *
	 * @param TriggeredInputActionName
	 *	The name of the input that was invoked, if the command was invoked by input from the player.
	 * @param Character
	 *	The character on which the ability will be invoked.
	 * @param AbilityToExecute
	 *	The ability that is expected to be executed unless a filter changes it.
	 * @param AbilityPayload
	 *	The payload to provide when invoking the ability.
	 */
	explicit FPF2AbilityExecutionFilterContext(
			const FName                                    TriggeredInputActionName,
			const TScriptInterface<IPF2CharacterInterface> Character,
			const FGameplayAbilitySpecHandle               AbilityToExecute,
			const FGameplayEventData                       AbilityPayload) :
		bProceed(true),
		AbilityToExecute(AbilityToExecute),
		AbilityPayload(AbilityPayload),
		TriggeredInputActionName(TriggeredInputActionName),
		Character(Character)
	{
	}

	// =================================================================================================================
	// Public Methods
	// =================================================================================================================
	/**
	 * Gets whether additional filters should be evaluated and the ability should be activated.
	 *
	 * @return
	 *	- true if execution should proceed.
	 *	- false if no further filters should be evaluated and the ability activation should be canceled.
	 */
	FORCEINLINE bool ShouldProceed() const
	{
		return this->bProceed;
	}

	/**
	 * Gets the ability that should be executed after all filters have fired.
	 *
	 * @return
	 *	The ability to execute, if proceeding.
	 */
	FORCEINLINE FGameplayAbilitySpecHandle GetAbilityToExecute() const
	{
		return this->AbilityToExecute;
	}

	/**
	 * Gets the payload to provide when invoking the ability.
	 *
	 * Not all abilities use the payload; this is only useful for those that do.
	 *
	 * @return
	 *	The ability payload.
	 */
	FORCEINLINE FGameplayEventData GetAbilityPayload() const
	{
		return this->AbilityPayload;
	}

	/**
	 * Gets the name of the input action (if any) that triggered invocation of the ability.
	 *
	 * @return
	 *	The name of the input action that the player invoked.
	 */
	FORCEINLINE FName GetTriggeredInputActionName() const
	{
		return this->TriggeredInputActionName;
	}

	/**
	 * Gets the character on which the ability should be activated.
	 *
	 * @return
	 *	The target character for the ability.
	 */
	FORCEINLINE TScriptInterface<IPF2CharacterInterface> GetCharacter() const
	{
		return this->Character;
	}

	/**
	 * Gets a reference to the world that contains the character who is activating the ability.
	 *
	 * @return
	 *	The world containing the character on which the ability is being activated.
	 */
	FORCEINLINE UWorld* GetWorld() const
	{
		if (this->Character == nullptr)
		{
			return nullptr;
		}
		else
		{
			return this->Character->ToActor()->GetWorld();
		}
	}
};

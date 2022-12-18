// OpenPF2 for UE Game Logic, Copyright 2022, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#pragma once

#include <GameplayAbilitySpec.h>

#include "PF2ActorComponentInterface.h"

#include "PF2CommandBindingsInterface.generated.h"

// =====================================================================================================================
// Forward Declarations (to minimize header dependencies)
// =====================================================================================================================
class UInputComponent;
class IPF2CharacterInterface;

// =====================================================================================================================
// Normal Declarations
// =====================================================================================================================
UINTERFACE(MinimalAPI, BlueprintType, meta=(CannotImplementInterfaceInBlueprint))
class UPF2CommandBindingsInterface : public UPF2ActorComponentInterface
{
	GENERATED_BODY()
};

/**
 * An interface for components that maintain Gameplay Ability input action bindings for characters.
 */
class OPENPF2CORE_API IPF2CommandBindingsInterface : public IPF2ActorComponentInterface
{
	GENERATED_BODY()

public:
	/**
	 * Clears all bindings.
	 *
	 * If input is currently wired up, bindings are removed from input before being cleared.
	 */
	UFUNCTION(BlueprintCallable, Category="OpenPF2|Components|Characters|Command Bindings")
	virtual void ClearBindings() = 0;

	/**
	 * Populates the bindings array from the abilities that have been granted to the owning character.
	 *
	 * To prevent duplicate bindings, this can only be called when no bindings have yet been defined or all have been
	 * cleared.
	 *
	 * If input is currently wired up, the new bindings are automatically added to input.
	 */
	UFUNCTION(BlueprintCallable, Category="OpenPF2|Components|Characters|Command Bindings")
	virtual void LoadAbilitiesFromCharacter() = 0;

	/**
	 * Wires-up all bindings to receive input from the given player input component.
	 *
	 * Only new bindings that have an action assigned and have not yet been wired up will be affected; any binding that
	 * was previously wired up will be ignored.
	 *
	 * @param InputComponent
	 *	The component to which input should be bound.
	 */
	UFUNCTION(BlueprintCallable, Category="OpenPF2|Components|Characters|Command Bindings")
	virtual void ConnectToInput(UInputComponent* InputComponent) = 0;

	/**
	 * Removes the association between actions and the input component, allowing all bindings to be re-assigned.
	 *
	 * This must be called before changing the action of any binding.
	 *
	 * Only bindings that have been wired up will be affected; any new binding that is not yet wired up will be ignored.
	 */
	UFUNCTION(BlueprintCallable, Category="OpenPF2|Components|Characters|Command Bindings")
	virtual void DisconnectFromInput() = 0;

	/**
	 * Executes the specified ability on the owning character in response to the specified action.
	 *
	 * This is expected to be invoked only by a command binding.
	 *
	 * @param ActionName
	 *	The name of the input action that invoked this binding.
	 * @param AbilitySpecHandle
	 *	The handle for the ability to activate.
	 */
	virtual void ExecuteBoundAbility(const FName ActionName, const FGameplayAbilitySpecHandle AbilitySpecHandle) = 0;
};

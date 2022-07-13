// OpenPF2 for UE Game Logic, Copyright 2022, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#pragma once

#include "Utilities/PF2LogIdentifiableInterface.h"

#include "PF2CommandBindingsInterface.generated.h"

// =====================================================================================================================
// Forward Declarations (to break recursive dependencies)
// =====================================================================================================================
class UInputComponent;
class IPF2CharacterInterface;

// =====================================================================================================================
// Normal Declarations
// =====================================================================================================================
UINTERFACE(MinimalAPI, BlueprintType, meta=(CannotImplementInterfaceInBlueprint))
class UPF2CommandBindingsInterface : public UPF2LogIdentifiableInterface
{
	GENERATED_BODY()
};

/**
 * An interface for components that maintain Gameplay Ability input action bindings for characters.
 */
class OPENPF2CORE_API IPF2CommandBindingsInterface : public IPF2LogIdentifiableInterface
{
	GENERATED_BODY()

public:
	/**
	 * Populates the bindings array from the abilities that have been granted to a character.
	 *
	 * @param Character
	 *	The character from which to load granted abilities.
	 */
	UFUNCTION(BlueprintCallable, Category="OpenPF2|Command Bindings")
	virtual void LoadAbilitiesFromCharacter(const TScriptInterface<IPF2CharacterInterface> Character) = 0;

	/**
	 * Populates the bindings array from the abilities that have been granted to a character.
	 *
	 * @param Character
	 *	The character from which to load granted abilities.
	 */
	virtual void LoadAbilitiesFromCharacter(IPF2CharacterInterface* Character) = 0;

	/**
	 * Wires-up all bindings to receive input from the given player input component.
	 *
	 * Only new bindings that have an action assigned and have not yet been wired up will be affected; any binding that
	 * was previously wired up will be ignored.
	 *
	 * @param InputComponent
	 *	The component to which input should be bound.
	 */
	UFUNCTION(BlueprintCallable, Category="OpenPF2|Command Bindings")
	virtual void ConnectToInput(UInputComponent* InputComponent) = 0;

	/**
	 * Removes the association between actions and the given input component, allowing all bindings to be re-assigned.
	 *
	 * This must be called before changing the action of any binding.
	 *
	 * Only bindings that have been wired up will be affected; any new binding that is not yet wired up will be ignored.
	 */
	UFUNCTION(BlueprintCallable, Category="OpenPF2|Command Bindings")
	virtual void DisconnectFromInput(UInputComponent* InputComponent) = 0;
};

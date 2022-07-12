// OpenPF2 for UE Game Logic, Copyright 2022, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#pragma once

#include <Components/ActorComponent.h>

#include "PF2CommandInputBinding.h"

#include "PF2CommandBindingsComponent.generated.h"

/**
 * A component for characters that need to support binding execution of Gameplay Abilities to input actions.
 *
 * Unlike the native input binding support offered by the GAS, this version does not bind input directly to a specific
 * pawn/character. Instead, it allows input to be routed to whichever character the player is currently controlling, and
 * it works automatically with abilities that need to be queued during encounters.
 */
UCLASS(ClassGroup="OpenPF2", meta=(BlueprintSpawnableComponent))
class OPENPF2CORE_API UPF2CommandBindingsComponent : public UActorComponent
{
	GENERATED_BODY()

	/**
	 * The association between inputs and Gameplay Abilities.
	 */
	UPROPERTY(EditDefaultsOnly)
	TArray<FPF2CommandInputBinding> Bindings;

public:
	/**
	 * Grants the given character all of the abilities for which there are bindings.
	 *
	 * This can only be run on the server. Only abilities that have not yet been granted to any character are granted.
	 * Abilities already granted (e.g., abilities that were loaded from the character) are skipped.
	 *
	 * @param Character
	 *	The character to whom abilities should be granted.
	 */
	UFUNCTION(BlueprintCallable)
	void GiveAbilitiesToCharacter(TScriptInterface<IPF2CharacterInterface> Character);

	/**
	 * Grants the given character all of the abilities for which there are bindings.
	 *
	 * This can only be run on the server. Only abilities that have not yet been granted to any character are granted.
	 * Abilities already granted (e.g., abilities that were loaded from the character) are skipped.
	 *
	 * @param Character
	 *	The character to whom abilities should be granted.
	 */
	void GiveAbilitiesToCharacter(IPF2CharacterInterface* Character);

	/**
	 * Populates the bindings array from the abilities that have been granted to a character.
	 *
	 * @param Character
	 *	The character from which to load granted abilities.
	 */
	void LoadAbilitiesFromCharacter(IPF2CharacterInterface* Character);

	/**
	 * Wires-up all bindings to receive input from the given player input component.
	 *
	 * @param InputComponent
	 *	The component to which input should be bound.
	 */
	UFUNCTION(BlueprintCallable)
	void BindToInputComponent(UInputComponent* InputComponent);

protected:
	/**
	 * Notifies the specified binding that the input action it corresponds to has been activated.
	 *
	 * @param Binding
	 *	The binding to notify of a button activation.
	 */
	void LocalInputPressed(FPF2CommandInputBinding Binding);

	/**
	* Notifies the specified that the input action it corresponds to has been released.
	 *
	 * @param Binding
	 *	The binding to notify of a button release.
	 */
	void LocalInputReleased(FPF2CommandInputBinding Binding);
};

// OpenPF2 for UE Game Logic, Copyright 2022, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#pragma once

#include <Components/ActorComponent.h>

#include "PF2CommandBindingsInterface.h"
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
class OPENPF2CORE_API UPF2CommandBindingsComponent : public UActorComponent, public IPF2CommandBindingsInterface
{
	GENERATED_BODY()

	/**
	 * The association between inputs and Gameplay Abilities.
	 */
	TArray<FPF2CommandInputBinding> Bindings;

public:
	// =================================================================================================================
	// Public Methods - IPF2CommandBindingsInterface Implementation
	// =================================================================================================================
	UFUNCTION(BlueprintCallable)
	virtual void LoadAbilitiesFromCharacter(const TScriptInterface<IPF2CharacterInterface> Character) override;

	virtual void LoadAbilitiesFromCharacter(IPF2CharacterInterface* Character) override;

	UFUNCTION(BlueprintCallable)
	virtual void ConnectToInput(UInputComponent* InputComponent) override;

	UFUNCTION(BlueprintCallable)
	virtual void DisconnectFromInput(UInputComponent* InputComponent) override;

	// =================================================================================================================
	// Public Methods - IPF2LogIdentifiableInterface Implementation
	// =================================================================================================================
	UFUNCTION(BlueprintCallable)
	virtual FString GetIdForLogs() const override;
};

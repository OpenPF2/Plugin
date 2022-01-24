// OpenPF2 for UE Game Logic, Copyright 2021, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#pragma once

#include "PF2ModeOfPlayRuleSetInterface.h"
#include "PF2PlayerControllerInterface.h"

#include "Abilities/PF2ActionQueueResult.h"

#include "PF2ModeOfPlayRuleSetBase.generated.h"

/**
 * Default base class for PF2 Mode of Play Rule Sets (MoPRS).
 *
 * @see IPF2GameModeInterface
 */
UCLASS(Abstract, Blueprintable)
// ReSharper disable once CppClassCanBeFinal
class OPENPF2CORE_API UPF2ModeOfPlayRuleSetBase : public UObject, public IPF2ModeOfPlayRuleSetInterface
{
	GENERATED_BODY()

public:
	// =================================================================================================================
	// Public Methods - UPF2ModeOfPlayRuleSetBase Implementation
	// =================================================================================================================
	virtual FPF2QueuedActionHandle OnQueueAction_Implementation(
		const TScriptInterface<IPF2CharacterInterface>&    Character,
		const TScriptInterface<IPF2QueuedActionInterface>& Action,
		OUT EPF2ActionQueueResult&                         OutQueueResult) override;

	virtual void OnCancelQueuedAction_Implementation(
		const TScriptInterface<IPF2CharacterInterface>&    Character,
		const TScriptInterface<IPF2QueuedActionInterface>& Action) override;

protected:
	// =================================================================================================================
	// Protected Methods
	// =================================================================================================================
	/**
	 * Gets controllers for all the characters in the world.
	 *
	 * @return
	 *	PF2-specific controllers for all players in the world.
	 */
	UFUNCTION(BlueprintCallable, Category="OpenPF2|Mode of Play Rule Sets|Characters")
	TArray<TScriptInterface<IPF2PlayerControllerInterface>> GetPlayerControllers() const;

	/**
	 * Gets all of the player-controlled PF2 characters in the world.
	 *
	 * @return
	 *	PF2-specific controllers for all players in the world.
	 */
	UFUNCTION(BlueprintCallable, Category="OpenPF2|Mode of Play Rule Sets|Characters")
	TArray<TScriptInterface<IPF2CharacterInterface>> GetPlayerControlledCharacters() const;
};

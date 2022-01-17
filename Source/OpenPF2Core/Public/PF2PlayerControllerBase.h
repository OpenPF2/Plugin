// OpenPF2 for UE Game Logic, Copyright 2021, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#pragma once

#include <GameFramework/PlayerController.h>

#include "PF2PlayerControllerInterface.h"
#include "PF2QueuedActionHandle.h"
#include "PF2PlayerControllerBase.generated.h"

/**
 * Default base class for PF2 Player Controllers.
 *
 * @see IPF2PlayerControllerInterface
 */
UCLASS(Abstract)
// ReSharper disable once CppClassCanBeFinal
class OPENPF2CORE_API APF2PlayerControllerBase : public APlayerController, public IPF2PlayerControllerInterface
{
	GENERATED_BODY()

public:
	// =================================================================================================================
	// Public Methods - IPF2PlayerControllerInterface Implementation
	// =================================================================================================================
	UFUNCTION(BlueprintCallable)
	virtual TScriptInterface<IPF2CharacterInterface> GetControlledCharacter() override;

	UFUNCTION(BlueprintCallable)
	virtual APlayerController* ToPlayerController() override;

	UFUNCTION()
	virtual void HandleModeOfPlayChanged(EPF2ModeOfPlayType NewMode) override;

	UFUNCTION(NetMulticast, Reliable)
	virtual void MulticastHandleActionQueued(const FPF2QueuedActionHandle ActionHandle) override;

	UFUNCTION(NetMulticast, Reliable)
	virtual void MulticastHandleActionDequeued(const FPF2QueuedActionHandle ActionHandle) override;

	UFUNCTION(BlueprintCallable, Server, Unreliable, DisplayName="Cancel Queued Action")
	virtual void ServerCancelQueuedAction(const FPF2QueuedActionHandle ActionHandle) override;

protected:
	// =================================================================================================================
	// Blueprint Event Callbacks
	// =================================================================================================================
	/**
	 * BP event invoked when the mode of play has changed.
	 *
	 * @param NewMode
	 *	The new mode of play.
	 */
	UFUNCTION(BlueprintImplementableEvent, Category="OpenPF2|Player Controllers")
	void OnModeOfPlayChanged(EPF2ModeOfPlayType NewMode);

	/**
	 * BP event invoked when an action/ability has been queued-up for the controlled character.
	 *
	 * @param ActionHandle
	 *	A reference to the ability that has been queued-up.
	 */
	UFUNCTION(BlueprintImplementableEvent, Category="OpenPF2|Player Controllers")
	void OnActionQueued(const FPF2QueuedActionHandle ActionHandle);

	/**
	 * BP event invoked when a previously queued action/ability for the controlled character has been cancelled.
	 *
	 * This happens if an action queued through the active Mode of Play Rule Set (MoPRS) was canceled by the player,
	 * by game rules, or something in the world.
	 *
	 * @param ActionHandle
	 *	A reference to the ability that has been canceled.
	 */
	UFUNCTION(BlueprintImplementableEvent, Category="OpenPF2|Player Controllers")
	void OnActionDequeued(const FPF2QueuedActionHandle ActionHandle);
};

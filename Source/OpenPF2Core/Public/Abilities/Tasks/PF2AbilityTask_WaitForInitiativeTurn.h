// OpenPF2 for UE Game Logic, Copyright 2021, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#pragma once

#include <Abilities/Tasks/AbilityTask.h>
#include <GameFramework/Character.h>

#include "PF2AbilityTaskBase.h"
#include "PF2GameStateInterface.h"
#include "PF2QueuedActionInterface.h"

#include "PF2AbilityTask_WaitForInitiativeTurn.generated.h"

/**
 * A task to delay execution of a Gameplay Ability until it is the character's turn according to initiative.
 *
 * Only GAs activated in encounter mode are subject to initiative. GAs activated while the game is in exploration or
 * downtime mode are executed immediately, without delay.
 */
UCLASS()
// ReSharper disable once CppClassCanBeFinal
class OPENPF2CORE_API UPF2AbilityTask_WaitForInitiativeTurn :
	public UPF2AbilityTaskBase,
	public IPF2QueuedActionInterface
{
	GENERATED_BODY()

public:
	// =================================================================================================================
	// Public Static Methods
	// =================================================================================================================
	/**
	 * Delay execution of this Gameplay Ability until the character's initiative turn comes up.
	 *
	 * This only affects the GA if it is activated in encounter mode. If this GA is activated while the game is in
	 * exploration or downtime mode, it is executed immediately, without delay.
	 *
	 * Execution pins work as follows:
	 *	- OnReadyToAct will fire when the character's "turn" in initiative order comes up.
	 *	- OnCancelled is called if the ability or task is cancelled, by either a player or the rule set (e.g., due to a
	 *	  change in mode of play).
	 *
	 * @param OwningAbility
	 *	A reference to the ability instance that is triggering this task. (This is automatically populated by Blueprint
	 *	from the ability Blueprint.)
	 * @param TaskInstanceName
	 *	A custom name for this task, in case it needs to be queried later while it is running.
	 * @param ActionName
	 *	The name to display for this action when queued, if the queue of actions are displayed to the player/user.
	 * @param ActionIcon
	 *	The icon to display for this action when queued, if the queue of actions are displayed to the player/user.
	 */
	UFUNCTION(
		BlueprintCallable,
		Category="Ability|Tasks",
		meta=(
			HidePin="OwningAbility",
			DefaultToSelf="OwningAbility",
			BlueprintInternalUseOnly="TRUE",
			DisplayName="Wait for Initiative Turn"
		)
	)
	static UPF2AbilityTask_WaitForInitiativeTurn* CreateWaitMovementModeChange(UGameplayAbility* OwningAbility,
	                                                                           const FName       TaskInstanceName,
	                                                                           const FText       ActionName,
	                                                                           const FSlateBrush ActionIcon);

protected:
	/**
	 * The name to display for this action when queued, if the queue of actions are displayed to the player/user.
	 */
	UPROPERTY()
	FText ActionName;

	/**
	 * The icon to display for this action when queued, if the queue of actions are displayed to the player/user.
	 */
	UPROPERTY()
	FSlateBrush ActionIcon;

	/**
	 * The character who is waiting on a turn to continue the GA that invoked this task.
	 */
	TWeakInterfacePtr<IPF2CharacterInterface> WaitingCharacter;

	/**
	 * The game state that is responsible for tracking character initiative order.
	 */
	TWeakInterfacePtr<IPF2GameStateInterface> GameState;

	// =================================================================================================================
	// Public Delegates/Execution Pins
	// =================================================================================================================
	/**
	 * Execution pin fired when the character's turn to act has come up according to initiative order.
	 */
	UPROPERTY(BlueprintAssignable)
	FGenericGameplayTaskDelegate OnReadyToAct;

	/**
	 * Execution pin fired if the action gets canceled by a player or the rule set (e.g., due to a change in mode of
	 * play).
	 */
	UPROPERTY(BlueprintAssignable)
	FGenericGameplayTaskDelegate OnCancelled;

	// =================================================================================================================
	// Public Methods - UAbilityTask Overrides
	// =================================================================================================================
	virtual void Activate() override;
	virtual void ExternalCancel() override;
	virtual void OnDestroy(bool AbilityEnded) override;

	// =================================================================================================================
	// Public Methods - IPF2QueuedActionInterface
	// =================================================================================================================
	virtual FText GetActionName() override;
	virtual FSlateBrush GetActionIcon() override;
	virtual void PerformQueuedAction() override;
	virtual void CancelQueuedAction() override;
};

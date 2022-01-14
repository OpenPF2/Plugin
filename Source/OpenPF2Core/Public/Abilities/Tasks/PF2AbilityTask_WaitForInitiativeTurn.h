// OpenPF2 for UE Game Logic, Copyright 2021, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#pragma once

#include <Abilities/Tasks/AbilityTask.h>
#include <GameFramework/Character.h>

#include "PF2AbilityTaskBase.h"
#include "PF2QueuedActionInterface.h"

#include "Abilities/PF2AbilityActivationOutcomeType.h"

#include "GameModes/PF2GameModeInterface.h"

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
	// =================================================================================================================
	// Protected Properties
	// =================================================================================================================
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
	 * The result of this ability task (e.g., whether it was executed or not, blocked, etc.).
	 */
	UPROPERTY(BlueprintReadOnly)
	EPF2AbilityActivationOutcomeType ActivationOutcome;

	// =================================================================================================================
	// Protected Fields
	// =================================================================================================================
	/**
	 * The character who is waiting on a turn to continue the GA that invoked this task.
	 */
	TWeakInterfacePtr<IPF2CharacterInterface> WaitingCharacter;

	/**
	 * The game mode that is responsible for managing character initiative order.
	 */
	TWeakInterfacePtr<IPF2GameModeInterface> GameMode;

	// =================================================================================================================
	// Delegates/Execution Pins
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

public:
	// =================================================================================================================
	// Public Constructors
	// =================================================================================================================
	/**
	 * Default constructor for UPF2AbilityTask_WaitForInitiativeTurn.
	 */
	explicit UPF2AbilityTask_WaitForInitiativeTurn() : ActivationOutcome(EPF2AbilityActivationOutcomeType::None)
	{
	}

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
	virtual EPF2AbilityActivationOutcomeType PerformAction() override;
	virtual void CancelAction() override;

protected:
	// =================================================================================================================
	// Protected Methods
	// =================================================================================================================
	/**
	 * Gets whether this ability task was executed after being queued.
	 *
	 * @return
	 *	- true if this ability task was executed after being queued.
	 *	- false if this ability task has not yet been queued and/or executed.
	 */
	FORCEINLINE bool WasActivated() const
	{
		return (this->ActivationOutcome != EPF2AbilityActivationOutcomeType::None);
	}

	/**
	 * Performs activation of this ability task when running on the client side.
	 *
	 * This consists of waiting until the character's turn comes up in initiative order.
	 */
	void Activate_Client();

	/**
	 * Performs activation of this ability task when running on the server side.
	 *
	 * This consists of registering a callback for the ability with the game mode, so that it can be invoked when the
	 * character's turn comes up according to initiative order. The server will also notify the client to proceed with
	 * local prediction of the ability by way of a generic signal.
	 *
	 * @param PF2Character
	 *	The character for which the ability task is being activated. The ability will not proceed until this character
	 *	is eligible to act.
	 */
	void Activate_Server(IPF2CharacterInterface* PF2Character);

	/**
	 * Callback invoked by the server on the client when the ability is ready to be performed.
	 *
	 * This method does not get called on the server side; it only runs on the client side.
	 */
	void OnServerActionCallback();
};

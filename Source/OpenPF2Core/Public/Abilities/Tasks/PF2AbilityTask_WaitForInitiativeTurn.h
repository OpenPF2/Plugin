// OpenPF2 for UE Game Logic, Copyright 2021, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#pragma once

#include <Abilities/Tasks/AbilityTask.h>
#include <GameFramework/Character.h>

#include "PF2AbilityTaskBase.h"
#include "PF2QueuedActionInterface.h"

#include "Abilities/PF2AbilityActivationResult.h"

#include "GameModes/PF2GameModeInterface.h"

#include "PF2AbilityTask_WaitForInitiativeTurn.generated.h"

/**
 * A task to delay execution of a Gameplay Ability until it is the character's turn according to initiative.
 *
 * Only GAs activated in encounter mode are subject to initiative. GAs activated while the game is in exploration or
 * downtime mode are typically executed immediately, without delay.
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
	 * The GA is only "resumed" after being queued if the ability is not otherwise blocked (e.g., but other abilities
	 * that are active on the character at the time that it is being resumed).
	 *
	 * Execution pins work as follows:
	 *	- OnQueued is called if the ability is queued, in case it needs to suspend itself while it is queued.
	 *	- OnReadyToAct is called when the character's "turn" in initiative order comes up. If the current Mode of Play
	 *	  Rule Set does not queue actions, this will fire immediately.
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
	static UPF2AbilityTask_WaitForInitiativeTurn* CreateWaitInitiativeTurn(
		UGameplayAbility*           OwningAbility,
		const FName                 TaskInstanceName,
		const FText                 ActionName,
		const FSlateBrush           ActionIcon);

	/**
	 * Delay execution of this Gameplay Ability until the character's initiative turn comes up and tags match.
	 *
	 * This only affects the GA if it is activated in encounter mode. If this GA is activated while the game is in
	 * exploration or downtime mode, it is executed immediately, without delay.
	 *
	 * The GA is only "resumed" after being queued if the ability is not otherwise blocked (e.g., but other abilities
	 * that are active on the character at the time that it is being resumed). In addition, this variation of the
	 * "Wait for Initiative Turn" task also factors in the tags of both the source/instigator and the target, and is
	 * intended to be used by abilities activated from events. The tags are evaluated at the time that the GA is being
	 * dequeued, so they should be provided from "live" objects rather than snapshotted objects to ensure that the tags
	 * are an accurate reflection of the world.
	 *
	 * Execution pins work as follows:
	 *	- OnQueued is called if the ability is queued, in case it needs to suspend itself while it is queued.
	 *	- OnReadyToAct is called when the character's "turn" in initiative order comes up. If the current Mode of Play
	 *	  Rule Set does not queue actions, this will fire immediately.
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
	 * @param SourceTags
	 *	The tags from the source/instigator actor/character. Can be left empty if the ability does not use source tags.
	 * @param TargetTags
	 *	The tags from the target actor/character. Can be left empty if this ability does not use target tags.
	 */
	UFUNCTION(
		BlueprintCallable,
		Category="Ability|Tasks",
		meta=(
			HidePin="OwningAbility",
			DefaultToSelf="OwningAbility",
			BlueprintInternalUseOnly="TRUE",
			DisplayName="Wait for Initiative Turn with Tags"
		)
	)
	static UPF2AbilityTask_WaitForInitiativeTurn* CreateWaitInitiativeTurnWithTags(
		UGameplayAbility*           OwningAbility,
		const FName                 TaskInstanceName,
		const FText                 ActionName,
		const FSlateBrush           ActionIcon,
		const FGameplayTagContainer& SourceTags,
		const FGameplayTagContainer& TargetTags);

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
	EPF2AbilityActivationResult ActivationOutcome;

	// =================================================================================================================
	// Protected Fields
	// =================================================================================================================
	/**
	 * For abilities that use source tags: The tags from the source/instigator actor/character.
	 *
	 * Can be a nullptr or empty container if the ability does not use source tags.
	 */
	const FGameplayTagContainer* SourceTags;

	/**
	 * For abilities that use target tags: The tags from the target actor/character.
	 *
	 * Can be a nullptr or empty container if the ability does not use target tags.
	 */
	const FGameplayTagContainer* TargetTags;

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
	 * Execution pin fired if the ability has been queued, in case it needs to suspend itself while it is queued.
	 *
	 * This execution pin is optional. This pin is fired upon queuing; then, when it is time for the ability to proceed,
	 * the "OnReadyToAct" execution pin will be fired to allow the ability to resume anything that was suspended.
	 */
	UPROPERTY(BlueprintAssignable)
	FGenericGameplayTaskDelegate OnQueued;

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
	explicit UPF2AbilityTask_WaitForInitiativeTurn() : ActivationOutcome(EPF2AbilityActivationResult::None)
	{
	}

	// =================================================================================================================
	// Public Methods - UAbilityTask Overrides
	// =================================================================================================================
	virtual void Activate() override;
	virtual void ExternalCancel() override;
	virtual void OnDestroy(bool bAbilityEnded) override;

	// =================================================================================================================
	// Public Methods - IPF2QueuedActionInterface
	// =================================================================================================================
	UFUNCTION(BlueprintCallable)
	virtual FText GetActionName() const override;

	UFUNCTION(BlueprintCallable)
	virtual FSlateBrush GetActionIcon() const override;

	UFUNCTION(BlueprintCallable)
	virtual EPF2AbilityActivationResult PerformAction() override;

	UFUNCTION(BlueprintCallable)
	virtual void CancelAction() override;

protected:
	// =================================================================================================================
	// Protected Methods
	// =================================================================================================================
	/**
	 * Gets whether this ability task was executed or cancelled after being queued.
	 *
	 * @return
	 *	- true if this ability task was executed or cancelled.
	 *	- false if this ability task has not yet been executed or cancelled.
	 */
	FORCEINLINE bool WasActivatedOrCanceled() const
	{
		const TArray<EPF2AbilityActivationResult> Statuses = {
			EPF2AbilityActivationResult::Activated,
			EPF2AbilityActivationResult::Cancelled,
		};

		return (Statuses.Contains(this->ActivationOutcome));
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
	void OnPerformAction_Client();

	/**
	 * Determine if the owning ability is blocked from activation or can be resumed where it left off.
	 *
	 * This takes the latest source and target tags into account because they may have changed since the ability was
	 * queued. For example, if this was an area of affect ability for which the player chose a target area, we need to
	 * recheck that the tags of the targets have not changed since the ability was queued.
	 *
	 * @return
	 *	- true if the ability is unblocked and can be resumed.
	 *	- false if the ability is blocked and cannot be resumed at this time (may be resumed in the future).
	 */
	bool CanAbilityProceed() const;
};

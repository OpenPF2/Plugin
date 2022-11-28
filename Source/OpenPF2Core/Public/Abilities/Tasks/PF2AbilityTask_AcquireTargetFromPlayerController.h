// OpenPF2 for UE Game Logic, Copyright 2022, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#pragma once

#include <Abilities/Tasks/AbilityTask.h>
#include <Abilities/Tasks/AbilityTask_WaitTargetData.h>

#include "PF2AbilityAllowedTargetSelectionType.h"
#include "PF2AbilityTaskBase.h"

#include "PF2AbilityTask_AcquireTargetFromPlayerController.generated.h"

// =====================================================================================================================
// Forward Declarations (to minimize header dependencies)
// =====================================================================================================================
class IPF2CharacterInterface;

// =====================================================================================================================
// Normal Declarations
// =====================================================================================================================
/**
 * A task to retrieve the target enemy or map location that the player has already selected through the PC.
 *
 * This is typically only useful in encounter mode, since it requires the player to select a location using a movement
 * grid, and the grid is hard to see unless the game is in a top-down perspective.
 */
UCLASS()
// ReSharper disable once CppClassCanBeFinal
class OPENPF2CORE_API UPF2AbilityTask_AcquireTargetFromPlayerController : public UPF2AbilityTaskBase
{
	GENERATED_BODY()

public:
	// =================================================================================================================
	// Public Static Methods
	// =================================================================================================================
	/**
	 * Retrieves the target enemy or map location that the player has selected through the UI.
	 *
	 * The location is obtained through a callback into the player controller.
	 *
	 * Execution pins work as follows:
	 *	- OnLocationSelected is called if there is a map location selection available from the player.
	 *	- OnCharacterSelected is called if there is a character selection available from the player.
	 *	- OnNothingSelected is called if there is not a valid selection available from the player.
	 *	- OnCancelled is called if the ability or task is cancelled.
	 *
	 * @param OwningAbility
	 *	A reference to the ability instance that is triggering this task. (This is automatically populated by Blueprint
	 *	from the ability Blueprint.)
	 * @param TaskInstanceName
	 *	A custom name for this task, in case it needs to be queried later while it is running.
	 * @param AllowedTargetType
	 *	The type of selection(s) the task will allow.
	 * @param RequiredTargetCharacterTags
	 *	One or more Gameplay Tags that must be present on a character in order for it to be considered a valid
	 *	selection. If empty, any character can be selected.
	 */
	UFUNCTION(
		BlueprintCallable,
		Category="Ability|Tasks|OpenPF2",
		meta=(
			HidePin="OwningAbility",
			DefaultToSelf="OwningAbility",
			BlueprintInternalUseOnly="TRUE",
			DisplayName="Acquire Target from Player Controller"
		)
	)
	static UPF2AbilityTask_AcquireTargetFromPlayerController* CreateAcquireTargetFromPlayerController(
		UGameplayAbility*                           OwningAbility,
		const FName                                 TaskInstanceName,
		const EPF2AbilityAllowedTargetSelectionType AllowedTargetType,
		const FGameplayTagContainer&                RequiredTargetCharacterTags);

protected:
	// =================================================================================================================
	// Protected Fields
	// =================================================================================================================
	/**
	 * The type of selection(s) the task will allow.
	 */
	EPF2AbilityAllowedTargetSelectionType AllowedTargetType;

	/**
	 * For character selections: The tags that a character must have for it to be a valid selection.
	 *
	 * Can be a nullptr or empty container if any character can be selected.
	 */
	FGameplayTagContainer RequiredTargetCharacterTags;

	/**
	 * For location selections: The map location that the player selected.
	 */
	const FVector TargetLocation;

	/**
	 * For character selections: The character that the player selected.
	 */
	const TScriptInterface<IPF2CharacterInterface> TargetCharacter;

	// =================================================================================================================
	// Delegates/Execution Pins
	// =================================================================================================================
	/**
	 * Execution pin fired when there is a map location selection available from the player.
	 */
	UPROPERTY(BlueprintAssignable)
	FWaitTargetDataDelegate OnLocationSelected;

	/**
	 * Execution pin fired when there is a character selection available from the player.
	 */
	UPROPERTY(BlueprintAssignable)
	FWaitTargetDataDelegate OnCharacterSelected;

	/**
	 * Execution pin fired when there is not a valid selection available from the player.
	 */
	UPROPERTY(BlueprintAssignable)
	FWaitTargetDataDelegate OnNothingSelected;

	/**
	 * Execution pin fired if the action gets canceled.
	 */
	UPROPERTY(BlueprintAssignable)
	FWaitTargetDataDelegate OnCancelled;

public:
	// =================================================================================================================
	// Public Methods - UAbilityTask Overrides
	// =================================================================================================================
	virtual void Activate() override;
	virtual void ExternalCancel() override;

private:
	// =================================================================================================================
	// Private Methods
	// =================================================================================================================
	/**
	 * Waits for the client to report and replicate a target, or replicate that a target is not available.
	 */
	void WaitForTargetFromClient();

	/**
	 * Notifies all bound multicast delegates that a target character or location has been selected.
	 *
	 * @param Data
	 *	The handle for the target data that was replicated.
	 * @param TargetTypeTag
	 *	A tag representing the type of target. Can be either "GameplayAbility.Event.TargetReceived.Character" or
	 *	"GameplayAbility.Event.TargetReceived.Location".
	 */
	void NotifyListenersAboutTarget(const FGameplayAbilityTargetDataHandle& Data, FGameplayTag TargetTypeTag) const;

	// =================================================================================================================
	// Private Native Event Callbacks
	// =================================================================================================================
	/**
	 * Callback fired if the GA running this task has been cancelled.
	 */
	void Native_OnAbilityCancelled() const;

	/**
	 * Callback invoked when target data has become available.
	 *
	 * This can be invoked on either the server or the client. When invoked on the client, the target data will be
	 * replicated to the server.
	 *
	 * @param Data
	 *	The handle for the target data to replicate.
	 * @param TargetTypeTag
	 *	A tag representing the type of target. Can be either "GameplayAbility.Event.TargetReceived.Character" or
	 *	"GameplayAbility.Event.TargetReceived.Location".
	 */
	UFUNCTION()
	void Native_OnTargetDataReady(
		const FGameplayAbilityTargetDataHandle& Data,
		const FGameplayTag                      TargetTypeTag);

	/**
	 * Callback invoked when target data is not available from the player controller.
	 *
	 * This can be invoked on either the server or the client. When invoked on the client, the cancellation will be
	 * replicated to the server.
	 */
	UFUNCTION()
	void Native_OnTargetDataNotAvailable();

	/**
	 * Callback invoked on the server when target data has been replicated from a client.
	 *
	 * @param Data
	 *	The handle for the target data that was replicated.
	 * @param TargetTypeTag
	 *	A tag representing the type of target. Can be either "GameplayAbility.Event.TargetReceived.Character" or
	 *	"GameplayAbility.Event.TargetReceived.Location".
	 */
	UFUNCTION()
	void Native_OnTargetDataReplicatedFromClient(
		const FGameplayAbilityTargetDataHandle& Data,
		const FGameplayTag                      TargetTypeTag);

	/**
	 * Callback invoked on the server when the client is not able to supply target data.
	 */
	UFUNCTION()
	void Native_OnTargetDataNotAvailableFromClient();
};

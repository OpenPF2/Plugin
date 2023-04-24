// OpenPF2 for UE Game Logic, Copyright 2022-2023, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#pragma once

#include <GameplayAbilitySpec.h>

#include <Components/InputComponent.h>

#include "OpenPF2Core.h"
#include "PF2AbilityInputBinding.generated.h"

// =====================================================================================================================
// Forward Declarations (to minimize header dependencies)
// =====================================================================================================================
class IPF2AbilityBindingsInterface;
class IPF2CharacterInterface;
class UGameplayAbility;

// =====================================================================================================================
// Normal Declarations
// =====================================================================================================================
/**
 * A single binding between an input action and an ability that can be activated.
 *
 * The ability must already have been granted to the character.
 */
USTRUCT(BlueprintType)
struct FPF2AbilityInputBinding
{
	GENERATED_BODY()

	// =================================================================================================================
	// Public Fields - Blueprint Accessible
	// =================================================================================================================
	/**
	 * The human-friendly name of the action, as configured in project input settings (e.g "Jump", "Fire", etc.).
	 */
	UPROPERTY(EditDefaultsOnly)
	FName ActionName;

protected:
	// =================================================================================================================
	// Protected Fields
	// =================================================================================================================
	/**
	 * The handle for the corresponding ability.
	 */
	UPROPERTY()
	FGameplayAbilitySpecHandle AbilitySpecHandle;

	/**
	 * The handles for input action bindings, if this binding has been connected to input.
	 */
	UPROPERTY()
	TArray<int32> InputHandles;

	/**
	 * The component that is managing this binding.
	 *
	 * This is declared as an actor component instead of an interface so that UE interacts with it properly for
	 * replication. UE will not do this if this component were declared/referenced through an interface field.
	 */
	UPROPERTY()
	UActorComponent* BindingsOwner;

	/**
	 * Whether this binding should consume the input when it fires.
	 *
	 * - If true, then the input will be consumed by this binding and a pawn or player controller will not be able to
	 *   react to it.
	 * - If false, then a pawn or player controller can react to the input action in addition to the binding being
	 *   invoked.
	 */
	UPROPERTY()
	bool bConsumeInput;

public:
	// =================================================================================================================
	// Public Constructors
	// =================================================================================================================
	/**
	 * Default constructor (used by Blueprint).
	 */
	explicit FPF2AbilityInputBinding() : BindingsOwner(nullptr), bConsumeInput(true)
	{
	}

	/**
	 * Constructor for initializing a FPF2AbilityInputBinding from a granted ability.
	 *
	 * @param ActionName
	 *	The human-friendly name of the action, as configured in project settings (e.g "Jump").
	 * @param AbilitySpec
	 *	The specification for the ability.
	 * @param Owner
	 *	The component that is managing this binding.
	 * @param bConsumeInput
	 *	Whether the binding should consume the input when it fires.
	 *	  - If true, then the input will be consumed by this binding and a pawn or player controller will not be able to
	 *	    react to it.
	 *	  - If false, then a pawn or player controller can react to the input action in addition to the binding being
	 *	    invoked.
	 */
	explicit FPF2AbilityInputBinding(const FName&                  ActionName,
	                                 const FGameplayAbilitySpec&   AbilitySpec,
	                                 IPF2AbilityBindingsInterface* Owner,
	                                 const bool                    bConsumeInput = true);

	// =================================================================================================================
	// Public Destructors
	// =================================================================================================================
	/**
	 * Default destructor.
	 */
	virtual ~FPF2AbilityInputBinding() = default;

	// =================================================================================================================
	// Public Methods
	// =================================================================================================================
	/**
	 * Determines whether the ability in this binding has been connected to an input component.
	 *
	 * @return
	 *	- true if this binding is presently connected to input.
	 *	- false if this binding is not connected to input at this time.
	 */
	FORCEINLINE bool IsConnectedToInput() const
	{
		return this->InputHandles.Num() != 0;
	}

	/**
	 * Gets whether this binding consumes input when it fires.
	 *
	 * @return
	 * - If true, then the input will be consumed by this binding and a pawn or player controller will not be able to
	 *   react to it.
	 * - If false, then a pawn or player controller can react to the input action in addition to the binding being
	 *   invoked.
	 */
	FORCEINLINE bool IsConsumingInput() const
	{
		return this->bConsumeInput;
	}

	/**
	 * Wires-up this binding to receive input from the given player input component.
	 *
	 * This only has an effect if this binding has an action assigned and this binding has not yet been wired up;
	 * otherwise, this call will have no effect.
	 *
	 * @param InputComponent
	 *	The component to which input should be bound.
	 */
	void ConnectToInput(UInputComponent* InputComponent);

	/**
	 * Removes this binding from the given player input component.
	 *
	 * This must be called before changing the action of any binding.
	 *
	 * This only has an effect if this binding has been wired up; otherwise, this call will have no effect.
	 */
	void DisconnectFromInput(UInputComponent* InputComponent);

protected:
	// =================================================================================================================
	// Protected Static Methods
	// =================================================================================================================
	/**
	 * Notifies the specified binding instance that the input action it corresponds to has been activated.
	 *
	 * @param Binding
	 *	The binding to notify of a button activation.
	 */
	static void LocalInputPressed(FPF2AbilityInputBinding* Binding);

	/**
	 * Notifies the specified binding instance that the input action it corresponds to has been released.
	 *
	 * @param Binding
	 *	The binding to notify of a button release.
	 */
	static void LocalInputReleased(FPF2AbilityInputBinding* Binding);

	// =================================================================================================================
	// Protected Instance Methods
	// =================================================================================================================
	/**
	 * Gets the component that is managing this binding.
	 *
	 * @return
	 *	The containing bindings component.
	 */
	IPF2AbilityBindingsInterface* GetBindingsOwner() const;

	/**
	 * Binds a specific input event/action on the specified input component to the given callback.
	 *
	 * @param InputComponent
	 *	The input component for which input is being bound.
	 * @param InKeyEvent
	 *	The event to which the callback will be bound.
	 * @param Callback
	 *	The callback to invoke.
	 *
	 * @return
	 *	The handle in the input component of the action binding.
	 */
	int32 AddActionBinding(UInputComponent*  InputComponent,
	                       const EInputEvent InKeyEvent,
	                       void              (*Callback)(FPF2AbilityInputBinding*));

	/**
	 * Assembles and executes a command that invokes the ability associated with this binding.
	 *
	 * The ability may be queued if the active MoPRS is requiring abilities to be queued (e.g., encounters).
	 */
	virtual void ActivateAbility();

	/**
	 * Notifies the ability that the player is no longer invoking the ability associated with this binding.
	 *
	 * The default implementation does nothing.
	 */
	virtual void DeactivateAbility();
};

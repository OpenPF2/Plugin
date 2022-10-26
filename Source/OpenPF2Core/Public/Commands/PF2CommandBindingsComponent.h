// OpenPF2 for UE Game Logic, Copyright 2022, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#pragma once

#include <Components/ActorComponent.h>

#include "PF2CharacterInterface.h"
#include "PF2CommandBindingsInterface.h"
#include "PF2CommandInputBinding.h"
#include "PF2CommandBindingsComponent.generated.h"

// =====================================================================================================================
// Delegate Declarations
// =====================================================================================================================
/**
 * Delegate for Blueprints to react to a command queue getting wired up to input or disconnected from input.
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPF2CommandQueueInputConnectionChangedDelegate);

// =====================================================================================================================
// Normal Declarations
// =====================================================================================================================
/**
 * A component for characters that need to support binding execution of Gameplay Abilities to input actions.
 *
 * Unlike the native input binding support offered by the GAS, this version does not bind input directly to a specific
 * pawn/character. Instead, it allows input to be routed to whichever character the player is currently controlling, and
 * it works automatically with abilities that need to be queued during encounters.
 */
UCLASS(ClassGroup="OpenPF2-Characters", meta=(BlueprintSpawnableComponent))
// ReSharper disable once CppClassCanBeFinal
class OPENPF2CORE_API UPF2CommandBindingsComponent : public UActorComponent, public IPF2CommandBindingsInterface
{
	GENERATED_BODY()

public:
	// =================================================================================================================
	// Public Properties - Multicast Delegates
	// =================================================================================================================
	/**
	 * Event fired when local input is connected to this component.
	 *
	 * This event is only fired on clients.
	 */
	UPROPERTY(BlueprintAssignable, Category="OpenPF2|Components|Characters|Command Bindings")
	FPF2CommandQueueInputConnectionChangedDelegate OnInputConnected;

	/**
	 * Event fired when local input is disconnected from this component.
	 *
	 * This event is only fired on clients.
	 */
	UPROPERTY(BlueprintAssignable, Category="OpenPF2|Components|Characters|Command Bindings")
	FPF2CommandQueueInputConnectionChangedDelegate OnInputDisconnected;

private:
	/**
	 * The input component to which this component is currently wired.
	 *
	 * This is not replicated, since it is only of importance to local clients.
	 */
	UPROPERTY()
	UInputComponent* InputComponent;

	/**
	 * The association between inputs and Gameplay Abilities.
	 *
	 * This supports replication from the server, which is enabled by default since the server is the authority on what
	 * abilities each character has and the default bindings for those abilities. Abilities are typically loaded by
	 * invoking LoadAbilitiesFromCharacter() from the server-only OnPossess() method of the Player Controller.
	 * Replication on this component also ensures any changes made to the bindings will automatically update what is
	 * bound to input as long as this component has been wired-up to an input component.
	 */
	UPROPERTY(ReplicatedUsing=OnRep_Bindings)
	TArray<FPF2CommandInputBinding> Bindings;

public:
	// =================================================================================================================
	// Public Constructor
	// =================================================================================================================
	/**
	 * Default constructor for UPF2CommandBindingsComponent.
	 */
	explicit UPF2CommandBindingsComponent() : InputComponent(nullptr)
	{
		// This component needs to be replicated in order for
		this->SetIsReplicatedByDefault(true);
	}

	// =================================================================================================================
	// Public Methods - IPF2CommandBindingsInterface Implementation
	// =================================================================================================================
	UFUNCTION(BlueprintCallable)
	virtual void ClearBindings() override;

	UFUNCTION(BlueprintCallable)
	virtual void LoadAbilitiesFromCharacter() override;

	UFUNCTION(BlueprintCallable)
	virtual void ConnectToInput(UInputComponent* NewInputComponent) override;

	UFUNCTION(BlueprintCallable)
	virtual void DisconnectFromInput() override;

	virtual void ExecuteBoundAbility(const FGameplayAbilitySpecHandle AbilitySpecHandle) override;

	// =================================================================================================================
	// Public Methods - IPF2ActorComponentInterface Implementation
	// =================================================================================================================
	UFUNCTION(BlueprintCallable)
	virtual UActorComponent* ToActorComponent() override;

	// =================================================================================================================
	// Public Methods - IPF2LogIdentifiableInterface Implementation
	// =================================================================================================================
	UFUNCTION(BlueprintCallable)
	virtual FString GetIdForLogs() const override;

	// =================================================================================================================
	// Public Methods - AActorComponent Overrides
	// =================================================================================================================
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	// =================================================================================================================
	// Protected Methods
	// =================================================================================================================
	/**
	 * Gets the input component to which this bindings component is wired up to, if it is wired up.
	 *
	 * @return
	 *	- If this component is currently wired-up to input: the input component to which it is wired up.
	 *	- If this component is not currently wired-up to input: null.
	 */
	FORCEINLINE UInputComponent* GetInputComponent() const
	{
		return this->InputComponent;
	}

	/**
	 * Gets whether this component is currently wired up to input.
	 *
	 * @return
	 *	- true if this component is currently wired up to input.
	 *	- false if it is not currently wired up to input.
	 */
	FORCEINLINE bool IsConnectedToInput() const
	{
		return this->GetInputComponent() != nullptr;
	}

	/**
	 * Gets the character of which this component is a part.
	 *
	 * @return
	 *	The character actor that owns this component.
	 */
	IPF2CharacterInterface* GetOwningCharacter() const;

	// =================================================================================================================
	// Protected Replication Callbacks
	// =================================================================================================================
	/**
	 * Replication callback for the "Bindings" property.
	 *
	 * This ensures that bindings loaded/defined on the server are applied properly to input on the client.
	 */
	UFUNCTION()
	void OnRep_Bindings(const TArray<FPF2CommandInputBinding> OldBindings) const;

	// =================================================================================================================
	// Protected Native Event Callbacks
	// =================================================================================================================
	/**
	 * Callback invoked in C++ code when input has been connected to this component.
	 *
	 * This notifies all event listeners that input has been connected.
	 */
	virtual void Native_OnInputConnected();

	/*
	 * Callback invoked in C++ code when input has been disconnected from this component.
	 *
	 * This notifies all event listeners that input has been disconnected.
	 */
	virtual void Native_OnInputDisconnected();
};

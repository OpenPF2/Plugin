// OpenPF2 for UE Game Logic, Copyright 2022-2023, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#pragma once

#include <Components/ActorComponent.h>

#include "PF2CharacterInterface.h"
#include "PF2AbilityBindingsInterface.h"
#include "PF2AbilityInputBinding.h"
#include "PF2AbilityBindingsComponent.generated.h"

// =====================================================================================================================
// Forward Declarations (to minimize header dependencies)
// =====================================================================================================================
class IPF2AbilityExecutionFilterInterface;
class UPF2AbilityExecutionFilterBase;

// =====================================================================================================================
// Delegate Declarations
// =====================================================================================================================
/**
 * Delegate for Blueprints to react to a bindings component getting wired up to input or disconnected from input.
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPF2AbilityBindingsInputConnectionChangedDelegate);

// =====================================================================================================================
// Normal Declarations
// =====================================================================================================================
/**
 * A component for characters that need to support binding execution of Gameplay Abilities to input actions.
 *
 * Unlike the native input binding support offered by the GAS, this version makes it possible to dynamically bind and
 * unbind input to abilities as needed, allowing input to be routed to whichever character the player is currently
 * controlling. This also works automatically with the character command system, ensuring that commands will be queued
 * during encounters if required by the MoPRS.
 */
UCLASS(ClassGroup="OpenPF2-Characters", meta=(BlueprintSpawnableComponent))
// ReSharper disable once CppClassCanBeFinal
class OPENPF2CORE_API UPF2AbilityBindingsComponent : public UActorComponent, public IPF2AbilityBindingsInterface
{
	GENERATED_BODY()

public:
	// =================================================================================================================
	// Public Fields
	// =================================================================================================================
	UPROPERTY(
		EditDefaultsOnly,
		meta=(MustImplement="PF2AbilityExecutionFilterInterface"),
		DisplayName="Ability Execution Filters",
		Category="OpenPF2 Command Bindings"
	)
	TArray<TSubclassOf<UObject>> Filters;

	// =================================================================================================================
	// Public Fields - Multicast Delegates
	// =================================================================================================================
	/**
	 * Event fired when local input is connected to this component.
	 *
	 * This event is only fired on clients.
	 */
	UPROPERTY(BlueprintAssignable, Category="OpenPF2|Components|Characters|Command Bindings")
	FPF2AbilityBindingsInputConnectionChangedDelegate OnInputConnected;

	/**
	 * Event fired when local input is disconnected from this component.
	 *
	 * This event is only fired on clients.
	 */
	UPROPERTY(BlueprintAssignable, Category="OpenPF2|Components|Characters|Command Bindings")
	FPF2AbilityBindingsInputConnectionChangedDelegate OnInputDisconnected;

protected:
	/**
	 * Whether bindings managed by this component should consume the input when they fire.
	 *
	 * - If true, then matching inputs will be consumed by bindings, and a pawn or player controller will not be able to
	 *   react to them.
	 * - If false, then a pawn or player controller can react to the input action in addition to bindings handling them.
	 */
	UPROPERTY(EditAnywhere, BlueprintGetter=IsConsumingInput, BlueprintSetter=SetConsumeInput)
	bool bConsumeInput;

private:
	/**
	 * The input component to which this component is currently wired.
	 *
	 * This is not replicated, since it is only of relevance to local clients.
	 */
	UPROPERTY()
	UInputComponent* InputComponent;

	/**
	 * The association between inputs and Gameplay Abilities.
	 *
	 * This is not replicated because input is only a concern of the local client and not the server. Instead, abilities
	 * should be loaded by invoking LoadAbilitiesFromCharacter() after abilities have replicated through the ASC from
	 * the server. This is handled automatically when using the default OpenPF2 player controller implementation.
	 */
	UPROPERTY()
	TArray<FPF2AbilityInputBinding> Bindings;

public:
	// =================================================================================================================
	// Public Constructor
	// =================================================================================================================
	/**
	 * Default constructor for UPF2AbilityBindingsComponent.
	 */
	explicit UPF2AbilityBindingsComponent() : bConsumeInput(true), InputComponent(nullptr)
	{
	}

	// =================================================================================================================
	// Public Methods - IPF2AbilityBindingsInterface Implementation
	// =================================================================================================================
	UFUNCTION(BlueprintCallable)
	virtual bool IsConsumingInput() const override;

	UFUNCTION(BlueprintCallable)
	virtual void SetConsumeInput(const bool bNewValue) override;

	UFUNCTION(BlueprintCallable)
	virtual void ClearBindings() override;

	UFUNCTION(BlueprintCallable)
	virtual void LoadAbilitiesFromCharacter() override;

	UFUNCTION(BlueprintCallable)
	virtual TMap<FName, TScriptInterface<IPF2GameplayAbilityInterface>> GetBindingsMap() const override;

	UFUNCTION(BlueprintCallable)
	virtual void ConnectToInput(UInputComponent* NewInputComponent) override;

	UFUNCTION(BlueprintCallable)
	virtual void DisconnectFromInput() override;

	virtual void ExecuteBoundAbility(const FName                      ActionName,
	                                 const FGameplayAbilitySpecHandle AbilitySpecHandle) override;

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

	/**
	 * Applies ability execution filters to the activation of a bound ability.
	 *
	 * Filters may veto execution of the filter. If a filter does so, the result of this method will be "false".
	 *
	 * @param InActionName
	 *	The name of the input action that was invoked.
	 * @param InCharacter
	 *	The character on which the action will be performed.
	 * @param InOutAbilitySpecHandle
	 *	The handle for the ability to activate. This will be modified by filter execution.
	 * @param InOutAbilityPayload
	 *	The payload to pass to the activated ability. This will be modified by filter execution.
	 *
	 * @return
	 *	- "true" if the ability should proceed to be executed.
	 *	- "false" if the ability should not be executed because the last filter executed vetoed it.
	 */
	bool FilterAbilityActivation(
		const FName                                    InActionName,
		const TScriptInterface<IPF2CharacterInterface> InCharacter,
		FGameplayAbilitySpecHandle&                    InOutAbilitySpecHandle,
		FGameplayEventData&                            InOutAbilityPayload);

	// =================================================================================================================
	// Protected Native Event Callbacks
	// =================================================================================================================
	/**
	 * Callback invoked in C++ code when input has been connected to this component.
	 *
	 * This notifies all event listeners that input has been connected.
	 */
	virtual void Native_OnInputConnected();

	/**
	 * Callback invoked in C++ code when input has been disconnected from this component.
	 *
	 * This notifies all event listeners that input has been disconnected.
	 */
	virtual void Native_OnInputDisconnected();
};

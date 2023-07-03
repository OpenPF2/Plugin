// OpenPF2 for UE Game Logic, Copyright 2022-2023, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#pragma once

#include <Components/ActorComponent.h>

#include <Containers/Map.h>

#include "PF2AbilityBindingsInterface.h"
#include "PF2AbilityInputBinding.h"
#include "PF2CharacterInterface.h"
#include "PF2AbilityBindingsComponent.generated.h"

// =====================================================================================================================
// Forward Declarations (to minimize header dependencies)
// =====================================================================================================================
class IPF2AbilityExecutionFilterInterface;
class UEnhancedInputComponent;
class UInputAction;
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
	/**
	 * Filters to apply to the activation of abilities through this component.
	 *
	 * This makes it possible to redirect an input action to one or more abilities depending upon the state of the game
	 * or something about the character. For example, consider an input action that works as follows:
	 * - While in exploration mode: the input action results in the character attempting their default attack.
	 * - While in encounter mode:
	 *   - If the character is targeting an empty square: the input action results in the character moving to the
	 *     square.
	 *   - If the character is targeting an square containing an enemy: the input action results in the character
	 *     attempting their default attack.
	 */
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
	UPROPERTY(BlueprintAssignable, Category="OpenPF2|Components|Characters|Ability Bindings")
	FPF2AbilityBindingsInputConnectionChangedDelegate OnInputConnected;

	/**
	 * Event fired when local input is disconnected from this component.
	 *
	 * This event is only fired on clients.
	 */
	UPROPERTY(BlueprintAssignable, Category="OpenPF2|Components|Characters|Ability Bindings")
	FPF2AbilityBindingsInputConnectionChangedDelegate OnInputDisconnected;

protected:
	UPROPERTY()
	UPF2AbilityBindingsInterfaceEvents* Events;

private:
	/**
	 * The input component to which this component is currently wired.
	 *
	 * This is not replicated, since it is only of relevance to local clients.
	 */
	UPROPERTY()
	UEnhancedInputComponent* InputComponent;

	/**
	 * The association between input actions and Gameplay Abilities.
	 *
	 * This is not replicated because input is only a concern of the local client and not the server. Instead, abilities
	 * should be loaded by invoking LoadAbilitiesFromCharacter() after abilities have replicated through the ASC from
	 * the server. This is handled automatically when using the default OpenPF2 player controller implementation.
	 */
	UPROPERTY()
	TMap<const UInputAction*, UPF2AbilityInputBinding*> Bindings;

public:
	// =================================================================================================================
	// Public Constructor
	// =================================================================================================================
	/**
	 * Default constructor for UPF2AbilityBindingsComponent.
	 */
	explicit UPF2AbilityBindingsComponent() : InputComponent(nullptr)
	{
		this->Events = CreateDefaultSubobject<UPF2AbilityBindingsInterfaceEvents>("InterfaceEvents");
	}

	// =================================================================================================================
	// Public Methods - IPF2AbilityBindingsInterface Implementation
	// =================================================================================================================
	UFUNCTION(BlueprintCallable)
	virtual UPF2AbilityBindingsInterfaceEvents* GetEvents() const override;

	UFUNCTION(BlueprintCallable)
	virtual TMap<UInputAction*, TScriptInterface<IPF2GameplayAbilityInterface>> GetBindingsMap() const override;

	UFUNCTION(BlueprintCallable)
	virtual void SetBinding(UInputAction* Action, const FGameplayAbilitySpec& AbilitySpec) override;

	UFUNCTION(BlueprintCallable)
	virtual void ClearBindings() override;

	UFUNCTION(BlueprintCallable)
	virtual void ClearBinding(const UInputAction* Action) override;

	UFUNCTION(BlueprintCallable)
	virtual void LoadAbilitiesFromCharacter() override;

	UFUNCTION(BlueprintCallable)
	virtual void ConnectToInput(UEnhancedInputComponent* NewInputComponent) override;

	UFUNCTION(BlueprintCallable)
	virtual void DisconnectFromInput() override;

	virtual void ExecuteBoundAbility(const UInputAction*              Action,
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
	 * Gets the enhanced input component to which this bindings component is wired up to, if it is wired up.
	 *
	 * @return
	 *	- If this component is currently wired-up to input: the input component to which it is wired up.
	 *	- If this component is not currently wired-up to input: null.
	 */
	FORCEINLINE UEnhancedInputComponent* GetInputComponent() const
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
	 * Binds an ability to a particular input action without notifying listeners.
	 *
	 * @param Action
	 *	The action to which the ability will be bound.
	 * @param AbilitySpec
	 *	The ability to bind.
	 */
	void SetBindingWithoutBroadcast(UInputAction* Action, const FGameplayAbilitySpec& AbilitySpec);

	/**
	 * Stops listening for input for the specified binding.
	 *
	 * @param Binding
	 *	The binding to disconnect from input.
	 */
	void DisconnectBindingFromInput(UPF2AbilityInputBinding* Binding) const;

	/**
	 * Applies ability execution filters to the activation of a bound ability.
	 *
	 * Filters may veto execution of the filter. If a filter does so, the result of this method will be "false".
	 *
	 * @param InAction
	 *	The input action that was invoked.
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
		const UInputAction*                            InAction,
		const TScriptInterface<IPF2CharacterInterface> InCharacter,
		FGameplayAbilitySpecHandle&                    InOutAbilitySpecHandle,
		FGameplayEventData&                            InOutAbilityPayload);

	// =================================================================================================================
	// Protected Native Event Callbacks
	// =================================================================================================================
	virtual void Native_OnBindingsChanged();

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

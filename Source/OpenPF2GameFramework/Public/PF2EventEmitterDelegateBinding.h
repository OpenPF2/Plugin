// OpenPF2 Game Framework for Unreal Engine, Copyright 2023-2024, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#pragma once

#include <Engine/ComponentDelegateBinding.h>
#include <Engine/DynamicBlueprintBinding.h>

#include <UObject/ObjectMacros.h>

#include "PF2EventEmitterDelegateBinding.generated.h"

/**
 * A type of dynamic binding that enables blueprints to bind to delegates of Events Objects exposed by Event Emitters.
 */
UCLASS()
class OPENPF2GAMEFRAMEWORK_API UPF2EventEmitterDelegateBinding : public UDynamicBlueprintBinding
{
	GENERATED_BODY()

protected:
	// =================================================================================================================
	// Protected Static Methods
	// =================================================================================================================
	/**
	 * Looks up the event emitter variable/property in a Blueprint object that is specified in a binding.
	 *
	 * This is null safe. If OwnerInstance is a null pointer, the result is also a null pointer.
	 *
	 * @param Binding
	 *	The binding that specifies the target variable/property.
	 * @param OwnerInstance
	 *	The blueprint that owns the variable/property that is desired.
	 *
	 * @return
	 *	Either a pointer to the event emitter stored in the target blueprint variable, or nullptr if the variable
	 *	cannot be located in the blueprint.
	 */
	static UObject* GetEmitterComponent(const UObject*                            OwnerInstance,
	                                    const FBlueprintComponentDelegateBinding& Binding);

	/**
	 * Looks up the delegate property of an Events Object that is targeted by a binding.
	 *
	 * @param Binding
	 *	The binding that specifies the target delegate property.
	 * @param EventsObject
	 *	The events object containing the delegate property.
	 *
	 * @return
	 *	Either a pointer to the delegate property in the events object, or nullptr if the property cannot be located in
	 *	the events object.
	 */
	static FMulticastDelegateProperty* GetDelegateProperty(const UObject*                            EventsObject,
	                                                       const FBlueprintComponentDelegateBinding& Binding);

	// =================================================================================================================
	// Protected Fields
	// =================================================================================================================
	/**
	 * Details about all of the events that will be bound when this binding is applied to an Event Emitter.
	 */
	UPROPERTY()
	TArray<FBlueprintComponentDelegateBinding> EventEmitterBindings;

public:
	/**
	 * Adds information about an event to be bound when this binding is applied to an Event Emitter.
	 *
	 * @param Binding
	 *	The binding to add.
	 */
	FORCEINLINE void AddBinding(const FBlueprintComponentDelegateBinding& Binding)
	{
		this->EventEmitterBindings.Add(Binding);
	}

	// =================================================================================================================
	// Public Methods - DynamicBlueprintBinding Implementation
	// =================================================================================================================
	virtual void BindDynamicDelegates(UObject* InInstance) const override;

	virtual void UnbindDynamicDelegates(UObject* InInstance) const override;

	virtual void UnbindDynamicDelegatesForProperty(UObject*               InInstance,
	                                               const FObjectProperty* InObjectProperty) const override;

protected:
	/**
	 * Binds an event to the delegate property of an Events Object.
	 *
	 * @param Owner
	 *	The blueprint instance that contains an event emitter as a component/variable/property.
	 * @param Binding
	 *	The binding that specifies the target variable/property and target event.
	 * @param EventsObject
	 *	The events object returned by the event emitter variable/property.
	 * @param DelegateProperty
	 *	The delegate property of the events object to which an event will be bound.
	 */
	void BindDynamicDelegate(UObject*                                  Owner,
	                         const FBlueprintComponentDelegateBinding& Binding,
	                         UObject*                                  EventsObject,
	                         const FMulticastDelegateProperty*         DelegateProperty) const;

	/**
	 * Unbinds an event from the delegate property of an Events Object.
	 *
	 * @param Owner
	 *	The blueprint instance that contains an event emitter as a component/variable/property.
	 * @param Binding
	 *	The binding that specifies the target variable/property and target event.
	 * @param EventsObject
	 *	The events object returned by the event emitter variable/property.
	 * @param DelegateProperty
	 *	The delegate property of the events object from which an event will be unbound.
	 */
	void UnbindDynamicDelegate(UObject*                                  Owner,
	                           const FBlueprintComponentDelegateBinding& Binding,
	                           UObject*                                  EventsObject,
	                           const FMulticastDelegateProperty*         DelegateProperty) const;

	/**
	 * Constructs a script delegate that is suitable for binding to the delegate property of an Events Object.
	 *
	 * @param Owner
	 *	The blueprint instance that contains an event emitter as a component/variable/property.
	 * @param Binding
	 *	The binding that specifies the target variable/property and target event.
	 * @param DelegateProperty
	 *	The delegate property of the events object from which an event will be unbound.
	 *
	 * @return
	 *	A script delegate that references the delegate property.
	 */
	FScriptDelegate BuildScriptDelegate(UObject*                                  Owner,
	                                    const FBlueprintComponentDelegateBinding& Binding,
	                                    const FMulticastDelegateProperty*         DelegateProperty) const;
};

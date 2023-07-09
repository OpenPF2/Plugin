// OpenPF2 for UE Game Logic, Copyright 2023, Guy Elsmore-Paddock. All Rights Reserved.
//
// Adapted from "Runtime/Engine/Private/ComponentDelegateBinding.cpp" (Unreal Engine 5.1), which is Copyright Epic
// Games, Inc. Licensed only for use with Unreal Engine.

#include "PF2EventEmitterDelegateBinding.h"

#include "PF2EventEmitterInterface.h"

UObject* UPF2EventEmitterDelegateBinding::GetEmitterComponent(const UObject*                            OwnerInstance,
                                                              const FBlueprintComponentDelegateBinding& Binding)
{
	UObject*    EmitterComponent      = nullptr;
	const FName ComponentPropertyName = Binding.ComponentPropertyName;

	if ((OwnerInstance != nullptr) && (ComponentPropertyName != NAME_None))
	{
		const UClass*          OwnerClass        = OwnerInstance->GetClass();
		const FObjectProperty* ComponentProperty = FindFProperty<FObjectProperty>(OwnerClass, ComponentPropertyName);

		if (ComponentProperty != nullptr)
		{
			// Get the property that points to the component.
			EmitterComponent = ComponentProperty->GetObjectPropertyValue_InContainer(OwnerInstance);
		}
	}

	return EmitterComponent;
}

FMulticastDelegateProperty* UPF2EventEmitterDelegateBinding::GetDelegateProperty(
	const UObject*                            EventsObject,
	const FBlueprintComponentDelegateBinding& Binding)
{
	FMulticastDelegateProperty* DelegateProperty     = nullptr;
	const FName                 DelegatePropertyName = Binding.DelegatePropertyName;

	if ((EventsObject != nullptr) && (DelegatePropertyName != NAME_None))
	{
		const UClass* EventsClass = EventsObject->GetClass();

		// Find the delegate property in the events class.
		DelegateProperty = FindFProperty<FMulticastDelegateProperty>(EventsClass, DelegatePropertyName);
	}

	return DelegateProperty;
}

void UPF2EventEmitterDelegateBinding::BindDynamicDelegates(UObject* InInstance) const
{
	for (auto BindingIt = this->EventEmitterBindings.CreateConstIterator(); BindingIt; ++BindingIt)
	{
		const FBlueprintComponentDelegateBinding& Binding = *BindingIt;

		const UObject*                    Emitter          = GetEmitterComponent(InInstance, Binding);
		UObject*                          EventsObject     = IPF2EventEmitterInterface::GetEventsOfObject(Emitter);
		const FMulticastDelegateProperty* DelegateProperty = GetDelegateProperty(EventsObject, Binding);

		this->BindDynamicDelegate(InInstance, Binding, EventsObject, DelegateProperty);
	}
}

void UPF2EventEmitterDelegateBinding::UnbindDynamicDelegates(UObject* InInstance) const
{
	for (auto BindingIt = this->EventEmitterBindings.CreateConstIterator(); BindingIt; ++BindingIt)
	{
		const FBlueprintComponentDelegateBinding& Binding = *BindingIt;

		const UObject*                    Emitter          = GetEmitterComponent(InInstance, Binding);
		UObject*                          EventsObject     = IPF2EventEmitterInterface::GetEventsOfObject(Emitter);
		const FMulticastDelegateProperty* DelegateProperty = GetDelegateProperty(EventsObject, Binding);

		this->UnbindDynamicDelegate(InInstance, Binding, EventsObject, DelegateProperty);
	}
}

void UPF2EventEmitterDelegateBinding::UnbindDynamicDelegatesForProperty(UObject*               InInstance,
                                                                        const FObjectProperty* InObjectProperty) const
{
	for (auto BindingIt = this->EventEmitterBindings.CreateConstIterator(); BindingIt; ++BindingIt)
	{
		const FBlueprintComponentDelegateBinding& Binding = *BindingIt;

		if (Binding.ComponentPropertyName == InObjectProperty->GetFName())
		{
			const UObject*                    Emitter          = GetEmitterComponent(InInstance, Binding);
			UObject*                          EventsObject     = IPF2EventEmitterInterface::GetEventsOfObject(Emitter);
			const FMulticastDelegateProperty* DelegateProperty = GetDelegateProperty(EventsObject, Binding);

			this->UnbindDynamicDelegate(InInstance, Binding, EventsObject, DelegateProperty);
			break;
		}
	}
}

// ReSharper disable once CppMemberFunctionMayBeStatic
void UPF2EventEmitterDelegateBinding::BindDynamicDelegate(
	UObject*                                  Owner,
	const FBlueprintComponentDelegateBinding& Binding,
	UObject*                                  EventsObject,
	const FMulticastDelegateProperty*         DelegateProperty) const
{
	const FScriptDelegate Delegate = BuildScriptDelegate(Owner, Binding, DelegateProperty);

	if ((EventsObject != nullptr) && Delegate.IsBound())
	{
		// Bind the custom event function of the owning Blueprint instance to the delegate on the events object.
		DelegateProperty->AddDelegate(Delegate, EventsObject);
	}
}

// ReSharper disable once CppMemberFunctionMayBeStatic
void UPF2EventEmitterDelegateBinding::UnbindDynamicDelegate(
	UObject*                                  Owner,
	const FBlueprintComponentDelegateBinding& Binding,
	UObject*                                  EventsObject,
	const FMulticastDelegateProperty*         DelegateProperty) const
{
	const FScriptDelegate Delegate = BuildScriptDelegate(Owner, Binding, DelegateProperty);

	if ((EventsObject != nullptr) && Delegate.IsBound())
	{
		// Unbind the custom event function of the owning Blueprint instance from the delegate on the events object.
		DelegateProperty->RemoveDelegate(Delegate, EventsObject);
	}
}

// ReSharper disable once CppMemberFunctionMayBeStatic
FScriptDelegate UPF2EventEmitterDelegateBinding::BuildScriptDelegate(
	UObject*                                  Owner,
	const FBlueprintComponentDelegateBinding& Binding,
	const FMulticastDelegateProperty*         DelegateProperty) const
{
	FScriptDelegate Delegate;
	const FName     FunctionNameToBind = Binding.FunctionNameToBind;

	checkf(!Delegate.IsBound(), TEXT("Delegate should start out unbound."));

	if ((Owner != nullptr) && (DelegateProperty != nullptr) && (FunctionNameToBind != NAME_None))
	{
		const UClass*    OwnerClass     = Owner->GetClass();
		const UFunction* FunctionToBind = OwnerClass->FindFunctionByName(FunctionNameToBind);

		if (FunctionToBind != nullptr)
		{
			Delegate.BindUFunction(Owner, FunctionNameToBind);
			checkf(Delegate.IsBound(), TEXT("Delegate should now be bound."));
		}
	}

	return Delegate;
}

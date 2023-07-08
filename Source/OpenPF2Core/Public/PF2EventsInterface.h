// OpenPF2 for UE Game Logic, Copyright 2023, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#pragma once

#include <UObject/Interface.h>

#include "PF2EventsInterface.generated.h"

// =====================================================================================================================
// Normal Declarations - Types
// =====================================================================================================================
UINTERFACE(BlueprintType, meta=(CannotImplementInterfaceInBlueprint))
class OPENPF2CORE_API UPF2EventsInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * An interface for objects that expose delegates via an "Events" object.
 *
 * Following the pattern afforded by this interface reduces coupling by enabling objects to make use of delegates/events
 * while still depending only on each other's UInterfaces. Normally, Blueprint does not support binding to delegates on
 * an object through a UInterface unless the object is cast to a concrete type, but that couples the class using the
 * object to only that concrete implementation of the interface.
 *
 * The contract of objects that implement this interface (an "Implementation Class") is that they must implement at
 * least these two methods:
 *   1. GetEvents() - Should be a BlueprintCallable method. Must return a specific, concrete UObject that has only
 *      dynamic multicast delegates and no other logic, properties, methods, or UFunctions. Since the return type of
 *      this method is specific to each Implementation Class, the exact signature of this method should be defined in
 *      the primary UInterface of the Implementation Class. Blueprints can bind delegates to this object.
 *
 *   2. GetGenericEventsObject() - Should NOT be a BlueprintCallable method. Must return the same object as GetEvents(),
 *      but as a non-specific, generic UObject. The signature of this method is defined by this interface. This method
 *      is used internally by the editor to expose delegates of the Events object as though they were events of the
 *      Implementation Class, to make it easier to use Implementation Classes following this Events object pattern.
 */
class OPENPF2CORE_API IPF2EventsInterface : public IInterface
{
	GENERATED_BODY()

public:
	/**
	 * Gets the object to which delegates can be bound.
	 *
	 * This is used internally by the OpenPF2 Editor Support module to extend the Blueprint editor with support for
	 * binding to delegates/events exposed by an interface.
	 *
	 * @return
	 *	The events object, as a UObject.
	 */
	virtual UObject* GetGenericEventsObject() const = 0;
};

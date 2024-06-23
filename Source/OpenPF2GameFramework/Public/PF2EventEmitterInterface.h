// OpenPF2 for UE Game Logic, Copyright 2023-2024, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#pragma once

#include <UObject/Interface.h>

#include "PF2EventEmitterInterface.generated.h"

// =====================================================================================================================
// Normal Declarations - Types
// =====================================================================================================================
UINTERFACE(BlueprintType, meta=(CannotImplementInterfaceInBlueprint))
class OPENPF2GAMEFRAMEWORK_API UPF2EventEmitterInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * An interface for objects that expose delegates via an Events Object.
 *
 * Following the pattern afforded by this interface reduces coupling by enabling objects to make use of delegates/events
 * while still depending only on each other's UInterfaces. Normally, Blueprint does not support binding to delegates on
 * an object through a UInterface unless the object is cast to a concrete type, but that couples the class using the
 * object to only that concrete implementation of the interface.
 *
 * The contract of objects that implement this interface ("Events Emitters") is that they must implement at least these
 * two methods:
 *   1. GetEvents() - Should be a BlueprintCallable method. Must return a specific, concrete UObject that has only
 *      dynamic multicast delegates and no other logic, properties, methods, or UFunctions. Since the return type of
 *      this method is specific to each Events Emitter, the exact signature of this method should be defined in
 *      the primary UInterface of the Events Emitter. Blueprints can bind delegates to this object.
 *
 *   2. GetGenericEventsObject() - Should NOT be a BlueprintCallable method. Must return the same object as GetEvents(),
 *      but as a non-specific, generic UObject. The signature of this method is defined by this interface. This method
 *      is used internally by the editor to expose delegates of the Events Object as though they were events of the
 *      Events Emitter, to make it easier to use Events Emitter following this Events Emitter pattern.
 */
class OPENPF2GAMEFRAMEWORK_API IPF2EventEmitterInterface : public IInterface
{
	GENERATED_BODY()

public:
	// =================================================================================================================
	// Public Static Methods
	// =================================================================================================================
	/**
	 * Gets the UClass of an events object returned by the CDO of the given UClass.
	 *
	 * This is only useful for classes that implement the IPF2EventEmitterInterface.
	 *
	 * This is null safe. If Class is a null pointer, the result will be a null pointer.
	 *
	 * @param Class
	 *	The class for which an events object type is desired.
	 *
	 * @return
	 *	If given a non-null class that implements the IPF2EventEmitterInterface, a pointer to the UClass describing the
	 *	type of events objects the CDO of the given class will return for delegate bindings.
	 */
	static UClass* GetEventsClassOfCDO(const UClass* Class);

	/**
	 * Gets the UClass of the events object returned by the given object instance.
	 *
	 * This is only useful for objects that implement the IPF2EventEmitterInterface.
	 *
	 * This is null safe. If Object is a null pointer, the result will be a null pointer.
	 *
	 * @param Object
	 *	The object for which an events object type is desired.
	 *
	 * @return
	 *	If given a non-null object that implements the IPF2EventEmitterInterface, a pointer to the UClass describing the
	 *	type of events objects that the given object returned for delegate bindings.
	 */
	static UClass* GetEventsClassOfObject(const UObject* Object);

	/**
	 * Gets a sample events object based on the CDO of the given UClass.
	 *
	 * This is only useful for classes that implement the IPF2EventEmitterInterface.
	 *
	 * This is null safe. If Class is a null pointer, the result will be a null pointer.
	 *
	 * @param Class
	 *	The class for which a sample events object is desired.
	 *
	 * @return
	 *	If given a non-null class that implements the IPF2EventEmitterInterface, a pointer to a sample events object
	 *	that the CDO of the given class has returned for delegate bindings.
	 */
	static UObject* GetEventsOfCDO(const UClass* Class);

	/**
	 * Gets the events object returned by the given object instance.
	 *
	 * This is only useful for objects that implement the IPF2EventEmitterInterface.
	 *
	 * This is null safe. If Object is a null pointer, the result will be a null pointer.
	 *
	 * @param Object
	 *	The object for which an events object is desired.
	 *
	 * @return
	 *	If given a non-null object that implements the IPF2EventEmitterInterface, a pointer to the events object that
	 *	the given object returned for delegate bindings.
	 */
	static UObject* GetEventsOfObject(const UObject* Object);

	// =================================================================================================================
	// Public Instance Methods
	// =================================================================================================================
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

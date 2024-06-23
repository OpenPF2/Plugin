// OpenPF2 for UE Game Logic, Copyright 2022-2024, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#pragma once

#include <UObject/Interface.h>

#include "PF2LogIdentifiableInterface.generated.h"

UINTERFACE(MinimalAPI, meta=(CannotImplementInterfaceInBlueprint))
class UPF2LogIdentifiableInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * An interface for objects that provide a unique identifier for logging.
 *
 * This is favored instead of Unreal Engine's native GetName() or GetFullName() methods to give objects greater control
 * over how they appear in logs specifically. The name or full name could either be not specific enough or the
 * opposite -- too verbose -- to be useful.
 */
class OPENPF2GAMEFRAMEWORK_API IPF2LogIdentifiableInterface
{
	GENERATED_BODY()

public:
	// =================================================================================================================
	// Public Static Methods
	// =================================================================================================================
	/**
	 * Returns a unique identifier for the given object, for logging and debugging purposes.
	 *
	 * The ID will be obtained via the GetIdForLogs() interface method if the given object implements the
	 * PF2LogIdentifiableInterface. Otherwise, the ID will be obtained via the GetFullName() method. If the object is
	 * null, the string "(null)" will be returned.
	 *
	 * @param Object
	 *	The object for which an ID for logs is desired. This may be null.
	 *
	 * @return
	 *	An identifier to use when identifying the given object in logs.
	 */
	FORCEINLINE static FString GetIdForLogs(UObject* Object)
	{
		FString                             IdForLogs;
		const IPF2LogIdentifiableInterface* LogIdentifiableIntf = Cast<IPF2LogIdentifiableInterface>(Object);

		if (LogIdentifiableIntf == nullptr)
		{
			if (Object == nullptr)
			{
				IdForLogs = TEXT("(null)");
			}
			else
			{
				IdForLogs = Object->GetFullName();
			}
		}
		else
		{
			IdForLogs = LogIdentifiableIntf->GetIdForLogs();
		}

		return IdForLogs;
	}

	// =================================================================================================================
	// Public Methods
	// =================================================================================================================
	/**
	 * Returns a unique identifier for this object, for logging and debugging purposes.
	 *
	 * @return
	 *	A unique identifier for object in debug logs.
	 */
	UFUNCTION(BlueprintCallable, Category="OpenPF2|Utility")
	virtual FString GetIdForLogs() const = 0;
};

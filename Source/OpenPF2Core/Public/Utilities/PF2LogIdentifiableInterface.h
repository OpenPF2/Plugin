// OpenPF2 for UE Game Logic, Copyright 2021, Guy Elsmore-Paddock. All Rights Reserved.
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
 */
class OPENPF2CORE_API IPF2LogIdentifiableInterface
{
	GENERATED_BODY()

public:
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

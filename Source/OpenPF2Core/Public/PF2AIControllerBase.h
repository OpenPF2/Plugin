// OpenPF2 for UE Game Logic, Copyright 2022-2023, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
//
// Portions of this code were adapted from or inspired by the "Real-Time Strategy Plugin for Unreal Engine 4" by Nick
// Pruehs, provided under the MIT License. Copyright (c) 2017 Nick Pruehs.

#pragma once

#include <AIController.h>

#include "PF2AIControllerInterface.h"

#include "PF2AIControllerBase.generated.h"

// =====================================================================================================================
// Normal Declarations
// =====================================================================================================================
/**
 * Default base class for OpenPF2 AI Controllers.
 *
 * @see IPF2AIControllerInterface
 */
UCLASS(Abstract)
// ReSharper disable once CppClassCanBeFinal
class OPENPF2CORE_API APF2AIControllerBase : public AAIController, public IPF2AIControllerInterface
{
	GENERATED_BODY()

public:
	// =================================================================================================================
	// Public Methods - IPF2LogIdentifiableInterface Implementation
	// =================================================================================================================
	virtual FString GetIdForLogs() const override;
};

// OpenPF2 Game Framework for Unreal Engine, Copyright 2023-2024, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#pragma once

#include <Components/ActorComponent.h>

#include "Utilities/PF2LogIdentifiableInterface.h"

#include "PF2ActorComponentBase.generated.h"

// =====================================================================================================================
// Normal Declarations
// =====================================================================================================================
/**
 * Abstract base class for actor components in OpenPF2.
 */
UCLASS(Abstract, ClassGroup="OpenPF2-Characters")
class OPENPF2GAMEFRAMEWORK_API UPF2ActorComponentBase :
	public UActorComponent,
	public IPF2LogIdentifiableInterface
{
	GENERATED_BODY()

public:
	// =================================================================================================================
	// Public Methods - IPF2LogIdentifiableInterface Implementation
	// =================================================================================================================
	virtual FString GetIdForLogs() const override;
};

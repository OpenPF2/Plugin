// OpenPF2 for UE Game Logic, Copyright 2023, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#pragma once

#include <Engine/DataAsset.h>

#include "PF2ItemInterface.h"
#include "PF2Item.generated.h"

/**
 * Primary data class for items a character can carry in inventory.
 *
 * This is the top-most C++ base class for items, but there are several sub-classes for more specific item types,
 * including weapons.
 *
 * (Though this is an abstract base class, it does not have the "Base" suffix in its name because the asset manager uses
 * the name of the closest native parent class as the asset type).
 */
UCLASS(Abstract)
class OPENPF2CORE_API UPF2Item : public UPrimaryDataAsset, public IPF2ItemInterface
{
	GENERATED_BODY()

public:
	// =================================================================================================================
	// Public Methods - IPF2ItemInterface Implementation
	// =================================================================================================================
	virtual FPrimaryAssetId GetPrimaryAssetId() override;
	virtual UDataAsset* ToDataAsset() override;

	// =================================================================================================================
	// Public Methods - IPF2LogIdentifiableInterface Implementation
	// =================================================================================================================
	virtual FString GetIdForLogs() const override;
};

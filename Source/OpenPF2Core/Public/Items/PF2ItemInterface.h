// OpenPF2 for UE Game Logic, Copyright 2023, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#pragma once

#include <Engine/DataAsset.h>

#include "Utilities/PF2LogIdentifiableInterface.h"

#include "PF2ItemInterface.generated.h"

UINTERFACE(NotBlueprintable)
class UPF2ItemInterface : public UPF2LogIdentifiableInterface
{
    GENERATED_BODY()
};

/**
 * An interface for OpenPF2-compatible items that characters can carry in inventory.
 */
class OPENPF2CORE_API IPF2ItemInterface : public IPF2LogIdentifiableInterface
{
    GENERATED_BODY()

public:
    /**
	 * Gets the type-name pair representing the primary asset ID for this item.
     *
     * @return
     *	The primary asset ID of this item.
     */
    UFUNCTION(BlueprintCallable, Category="OpenPF2|Items")
	virtual FPrimaryAssetId GetPrimaryAssetId() = 0;

	/**
	 * Gets the data asset that is implementing this interface.
	 *
	 * @return
	 *	This item, as a data asset.
	 */
	UFUNCTION(BlueprintCallable, Category="OpenPF2|Items")
	virtual UDataAsset* ToDataAsset() = 0;
};

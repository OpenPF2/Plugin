// OpenPF2 for UE Game Logic, Copyright 2021-2023, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#pragma once

#include <UObject/Interface.h>

#include "PF2WeaponInterface.generated.h"

// =====================================================================================================================
// Forward Declarations (to minimize header dependencies)
// =====================================================================================================================
class APF2DamageCauseWrapper;

// =====================================================================================================================
// Normal Declarations
// =====================================================================================================================
UINTERFACE()
class UPF2WeaponInterface : public UInterface
{
    GENERATED_BODY()
};

/**
 * An interface for OpenPF2-compatible Weapons.
 */
class OPENPF2CORE_API IPF2WeaponInterface
{
    GENERATED_BODY()

public:
    /**
     * Converts this weapon into an actor that can represent a "damage causer" for replication.
     *
     * @return
     *	This instance, wrapped as a damage causer.
     */
	UFUNCTION(BlueprintCallable, Category="OpenPF2|Items|Weapons")
    virtual APF2DamageCauseWrapper* ToDamageCauser() = 0;

};

// OpenPF2 for UE Game Logic, Copyright 2022, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#pragma once

#include <GameplayAbilitySpec.h>

#include "PF2CharacterControllerInterface.h"

#include "PF2AIControllerInterface.generated.h"

// =====================================================================================================================
// Normal Declarations
// =====================================================================================================================
UINTERFACE(MinimalAPI, BlueprintType, meta=(CannotImplementInterfaceInBlueprint))
class UPF2AIControllerInterface : public UPF2CharacterControllerInterface
{
	GENERATED_BODY()
};

/**
 * An interface for OpenPF2-compatible AI controllers.
 */
class OPENPF2CORE_API IPF2AIControllerInterface : public IPF2CharacterControllerInterface
{
	GENERATED_BODY()
};

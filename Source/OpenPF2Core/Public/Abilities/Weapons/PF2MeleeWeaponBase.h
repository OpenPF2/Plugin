// OpenPF2 for UE Game Logic, Copyright 2021, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#pragma once

#include "Abilities/Weapons/PF2WeaponBase.h"

#include "PF2MeleeWeaponBase.generated.h"

/**
 * Base class for weapons that a character can use to attack another character within reach.
 *
 * This is the top-most C++ base class for melee weapons, but there are several Blueprint sub-classes of this class that
 * offer functionality that tends to be a more complete fit for your own melee weapon implementations.
 */
UCLASS(Abstract)
// ReSharper disable once CppClassCanBeFinal
class OPENPF2CORE_API UPF2MeleeWeaponBase : public UPF2WeaponBase
{
	GENERATED_BODY()
};

// OpenPF2 for UE Game Logic, Copyright 2021, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#pragma once

#include "PF2AbilityType.generated.h"

/**
 * Enumeration outlining the abilities each character has.
 */
UENUM()
enum class EPF2AbilityType : uint8
{
	Charisma,
	Constitution,
	Dexterity,
	Intelligence,
	Strength,
	Wisdom,
};

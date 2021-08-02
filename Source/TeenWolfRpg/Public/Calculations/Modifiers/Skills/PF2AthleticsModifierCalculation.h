﻿// OpenPF2 for UE Game Logic, Copyright 2021, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#pragma once

#include <CoreMinimal.h>

#include "Calculations/Modifiers/PF2ModifierCalculationBase.h"
#include "PF2AthleticsModifierCalculation.generated.h"

/**
 * MMC that calculates the proficiency a character has in Athletics skill.
 */
UCLASS()
class TEENWOLFRPG_API UPF2AthleticsModifierCalculation : public UPF2ModifierCalculationBase
{
	GENERATED_BODY()

public:
	explicit UPF2AthleticsModifierCalculation();
};
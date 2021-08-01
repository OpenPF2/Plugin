// OpenPF2 for UE Game Logic, Copyright 2021, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#pragma once

#include <CoreMinimal.h>

#include "Calculations/Modifiers/RPGModifierCalculationBase.h"
#include "RPGLore1ModifierCalculation.generated.h"

/**
 * MMC that calculates the proficiency a character has in Lore 1 skill.
 */
UCLASS()
class TEENWOLFRPG_API URPGLore1ModifierCalculation : public URPGModifierCalculationBase
{
	GENERATED_BODY()

public:
	explicit URPGLore1ModifierCalculation();
};

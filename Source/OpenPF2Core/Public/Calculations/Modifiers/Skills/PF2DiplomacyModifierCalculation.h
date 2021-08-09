// OpenPF2 for UE Game Logic, Copyright 2021, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#pragma once

#include <CoreMinimal.h>

#include "Calculations/Modifiers/PF2ModifierCalculationBase.h"
#include "PF2DiplomacyModifierCalculation.generated.h"

/**
 * MMC that calculates the proficiency a character has in Diplomacy skill.
 */
UCLASS()
class OPENPF2CORE_API UPF2DiplomacyModifierCalculation : public UPF2ModifierCalculationBase
{
	GENERATED_BODY()

public:
	explicit UPF2DiplomacyModifierCalculation();
};

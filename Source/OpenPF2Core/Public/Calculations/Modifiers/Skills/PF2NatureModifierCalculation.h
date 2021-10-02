// OpenPF2 for UE Game Logic, Copyright 2021, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#pragma once

#include <CoreMinimal.h>

#include "Calculations/Modifiers/PF2SimpleTemlModifierCalculationBase.h"
#include "PF2NatureModifierCalculation.generated.h"

/**
 * MMC that calculates the proficiency a character has in Nature skill.
 */
UCLASS()
class OPENPF2CORE_API UPF2NatureModifierCalculation : public UPF2SimpleTemlModifierCalculationBase
{
	GENERATED_BODY()

public:
	// =================================================================================================================
	// Constructors
	// =================================================================================================================
	explicit UPF2NatureModifierCalculation();
};

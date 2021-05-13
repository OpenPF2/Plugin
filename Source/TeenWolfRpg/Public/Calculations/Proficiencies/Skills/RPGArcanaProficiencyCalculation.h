// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include <CoreMinimal.h>

#include "Calculations/Proficiencies/RPGProficiencyCalculationBase.h"
#include "RPGArcanaProficiencyCalculation.generated.h"

/**
* MMC that calculates the proficiency a character has in Arcana skill.
*/
UCLASS()
class TEENWOLFRPG_API URPGArcanaProficiencyCalculation : public URPGProficiencyCalculationBase
{
	GENERATED_BODY()

public:
	explicit URPGArcanaProficiencyCalculation();
};

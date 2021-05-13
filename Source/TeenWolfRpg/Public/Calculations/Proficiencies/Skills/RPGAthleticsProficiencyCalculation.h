// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include <CoreMinimal.h>

#include "Calculations/Proficiencies/RPGProficiencyCalculationBase.h"
#include "RPGAthleticsProficiencyCalculation.generated.h"

/**
* MMC that calculates the proficiency a character has in Athletics skill.
*/
UCLASS()
class TEENWOLFRPG_API URPGAthleticsProficiencyCalculation : public URPGProficiencyCalculationBase
{
	GENERATED_BODY()

public:
	explicit URPGAthleticsProficiencyCalculation();
};

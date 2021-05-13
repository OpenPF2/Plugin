// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include <CoreMinimal.h>

#include "Calculations/Proficiencies/RPGProficiencyCalculationBase.h"
#include "RPGAcrobaticsProficiencyCalculation.generated.h"

/**
* MMC that calculates the proficiency a character has in Acrobatics skill.
*/
UCLASS()
class TEENWOLFRPG_API URPGAcrobaticsProficiencyCalculation : public URPGProficiencyCalculationBase
{
	GENERATED_BODY()

public:
	explicit URPGAcrobaticsProficiencyCalculation();
};

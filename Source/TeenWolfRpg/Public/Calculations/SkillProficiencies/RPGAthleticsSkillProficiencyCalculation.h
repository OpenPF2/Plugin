// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include <CoreMinimal.h>

#include "RPGSkillProficiencyCalculationBase.h"
#include "RPGAthleticsSkillProficiencyCalculation.generated.h"

/**
* MMC that calculates the proficiency a character has in Athletics skill.
*/
UCLASS()
class TEENWOLFRPG_API URPGAthleticsSkillProficiencyCalculation : public URPGSkillProficiencyCalculationBase
{
	GENERATED_BODY()

public:
	explicit URPGAthleticsSkillProficiencyCalculation();
};

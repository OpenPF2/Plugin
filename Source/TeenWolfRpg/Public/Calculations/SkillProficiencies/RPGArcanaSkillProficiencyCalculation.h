// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include <CoreMinimal.h>

#include "RPGSkillProficiencyCalculationBase.h"
#include "RPGArcanaSkillProficiencyCalculation.generated.h"

/**
* MMC that calculates the proficiency a character has in Arcana skill.
*/
UCLASS()
class TEENWOLFRPG_API URPGArcanaSkillProficiencyCalculation : public URPGSkillProficiencyCalculationBase
{
	GENERATED_BODY()

public:
	explicit URPGArcanaSkillProficiencyCalculation();
};

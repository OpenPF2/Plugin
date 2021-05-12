// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include <CoreMinimal.h>

#include "RPGSkillProficiencyCalculationBase.h"
#include "RPGAcrobaticsSkillProficiencyCalculation.generated.h"

/**
* MMC that calculates the proficiency a character has in Acrobatics skill.
*/
UCLASS()
class TEENWOLFRPG_API URPGAcrobaticsSkillProficiencyCalculation : public URPGSkillProficiencyCalculationBase
{
	GENERATED_BODY()

public:
	explicit URPGAcrobaticsSkillProficiencyCalculation();
};

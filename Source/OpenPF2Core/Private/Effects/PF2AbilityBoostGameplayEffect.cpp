// OpenPF2 for UE Game Logic, Copyright 2021, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "Effects/PF2AbilityBoostGameplayEffect.h"
#include "Executions/PF2AbilityBoostExecution.h"

void UPF2AbilityBoostGameplayEffect::PostLoad()
{
	Super::PostLoad();

	this->PopulateExecutions();
}

void UPF2AbilityBoostGameplayEffect::PopulateExecutions()
{
	FGameplayEffectExecutionDefinition			AbilityBoostCalculationExecution;
	FGameplayEffectAttributeCaptureDefinition	TargetAbilityCaptureDefinition;

	TargetAbilityCaptureDefinition.AttributeToCapture = this->GetTargetAbilityAttribute();
	TargetAbilityCaptureDefinition.AttributeSource	  = EGameplayEffectAttributeCaptureSource::Target;

	AbilityBoostCalculationExecution.CalculationClass = UPF2AbilityBoostExecution::StaticClass();

	this->Executions.Empty(this->BoostCount);

	for (uint8 ExecutionCount = 0; ExecutionCount < this->BoostCount; ++ExecutionCount)
	{
		this->Executions.Add(AbilityBoostCalculationExecution);
	}
}

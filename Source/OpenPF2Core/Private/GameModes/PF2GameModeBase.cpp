// OpenPF2 for UE Game Logic, Copyright 2021, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "GameModes/PF2GameModeBase.h"

#include "PF2EnumUtilities.h"
#include "GameModes/PF2ModeOfPlayRuleSet.h"

void APF2GameModeBase::StartEncounterMode()
{
	this->AttemptModeOfPlaySwitch(EPF2ModeOfPlayType::Encounter);
}

void APF2GameModeBase::StartExplorationMode()
{
	this->AttemptModeOfPlaySwitch(EPF2ModeOfPlayType::Exploration);
}

void APF2GameModeBase::StartDowntimeMode()
{
	this->AttemptModeOfPlaySwitch(EPF2ModeOfPlayType::Downtime);
}

void APF2GameModeBase::BeginPlay()
{
	Super::BeginPlay();

	// Start off in exploration mode.
	this->AttemptModeOfPlaySwitch(EPF2ModeOfPlayType::Exploration);
}

void APF2GameModeBase::AttemptModeOfPlaySwitch(const EPF2ModeOfPlayType NewMode)
{
	IPF2GameStateInterface* Pf2GameState = this->GetGameState<IPF2GameStateInterface>();

	if (Pf2GameState != nullptr)
	{
		const IPF2ModeOfPlayRuleSet* RuleSet =
			Cast<IPF2ModeOfPlayRuleSet>(Pf2GameState->GetModeOfPlayRuleSet().GetObject());

		bool CanTransition;

		if (Pf2GameState->GetModeOfPlay() == EPF2ModeOfPlayType::None)
		{
			// We're not in any mode.
			CanTransition = true;
		}
		else if (RuleSet == nullptr)
		{
			UE_LOG(
				LogPf2Core,
				Error,
				TEXT("Cannot transition from current mode of play (%s) to new mode (%s) because there is no loaded rule set."),
				*PF2EnumUtilities::ToString(Pf2GameState->GetModeOfPlay()),
				*PF2EnumUtilities::ToString(NewMode)
			);

			CanTransition = false;
		}
		else if (!RuleSet->CanTransitionTo(Pf2GameState, NewMode))
		{
			UE_LOG(
				LogPf2Core,
				Warning,
				TEXT("Refusing to transition from current mode of play (%s) to new mode (%s) because loaded rule set does not allow the transition."),
				*PF2EnumUtilities::ToString(Pf2GameState->GetModeOfPlay()),
				*PF2EnumUtilities::ToString(NewMode)
			);

			CanTransition = false;
		}
		else
		{
			CanTransition = true;
		}

		if (CanTransition)
		{
			const TScriptInterface<IPF2ModeOfPlayRuleSet> NewRuleSet = this->CreateModeOfPlayRuleSet(NewMode);

			Pf2GameState->SwitchModeOfPlay(NewMode, NewRuleSet);
		}
	}
}

// OpenPF2 for UE Game Logic, Copyright 2021, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "GameModes/PF2GameModeBase.h"

#include "PF2EnumUtilities.h"
#include "GameModes/PF2ModeOfPlayRuleSet.h"

TScriptInterface<IPF2ModeOfPlayRuleSet> APF2GameModeBase::CreateModeOfPlayRuleSet(const EPF2ModeOfPlayType ModeOfPlay)
{
	TScriptInterface<IPF2ModeOfPlayRuleSet> RuleSetWrapper;

	if (this->ModeRuleSets.Contains(ModeOfPlay))
	{
		const UClass* const RuleSetType = this->ModeRuleSets[ModeOfPlay];
		UObject*            NewRuleSet  = NewObject<UObject>(this, RuleSetType);

		RuleSetWrapper = TScriptInterface<IPF2ModeOfPlayRuleSet>(NewRuleSet);
	}

	return RuleSetWrapper;
}

void APF2GameModeBase::RequestEncounterMode()
{
	this->AttemptModeOfPlaySwitch(EPF2ModeOfPlayType::Encounter);
}

void APF2GameModeBase::RequestExplorationMode()
{
	this->AttemptModeOfPlaySwitch(EPF2ModeOfPlayType::Exploration);
}

void APF2GameModeBase::RequestDowntimeMode()
{
	this->AttemptModeOfPlaySwitch(EPF2ModeOfPlayType::Downtime);
}

void APF2GameModeBase::BeginPlay()
{
	Super::BeginPlay();

	// Start off in exploration mode.
	this->AttemptModeOfPlaySwitch(EPF2ModeOfPlayType::Exploration);
}

void APF2GameModeBase::AttemptModeOfPlaySwitch(const EPF2ModeOfPlayType NewModeOfPlay)
{
	IPF2GameStateInterface*                        Pf2GameStateInterface = this->GetGameState<IPF2GameStateInterface>();
	const TScriptInterface<IPF2GameStateInterface> Pf2GameState          = Cast<UObject>(Pf2GameStateInterface);

	if (Pf2GameState != nullptr)
	{
		const EPF2ModeOfPlayType                      OldModeOfPlay    = Pf2GameState->GetModeOfPlay();
		const TScriptInterface<IPF2ModeOfPlayRuleSet> OldRuleSet       = Pf2GameState->GetModeOfPlayRuleSet();
		UObject*                                      OldRuleSetObject = OldRuleSet.GetObject();

		bool CanTransition;

		if (OldModeOfPlay == EPF2ModeOfPlayType::None)
		{
			// We're not in any mode.
			CanTransition = true;
		}
		else if (OldRuleSetObject == nullptr)
		{
			UE_LOG(
				LogPf2Core,
				Error,
				TEXT("Cannot transition from current mode of play (%s) to new mode (%s) because there is no loaded rule set."),
				*PF2EnumUtilities::ToString(Pf2GameState->GetModeOfPlay()),
				*PF2EnumUtilities::ToString(NewModeOfPlay)
			);

			CanTransition = false;
		}
		else if (!OldRuleSet->Execute_CanTransitionTo(OldRuleSetObject, Pf2GameState, NewModeOfPlay))
		{
			UE_LOG(
				LogPf2Core,
				Warning,
				TEXT("Refusing to transition from current mode of play (%s) to new mode (%s) because loaded rule set does not allow the transition."),
				*PF2EnumUtilities::ToString(Pf2GameState->GetModeOfPlay()),
				*PF2EnumUtilities::ToString(NewModeOfPlay)
			);

			CanTransition = false;
		}
		else
		{
			CanTransition = true;
		}

		if (CanTransition)
		{
			const TScriptInterface<IPF2ModeOfPlayRuleSet> NewRuleSet = this->CreateModeOfPlayRuleSet(NewModeOfPlay);

			UObject* const NewRuleSetObject = NewRuleSet.GetObject();

			if (OldRuleSetObject != nullptr)
			{
				OldRuleSet->Execute_OnModeOfPlayEnd(OldRuleSetObject, OldModeOfPlay);
			}

			Pf2GameState->SwitchModeOfPlay(NewModeOfPlay, NewRuleSet);

			if (NewRuleSetObject != nullptr)
			{
				NewRuleSet->Execute_OnModeOfPlayStart(NewRuleSetObject, NewModeOfPlay);
			}
		}
	}
}

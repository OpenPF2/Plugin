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

void APF2GameModeBase::Tick(const float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	IPF2GameStateInterface* Pf2GameState = this->GetGameState<IPF2GameStateInterface>();

	if (Pf2GameState != nullptr)
	{
		const TScriptInterface<IPF2ModeOfPlayRuleSet> RuleSet = Pf2GameState->GetModeOfPlayRuleSet();

		if (RuleSet != nullptr)
		{
			RuleSet->Execute_OnTick(RuleSet.GetObject(), DeltaSeconds);
		}
	}
}

void APF2GameModeBase::AttemptModeOfPlaySwitch(const EPF2ModeOfPlayType NewModeOfPlay)
{
	IPF2GameStateInterface*                        Pf2GameStateInterface = this->GetGameState<IPF2GameStateInterface>();
	const TScriptInterface<IPF2GameStateInterface> Pf2GameState          = Cast<UObject>(Pf2GameStateInterface);

	if (Pf2GameState == nullptr)
	{
		UE_LOG(
			LogPf2Core,
			Error,
			TEXT("Cannot transition to new mode of play (%s) because current game state is not compatible with PF2."),
			*PF2EnumUtilities::ToString(NewModeOfPlay)
		);
	}
	else
	{
		const EPF2ModeOfPlayType                      OldModeOfPlay = Pf2GameState->GetModeOfPlay();
		const TScriptInterface<IPF2ModeOfPlayRuleSet> OldRuleSet    = Pf2GameState->GetModeOfPlayRuleSet();
		bool                                          CanTransition;

		if (OldModeOfPlay == EPF2ModeOfPlayType::None)
		{
			// We're not in any mode.
			CanTransition = true;
		}
		else if (OldRuleSet == nullptr)
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
		else if (!OldRuleSet->Execute_CanTransitionTo(OldRuleSet.GetObject(), Pf2GameState, NewModeOfPlay))
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
			this->ForceSwitchModeOfPlay(NewModeOfPlay);
		}
	}
}

void APF2GameModeBase::ForceSwitchModeOfPlay(const EPF2ModeOfPlayType NewModeOfPlay)
{
	IPF2GameStateInterface*                        Pf2GameStateInterface = this->GetGameState<IPF2GameStateInterface>();
	const TScriptInterface<IPF2GameStateInterface> Pf2GameState          = Cast<UObject>(Pf2GameStateInterface);

	if (Pf2GameState == nullptr)
	{
		UE_LOG(
			LogPf2Core,
			Error,
			TEXT("Cannot transition to new mode of play (%s) because current game state is not compatible with PF2."),
			*PF2EnumUtilities::ToString(NewModeOfPlay)
		);
	}
	else
	{
		const EPF2ModeOfPlayType                      OldModeOfPlay    = Pf2GameState->GetModeOfPlay();
		const TScriptInterface<IPF2ModeOfPlayRuleSet> OldRuleSet       = Pf2GameState->GetModeOfPlayRuleSet();
		const TScriptInterface<IPF2ModeOfPlayRuleSet> NewRuleSet       = this->CreateModeOfPlayRuleSet(NewModeOfPlay);

		if (OldRuleSet != nullptr)
		{
			OldRuleSet->Execute_OnModeOfPlayEnd(OldRuleSet.GetObject(), OldModeOfPlay);
		}

		Pf2GameState->SwitchModeOfPlay(NewModeOfPlay, NewRuleSet);

		if (NewRuleSet != nullptr)
		{
			NewRuleSet->Execute_OnModeOfPlayStart(NewRuleSet.GetObject(), NewModeOfPlay);
		}
	}
}

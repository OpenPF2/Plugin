// OpenPF2 for UE Game Logic, Copyright 2021, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "GameModes/PF2GameModeBase.h"

#include "PF2CharacterInterface.h"
#include "PF2GameStateInterface.h"
#include "PF2QueuedActionInterface.h"

#include "GameModes/PF2ModeOfPlayRuleSetInterface.h"
#include "Utilities/PF2EnumUtilities.h"

APF2GameModeBase::APF2GameModeBase()
{
	this->PrimaryActorTick.bCanEverTick = true;
}

TScriptInterface<IPF2ModeOfPlayRuleSetInterface> APF2GameModeBase::CreateModeOfPlayRuleSet(
	const EPF2ModeOfPlayType ModeOfPlay)
{
	TScriptInterface<IPF2ModeOfPlayRuleSetInterface> RuleSetWrapper;

	if (this->ModeRuleSets.Contains(ModeOfPlay))
	{
		const UClass* const RuleSetType = this->ModeRuleSets[ModeOfPlay];
		UObject*            NewRuleSet  = NewObject<UObject>(this, RuleSetType);

		RuleSetWrapper = TScriptInterface<IPF2ModeOfPlayRuleSetInterface>(NewRuleSet);
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

void APF2GameModeBase::AddCharacterToEncounter(const TScriptInterface<IPF2CharacterInterface>& Character)
{
	const TScriptInterface<IPF2ModeOfPlayRuleSetInterface> RuleSet = this->GetModeOfPlayRuleSet();

	if (RuleSet == nullptr)
	{
		UE_LOG(
			LogPf2CoreEncounters,
			Error,
			TEXT("No MoPRS is set. Ignoring request to add character (%s) to encounter."),
			*(Character->GetCharacterName().ToString())
		);
	}
	else
	{
		RuleSet->Execute_OnCharacterAddedToEncounter(RuleSet.GetObject(), Character);
	}
}

void APF2GameModeBase::RemoveCharacterFromEncounter(const TScriptInterface<IPF2CharacterInterface>& Character)
{
	const TScriptInterface<IPF2ModeOfPlayRuleSetInterface> RuleSet = this->GetModeOfPlayRuleSet();

	if (RuleSet == nullptr)
	{
		UE_LOG(
			LogPf2CoreEncounters,
			Error,
			TEXT("No MoPRS is set. Ignoring request to remove character (%s) from encounter."),
			*(Character->GetCharacterName().ToString())
		);
	}
	else
	{
		RuleSet->Execute_OnCharacterRemovedFromEncounter(RuleSet.GetObject(), Character);
	}
}

FPF2QueuedActionHandle APF2GameModeBase::QueueActionForInitiativeTurn(
	TScriptInterface<IPF2CharacterInterface>&    Character,
	TScriptInterface<IPF2QueuedActionInterface>& Action,
	EPF2ActionQueueResult&                       OutQueueResult)
{
	FPF2QueuedActionHandle                                 Result;
	const TScriptInterface<IPF2ModeOfPlayRuleSetInterface> RuleSet = this->GetModeOfPlayRuleSet();

	if (RuleSet == nullptr)
	{
		UE_LOG(
			LogPf2CoreEncounters,
			Error,
			TEXT("No MoPRS is set. Performing action (%s) without queuing."),
			*(Action->GetActionName().ToString())
		);

		Action->PerformAction();
	}
	else
	{
		Result = RuleSet->Execute_OnQueueAction(RuleSet.GetObject(), Character, Action, OutQueueResult);
	}

	return Result;
}

void APF2GameModeBase::CancelActionQueuedForInitiativeTurnByHandle(const FPF2QueuedActionHandle ActionHandle)
{
	const TScriptInterface<IPF2ModeOfPlayRuleSetInterface> RuleSet = this->GetModeOfPlayRuleSet();

	if (RuleSet == nullptr)
	{
		UE_LOG(
			LogPf2CoreEncounters,
			Error,
			TEXT("No MoPRS is set. Ignoring request to remove action (%s, handle: %d) from queue."),
			*(ActionHandle.ActionName.ToString()),
			ActionHandle.HandleId
		);
	}
	else
	{
		RuleSet->Execute_OnCancelQueuedActionByHandle(RuleSet.GetObject(), ActionHandle);
	}
}

void APF2GameModeBase::CancelActionQueuedForInitiativeTurn(const TScriptInterface<IPF2CharacterInterface>&    Character,
                                                           const TScriptInterface<IPF2QueuedActionInterface>& Action)
{
	const TScriptInterface<IPF2ModeOfPlayRuleSetInterface> RuleSet = this->GetModeOfPlayRuleSet();

	if (RuleSet == nullptr)
	{
		UE_LOG(
			LogPf2CoreEncounters,
			Error,
			TEXT("No MoPRS is set. Ignoring request to remove action (%s) from queue."),
			*(Action->GetActionName().ToString())
		);
	}
	else
	{
		RuleSet->Execute_OnCancelQueuedAction(RuleSet.GetObject(), Character, Action);
	}
}

void APF2GameModeBase::BeginPlay()
{
	Super::BeginPlay();

	// Start off in exploration mode.
	this->AttemptModeOfPlaySwitch(EPF2ModeOfPlayType::Exploration);
}

void APF2GameModeBase::Tick(const float DeltaSeconds)
{
	const TScriptInterface<IPF2ModeOfPlayRuleSetInterface> RuleSet = this->GetModeOfPlayRuleSet();

	Super::Tick(DeltaSeconds);

	if (RuleSet != nullptr)
	{
		RuleSet->Execute_OnTick(RuleSet.GetObject(), DeltaSeconds);
	}
}

TScriptInterface<IPF2ModeOfPlayRuleSetInterface> APF2GameModeBase::GetModeOfPlayRuleSet()
{
	TScriptInterface<IPF2ModeOfPlayRuleSetInterface> RuleSet;
	IPF2GameStateInterface*                          Pf2GameState = this->GetGameState<IPF2GameStateInterface>();

	if (Pf2GameState == nullptr)
	{
		UE_LOG(
			LogPf2Core,
			Error,
			TEXT("Mode of Play Rule Set (MoPRS) support is not enabled because the current game state is not compatible with PF2.")
		);

		RuleSet = TScriptInterface<IPF2ModeOfPlayRuleSetInterface>();
	}
	else
	{
		RuleSet = Pf2GameState->GetModeOfPlayRuleSet();
	}

	return RuleSet;
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
		const EPF2ModeOfPlayType                               OldModeOfPlay  = Pf2GameState->GetModeOfPlay();
		const TScriptInterface<IPF2ModeOfPlayRuleSetInterface> OldRuleSet     = Pf2GameState->GetModeOfPlayRuleSet();
		bool                                                   bCanTransition;

		if (OldModeOfPlay == EPF2ModeOfPlayType::None)
		{
			// We're not in any mode.
			bCanTransition = true;
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

			bCanTransition = false;
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

			bCanTransition = false;
		}
		else
		{
			bCanTransition = true;
		}

		if (bCanTransition)
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
		const EPF2ModeOfPlayType                               OldModeOfPlay = Pf2GameState->GetModeOfPlay();
		const TScriptInterface<IPF2ModeOfPlayRuleSetInterface> OldRuleSet    = Pf2GameState->GetModeOfPlayRuleSet();
		const TScriptInterface<IPF2ModeOfPlayRuleSetInterface> NewRuleSet    = this->CreateModeOfPlayRuleSet(NewModeOfPlay);

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

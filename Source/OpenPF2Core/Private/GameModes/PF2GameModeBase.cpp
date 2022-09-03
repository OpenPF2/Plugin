﻿// OpenPF2 for UE Game Logic, Copyright 2021-2022, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
//
// Portions of this code were adapted from or inspired by the "Real-Time Strategy Plugin for Unreal Engine 4" by Nick
// Pruehs, provided under the MIT License. Copyright (c) 2017 Nick Pruehs.

#include "GameModes/PF2GameModeBase.h"

#include <EngineUtils.h>

#include "PF2CharacterInterface.h"
#include "PF2GameStateInterface.h"
#include "PF2OwnerTrackingInterface.h"
#include "PF2PartyInterface.h"
#include "PF2PlayerStateInterface.h"

#include "Commands/PF2CharacterCommandInterface.h"

#include "GameModes/PF2ModeOfPlayRuleSetInterface.h"

#include "Utilities/PF2EnumUtilities.h"
#include "Utilities/PF2InterfaceUtilities.h"

TScriptInterface<IPF2ModeOfPlayRuleSetInterface> APF2GameModeBase::CreateModeOfPlayRuleSet(
	const EPF2ModeOfPlayType ModeOfPlay)
{
	TScriptInterface<IPF2ModeOfPlayRuleSetInterface> RuleSetWrapper;

	if (this->ModeRuleSets.Contains(ModeOfPlay))
	{
		UClass* const RuleSetType = this->ModeRuleSets[ModeOfPlay];
		UObject*      NewRuleSet;

		// Rule sets are usually actors, but the interface doesn't strictly require them to be. We have to instantiate
		// them appropriately, since actors have to be added to the world (so that actor callbacks like BeginPlay are
		// invoked), while base UObjects don't.
		if (RuleSetType->IsChildOf(AActor::StaticClass()))
		{
			NewRuleSet = this->GetWorld()->SpawnActor(RuleSetType);
		}
		else
		{
			NewRuleSet = NewObject<UObject>(this, RuleSetType);
		}

		RuleSetWrapper = TScriptInterface<IPF2ModeOfPlayRuleSetInterface>(NewRuleSet);
	}

	return RuleSetWrapper;
}

void APF2GameModeBase::TransferCharacterOwnership(
	const TScriptInterface<IPF2CharacterInterface>        Character,
	const TScriptInterface<IPF2PlayerControllerInterface> ControllerOfNewOwner)
{
	TScriptInterface<IPF2PlayerStateInterface>   PlayerStateOfNewOwner;
	TScriptInterface<IPF2OwnerTrackingInterface> OwnerTracker;

	check(Character != nullptr);

	if (ControllerOfNewOwner == nullptr)
	{
		PlayerStateOfNewOwner = TScriptInterface<IPF2PlayerStateInterface>(nullptr);
	}
	else
	{
		PlayerStateOfNewOwner = ControllerOfNewOwner->GetPlayerState();
		check(PlayerStateOfNewOwner != nullptr);
	}

	OwnerTracker = Character->GetOwnerTrackingComponent();

	if (OwnerTracker == nullptr)
	{
		UE_LOG(
			LogPf2Core,
			Warning,
			TEXT("Character ('%s') lacks an owner tracking component, so it will not be able to respond properly to ownership changes."),
			*(ControllerOfNewOwner->GetIdForLogs()),
			*(Character->GetIdForLogs())
		);
	}
	else
	{
		const TScriptInterface<IPF2PlayerStateInterface> PlayerStateOfOldOwner = OwnerTracker->GetStateOfOwningPlayer();

		if (PlayerStateOfOldOwner != PlayerStateOfNewOwner)
		{
			if (PlayerStateOfOldOwner != nullptr)
			{
				PlayerStateOfOldOwner->ReleaseCharacter(Character);
			}

			OwnerTracker->SetOwningPlayerByState(PlayerStateOfNewOwner);
		}
	}

	if (PlayerStateOfNewOwner == nullptr)
	{
		UE_LOG(
			LogPf2Core,
			Verbose,
			TEXT("Character ('%s') is now no longer owned by any character."),
			*(Character->GetIdForLogs())
		);
	}
	else
	{
		UE_LOG(
			LogPf2Core,
			Verbose,
			TEXT("Player controller ('%s') now owns character ('%s')."),
			*(ControllerOfNewOwner->GetIdForLogs()),
			*(Character->GetIdForLogs())
		);

		PlayerStateOfNewOwner->GiveCharacter(Character);
	}

	// Set player controller as networking authority for the character.
	Character->ToActor()->SetOwner(ControllerOfNewOwner->ToPlayerController());
}

void APF2GameModeBase::SwitchPartyOfPlayer(const TScriptInterface<IPF2PlayerControllerInterface> PlayerController,
                                           const TScriptInterface<IPF2PartyInterface>            NewParty)
{
	const TScriptInterface<IPF2PlayerStateInterface> PlayerState = PlayerController->GetPlayerState();
	TScriptInterface<IPF2PartyInterface>             OldParty;

	check(PlayerState != nullptr);

	OldParty = PlayerState->GetParty();

	if (OldParty != NewParty)
	{
		for (const auto& Character : PlayerState->GetControllableCharacters())
		{
			PlayerState->ReleaseCharacter(Character);
		}

		// We already released all the characters, so this allows us to reuse the logic without duplicating it here.
		this->SwitchPartyOfPlayerAndOwnedCharacters(PlayerController, NewParty);
	}
}

void APF2GameModeBase::SwitchPartyOfPlayerAndOwnedCharacters(
	const TScriptInterface<IPF2PlayerControllerInterface> PlayerController,
	const TScriptInterface<IPF2PartyInterface>            NewParty)
{
	TScriptInterface<IPF2PlayerStateInterface> PlayerState;
	TScriptInterface<IPF2PartyInterface>       OldParty;

	check(PlayerController != nullptr);

	PlayerState = PlayerController->GetPlayerState();
	check(PlayerState != nullptr);

	OldParty = PlayerState->GetParty();

	if (OldParty != NewParty)
	{
		// Remove from old party, if there is one.
		if (OldParty != nullptr)
		{
			OldParty->RemovePlayerFromPartyByState(PlayerState);
		}

		PlayerState->SetParty(NewParty);

		// Associate all controllable characters with the new party.
		for (const auto& Character : PlayerState->GetControllableCharacters())
		{
			const TScriptInterface<IPF2OwnerTrackingInterface> OwnerTracker = Character->GetOwnerTrackingComponent();

			OwnerTracker->SetParty(NewParty);
		}

		// Notify the new party, if there is one.
		if (NewParty != nullptr)
		{
			NewParty->AddPlayerToPartyByState(PlayerState);
		}
	}
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
			TEXT("No MoPRS is set. Ignoring request to add character ('%s') to encounter."),
			*(Character->GetCharacterName().ToString())
		);
	}
	else
	{
		IPF2ModeOfPlayRuleSetInterface::Execute_BP_OnCharacterAddedToEncounter(RuleSet.GetObject(), Character);
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
			TEXT("No MoPRS is set. Ignoring request to remove character ('%s') from encounter."),
			*(Character->GetCharacterName().ToString())
		);
	}
	else
	{
		IPF2ModeOfPlayRuleSetInterface::Execute_BP_OnCharacterRemovedFromEncounter(RuleSet.GetObject(), Character);
	}
}

EPF2CommandExecuteOrQueueResult APF2GameModeBase::AttemptToExecuteOrQueueCommand(
		TScriptInterface<IPF2CharacterInterface>&        Character,
		TScriptInterface<IPF2CharacterCommandInterface>& Command)
{
	EPF2CommandExecuteOrQueueResult                        Result;
	const TScriptInterface<IPF2ModeOfPlayRuleSetInterface> RuleSet = this->GetModeOfPlayRuleSet();

	if (RuleSet == nullptr)
	{
		UE_LOG(
			LogPf2CoreEncounters,
			Error,
			TEXT("No MoPRS is set. Performing command ('%s') without queuing."),
			*(Command->GetCommandLabel().ToString())
		);

		Result =
			IPF2CharacterCommandInterface::ImmediateResultToExecuteOrQueueResult(Command->AttemptExecuteImmediately());
	}
	else
	{
		Result =
			IPF2ModeOfPlayRuleSetInterface::Execute_AttemptToExecuteOrQueueCommand(
				RuleSet.GetObject(),
				Character,
				Command
			);
	}

	return Result;
}

void APF2GameModeBase::BeginPlay()
{
	Super::BeginPlay();

	// Start off in exploration mode.
	this->AttemptModeOfPlaySwitch(EPF2ModeOfPlayType::Exploration);
}

void APF2GameModeBase::HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer)
{
	TScriptInterface<IPF2ModeOfPlayRuleSetInterface> RuleSet;

	this->AssignPlayerIndex(NewPlayer);
	Super::HandleStartingNewPlayer_Implementation(NewPlayer);

	RuleSet = this->GetModeOfPlayRuleSet();

	if (RuleSet != nullptr)
	{
		IPF2ModeOfPlayRuleSetInterface::Execute_BP_OnPlayableCharacterStarting(
			RuleSet.GetObject(),
			NewPlayer->GetCharacter()
		);
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

void APF2GameModeBase::AssignPlayerIndex(const APlayerController* PlayerController) const
{
	IPF2PlayerStateInterface* PlayerStateIntf = PlayerController->GetPlayerState<IPF2PlayerStateInterface>();

	if (PlayerStateIntf != nullptr)
	{
		const uint8 NextPlayerIndex = this->GetNextAvailablePlayerIndex();

		PlayerStateIntf->SetPlayerIndex(NextPlayerIndex);
	}
}

void APF2GameModeBase::AttemptModeOfPlaySwitch(const EPF2ModeOfPlayType NewModeOfPlay)
{
	const TScriptInterface<IPF2GameStateInterface> Pf2GameState =
		PF2InterfaceUtilities::ToScriptInterface(this->GetGameStateIntf());

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
			// This typically should not happen. If it does, then the game designer is missing a rule set mapping. By
			// default, we'll allow the transition since we have no rule set to veto it.
			UE_LOG(
				LogPf2Core,
				Warning,
				TEXT("There is no loaded rule set, so a requested transition from the current mode of play (%s) to a new mode of play (%s) has automatically been allowed."),
				*PF2EnumUtilities::ToString(OldModeOfPlay),
				*PF2EnumUtilities::ToString(NewModeOfPlay)
			);

			bCanTransition = true;
		}
		else if (!IPF2ModeOfPlayRuleSetInterface::Execute_CanTransitionTo(OldRuleSet.GetObject(), Pf2GameState, NewModeOfPlay))
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
	const TScriptInterface<IPF2GameStateInterface> Pf2GameState =
		PF2InterfaceUtilities::ToScriptInterface(this->GetGameStateIntf());

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
			AActor* OldRuleSetActor = Cast<AActor>(OldRuleSet.GetObject());

			IPF2ModeOfPlayRuleSetInterface::Execute_BP_OnModeOfPlayEnd(OldRuleSet.GetObject(), OldModeOfPlay);

			if (OldRuleSetActor != nullptr)
			{
				// Rule sets are usually actors, but the interface doesn't strictly require them to be. If the old rule
				// set was implemented as an actor, then we also need to remove it from the world.
				OldRuleSetActor->Destroy();
			}
		}

		Pf2GameState->SetModeOfPlay(NewModeOfPlay, NewRuleSet);

		if (NewRuleSet != nullptr)
		{
			IPF2ModeOfPlayRuleSetInterface::Execute_BP_OnModeOfPlayStart(NewRuleSet.GetObject(), NewModeOfPlay);
		}
	}
}

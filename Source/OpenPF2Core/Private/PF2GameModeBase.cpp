// OpenPF2 for UE Game Logic, Copyright 2021, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "PF2GameModeBase.h"

void APF2GameModeBase::StartEncounterMode()
{
	this->SwitchModeOfPlay(EPF2ModeOfPlay::Encounter);
}

void APF2GameModeBase::StartExplorationMode()
{
	this->SwitchModeOfPlay(EPF2ModeOfPlay::Exploration);
}

void APF2GameModeBase::StartDowntimeMode()
{
	this->SwitchModeOfPlay(EPF2ModeOfPlay::Downtime);
}

void APF2GameModeBase::SwitchModeOfPlay(const EPF2ModeOfPlay NewMode) const
{
	IPF2GameStateInterface* Pf2GameState = this->GetGameState<IPF2GameStateInterface>();

	if (Pf2GameState != nullptr)
	{
		Pf2GameState->SwitchModeOfPlay(NewMode);
	}
}

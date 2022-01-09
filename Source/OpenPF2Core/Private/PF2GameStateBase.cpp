// OpenPF2 for UE Game Logic, Copyright 2021, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "PF2GameStateBase.h"

#include <Engine/World.h>
#include <Net/UnrealNetwork.h>

#include "OpenPF2Core.h"
#include "PF2PlayerControllerInterface.h"
#include "GameModes/PF2ModeOfPlayRuleSet.h"
#include "Utilities/PF2EnumUtilities.h"

APF2GameStateBase::APF2GameStateBase()
{
}

void APF2GameStateBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APF2GameStateBase, ModeOfPlay);
}

void APF2GameStateBase::SwitchModeOfPlay(const EPF2ModeOfPlayType                      NewMode,
                                         const TScriptInterface<IPF2ModeOfPlayRuleSet> NewRuleSet)
{
	if (this->HasAuthority())
	{
		UE_LOG(
			LogPf2Core,
			Verbose,
			TEXT("Transitioning from current mode of play (%s) to new mode (%s)."),
			*PF2EnumUtilities::ToString(this->ModeOfPlay),
			*PF2EnumUtilities::ToString(NewMode)
		);

		this->ModeOfPlay        = NewMode;
		this->ModeOfPlayRuleSet = NewRuleSet;
	}
}

void APF2GameStateBase::OnRep_ModeOfPlay()
{
	const UWorld* const World = this->GetWorld();

	for (FConstPlayerControllerIterator Iterator = World->GetPlayerControllerIterator(); Iterator; ++Iterator)
	{
		APlayerController* PlayerController = Iterator->Get();

		IPF2PlayerControllerInterface* const PF2PlayerController =
			Cast<IPF2PlayerControllerInterface>(PlayerController);

		if (PF2PlayerController != nullptr)
		{
			PF2PlayerController->Execute_OnModeOfPlayChanged(PlayerController, this->ModeOfPlay);
		}
	}
}

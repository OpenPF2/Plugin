// OpenPF2 for UE Game Logic, Copyright 2022, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
//
// Portions of this code were adapted from or inspired by the "Real-Time Strategy Plugin for Unreal Engine 4" by Nick
// Pruehs, provided under the MIT License. Copyright (c) 2017 Nick Pruehs.

#include "PF2AIControllerBase.h"

#include <BehaviorTree/BlackboardComponent.h>

#include "PF2CharacterInterface.h"

#include "Commands/PF2CharacterCommand.h"

#include "Utilities/PF2LogUtilities.h"

void APF2AIControllerBase::PerformCommandOnPossessedCharacter(
	const TScriptInterface<IPF2CharacterCommandInterface>& CharacterCommand)
{
	const TScriptInterface<IPF2CharacterInterface> TargetCharacter = CharacterCommand->GetTargetCharacter();

	UE_LOG(
		LogPf2CoreAbilities,
		VeryVerbose,
		TEXT("[%s] PerformCommandOnPossessedCharacter() called on AI controller ('%s')."),
		*(PF2LogUtilities::GetHostNetId(this->GetWorld())),
		*(this->GetIdForLogs())
	);

	if (TargetCharacter == nullptr)
	{
		UE_LOG(
			LogPf2CoreAbilities,
			Error,
			TEXT("[%s] PerformCommandOnPossessedCharacter(): Null command passed to AI controller ('%s')."),
			*(PF2LogUtilities::GetHostNetId(this->GetWorld())),
			*(this->GetIdForLogs())
		);
		return;
	}

	if (TargetCharacter->ToPawn()->GetController() != this)
	{
		UE_LOG(
			LogPf2CoreAbilities,
			Error,
			TEXT("[%s] PerformCommandOnPossessedCharacter(%s): Target character must be possessed by this AI controller ('%s')."),
			*(PF2LogUtilities::GetHostNetId(this->GetWorld())),
			*(CharacterCommand->GetIdForLogs()),
			*(this->GetIdForLogs())
		);
		return;
	}

	// FIXME: What if multiple commands come in in quick succession? This is only a short-term fix.
	this->GetBlackboardComponent()->SetValueAsObject(this->GetBlackboardNextCommandKey(), CharacterCommand.GetObject());
}

FString APF2AIControllerBase::GetIdForLogs() const
{
	return this->GetName();
}

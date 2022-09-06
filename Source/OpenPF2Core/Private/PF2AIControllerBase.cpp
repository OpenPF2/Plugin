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

void APF2AIControllerBase::PerformAbilityOnControllableCharacter(
	const FGameplayAbilitySpecHandle                AbilitySpecHandle,
	const TScriptInterface<IPF2CharacterInterface>& TargetCharacter)
{
	IPF2CharacterCommandInterface* Command;

	UE_LOG(
		LogPf2CoreAbilities,
		VeryVerbose,
		TEXT("[%s] PerformAbilityOnControllableCharacter() called on AI controller ('%s')."),
		*(PF2LogUtilities::GetHostNetId(this->GetWorld())),
		*(this->GetIdForLogs())
	);

	if (TargetCharacter->ToPawn()->GetController() != this)
	{
		UE_LOG(
			LogPf2CoreAbilities,
			Error,
			TEXT("[%s] %s::PerformAbilityOnControllableCharacter(%s,%s): TargetCharacter must be controllable by this AI controller."),
			*(PF2LogUtilities::GetHostNetId(this->GetWorld())),
			*(this->GetIdForLogs()),
			*(AbilitySpecHandle.ToString()),
			*(TargetCharacter->GetIdForLogs())
		);
		return;
	}

	// TODO: Pass the command through the RPC rather than building it in each controller. It's already an actor.
	Command =
		APF2CharacterCommand::Create(PF2InterfaceUtilities::FromScriptInterface(TargetCharacter), AbilitySpecHandle);

	// FIXME: What if multiple commands come in in quick succession? This is only a short-term fix.
	this->GetBlackboardComponent()->SetValueAsObject(this->GetBlackboardNextCommandKey(), Cast<UObject>(Command));
}

FString APF2AIControllerBase::GetIdForLogs() const
{
	return this->GetName();
}

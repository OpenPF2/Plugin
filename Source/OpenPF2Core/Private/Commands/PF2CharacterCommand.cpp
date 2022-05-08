// OpenPF2 for UE Game Logic, Copyright 2022, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "Commands/PF2CharacterCommand.h"

#include "Abilities/PF2GameplayAbilityInterface.h"


UTexture2D* UPF2CharacterCommand::GetCommandIcon() const
{
	return GetAbility()->GetAbilityIcon();
}

FText UPF2CharacterCommand::GetCommandLabel() const
{
	return GetAbility()->GetAbilityLabel();
}

FText UPF2CharacterCommand::GetCommandDescription() const
{
	return GetAbility()->GetAbilityDescription();
}

EPF2CommandExecuteOrQueueResult UPF2CharacterCommand::AttemptExecuteOrQueue()
{
	// FIXME
	return EPF2CommandExecuteOrQueueResult::None;
}

EPF2CommandExecuteOrBlockResult UPF2CharacterCommand::AttemptExecuteOrBlock()
{
	// FIXME
	return EPF2CommandExecuteOrBlockResult::None;
}

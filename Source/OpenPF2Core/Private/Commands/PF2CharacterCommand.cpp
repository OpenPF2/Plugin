// OpenPF2 for UE Game Logic, Copyright 2022, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "Commands/PF2CharacterCommand.h"

#include "Abilities/PF2GameplayAbilityInterface.h"

#include "GameModes/PF2GameModeInterface.h"

#include "Utilities/PF2EnumUtilities.h"
#include "Utilities/PF2InterfaceUtilities.h"
#include "Utilities/PF2LogUtilities.h"

UTexture2D* UPF2CharacterCommand::GetCommandIcon() const
{
	return GetAbilityIntf()->GetAbilityIcon();
}

FText UPF2CharacterCommand::GetCommandLabel() const
{
	return GetAbilityIntf()->GetAbilityLabel();
}

FText UPF2CharacterCommand::GetCommandDescription() const
{
	return GetAbilityIntf()->GetAbilityDescription();
}

EPF2CommandExecuteOrQueueResult UPF2CharacterCommand::AttemptExecuteOrQueue()
{
	EPF2CommandExecuteOrQueueResult Result = EPF2CommandExecuteOrQueueResult::None;
	const UWorld* const             World  = this->GetWorld();

	UE_LOG(
		LogPf2CoreAbilities,
		VeryVerbose,
		TEXT("[%s] AttemptExecuteOrQueue() called on command ('%s')."),
		*(PF2LogUtilities::GetHostNetId(this->GetWorld())),
		*(this->GetIdForLogs())
	);

	if (World != nullptr)
	{
		IPF2GameModeInterface* PF2GameMode = Cast<IPF2GameModeInterface>(World->GetAuthGameMode());

		if (PF2GameMode != nullptr)
		{
			TScriptInterface<IPF2CharacterInterface> CharacterIntf =
				PF2InterfaceUtilities::ToScriptInterface(this->GetCharacter());

			TScriptInterface<IPF2CharacterCommandInterface> CommandIntf =
				PF2InterfaceUtilities::ToScriptInterface<IPF2CharacterCommandInterface>(this);

			Result = PF2GameMode->AttemptExecuteOrQueueCommand(CharacterIntf, CommandIntf);
		}
	}

	return Result;
}

EPF2ImmediateCommandExecutionResult UPF2CharacterCommand::AttemptExecuteImmediately()
{
	EPF2ImmediateCommandExecutionResult Result;

	UE_LOG(
		LogPf2CoreAbilities,
		VeryVerbose,
		TEXT("[%s] AttemptExecuteImmediately() called on command ('%s')."),
		*(PF2LogUtilities::GetHostNetId(this->GetWorld())),
		*(this->GetIdForLogs())
	);

	if (this->GetAbilitySystemComponent()->TryActivateAbility(this->GetAbilitySpecHandle()))
	{
		Result = EPF2ImmediateCommandExecutionResult::Activated;
	}
	else
	{
		Result = EPF2ImmediateCommandExecutionResult::Blocked;
	}

	UE_LOG(
		LogPf2CoreAbilities,
		VeryVerbose,
		TEXT("[%s] AttemptExecuteImmediately() result for command ('%s'): %s."),
		*(PF2LogUtilities::GetHostNetId(this->GetWorld())),
		*(this->GetIdForLogs()),
		*(PF2EnumUtilities::ToString(Result))
	);

	return Result;
}

FString UPF2CharacterCommand::GetIdForLogs() const
{
	// ReSharper disable CppRedundantParentheses
	return FString::Format(
		TEXT("{0}[{1}.{2}]"),
		{
			*(this->GetCommandLabel().ToString()),
			*(this->GetAbility()->GetName()),
			*(this->GetName())
		}
	);
}

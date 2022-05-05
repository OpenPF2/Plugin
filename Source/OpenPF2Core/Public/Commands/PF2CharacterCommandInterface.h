// OpenPF2 for UE Game Logic, Copyright 2022, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#pragma once

#include <CoreMinimal.h>
#include <Engine/Texture2D.h>
#include <UObject/Interface.h>

#include "Commands/PF2CommandExecuteOrBlockResult.h"
#include "Commands/PF2CommandExecuteOrQueueResult.h"

#include "PF2CharacterCommandInterface.generated.h"

class IPF2CharacterInterface;
UINTERFACE(MinimalAPI, BlueprintType, meta=(CannotImplementInterfaceInBlueprint))
class UPF2CharacterCommandInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * An interface for commands that can either be executed immediately, or defer their execution to a future time.
 */
class OPENPF2CORE_API IPF2CharacterCommandInterface
{
	GENERATED_BODY()

public:
	/**
	 * Gets the name of this command whenever it is displayed to players/users.
	 *
	 * @return
	 *	A textual description of this command.
	 */
	UFUNCTION(BlueprintCallable, Category="OpenPF2|Character Commands")
	virtual FText GetCommandLabel() const = 0;

	/**
	 * Gets an icon to represent this command whenever it is displayed to players/users.
	 *
	 * @return
	 *	A graphical representation of this command.
	 */
	UFUNCTION(BlueprintCallable, Category="OpenPF2|Character Commands")
	virtual UTexture2D* GetCommandIcon() const = 0;

	/**
	 * Attempt to execute this command immediately, if possible; queue it for the character, if not possible.
	 *
	 * In rare circumstances, it is possible that the command is neither queued nor executed, in which case the result
	 * will be EPF2CommandExecuteOrQueueResult::Refused.
	 *
	 * @param Pf2Character
	 *	The character for which the command will be queued, if it cannot be executed immediately.
	 *
	 * @return
	 *	The outcome of attempting to execute the command.
	 */
	UFUNCTION(BlueprintCallable, Category="OpenPF2|Character Commands")
	virtual EPF2CommandExecuteOrQueueResult AttemptExecuteOrQueue(IPF2CharacterInterface* Pf2Character) = 0;

	/**
	 * Attempt to execute this command immediately, if possible; do nothing, if not possible.
	 *
	 * @return
	 *	The outcome of attempting to execute the command.
	 */
	UFUNCTION(BlueprintCallable, Category="OpenPF2|Character Commands")
	virtual EPF2CommandExecuteOrBlockResult AttemptExecuteOrBlock() = 0;
};

// OpenPF2 for UE Game Logic, Copyright 2022, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#pragma once

#include <Kismet/BlueprintFunctionLibrary.h>

#include "Commands/PF2CommandExecuteImmediatelyResult.h"
#include "Commands/PF2CommandExecuteOrQueueResult.h"

#include "PF2CharacterCommandLibrary.generated.h"

// =====================================================================================================================
// Normal Declarations
// =====================================================================================================================
/**
 * Function library for commands issued to OpenPF2 characters.
 */
UCLASS()
class UPF2CharacterCommandLibrary final : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/**
	 * Utility function for mapping a "Command Execute Immediately Result" to a "Command Execute Or Queue Result".
	 *
	 * @param ImmediateResult
	 *	The result to transcribed.
	 *
	 * @return
	 *	The transcribed result.
	 */
	UFUNCTION(BlueprintPure, Category="OpenPF2|Character Commands")
	static EPF2CommandExecuteOrQueueResult ImmediateResultToExecuteOrQueueResult(
		const EPF2CommandExecuteImmediatelyResult ImmediateResult);
};

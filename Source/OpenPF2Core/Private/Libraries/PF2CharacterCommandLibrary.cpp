// OpenPF2 for UE Game Logic, Copyright 2022, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "Libraries/PF2CharacterCommandLibrary.h"

EPF2CommandExecuteOrQueueResult UPF2CharacterCommandLibrary::ImmediateResultToExecuteOrQueueResult(
	const EPF2CommandExecuteImmediatelyResult ImmediateResult)
{
	switch (ImmediateResult)
	{
		default:
		case EPF2CommandExecuteImmediatelyResult::None:
			return EPF2CommandExecuteOrQueueResult::None;

		case EPF2CommandExecuteImmediatelyResult::Activated:
			return EPF2CommandExecuteOrQueueResult::ExecutedImmediately;

		case EPF2CommandExecuteImmediatelyResult::Blocked:
			return EPF2CommandExecuteOrQueueResult::Refused;

		case EPF2CommandExecuteImmediatelyResult::Cancelled:
			return EPF2CommandExecuteOrQueueResult::Refused;
	}
}

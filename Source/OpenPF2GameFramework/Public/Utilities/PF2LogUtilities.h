// OpenPF2 Game Framework for Unreal Engine, Copyright 2022-2024, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#pragma once

// ReSharper disable once CppUnusedIncludeDirective
#include <Engine/World.h>

/**
 * Utility logic for generating logger statements.
 */
namespace PF2LogUtilities
{
	/**
	 * Gets the identifier for where code is currently executing -- either on a server or a client.
	 *
	 * @param World
	 *	The loaded world of the current host (client/server).
	 *
	 * @return
	 *	An identifier that can be added to logs to identify the host that is running the current code.
	 */
	OPENPF2GAMEFRAMEWORK_API FString GetHostNetId(const UWorld* World);
}

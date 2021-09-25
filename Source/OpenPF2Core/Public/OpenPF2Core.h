// OpenPF2 for UE Game Logic, Copyright 2021, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

/**
 * Log category for logic evaluated by the OpenPF2 core code.
 */
OPENPF2CORE_API DECLARE_LOG_CATEGORY_EXTERN(LogPf2Core, VeryVerbose, VeryVerbose);

/**
 * Log category for logging character abilities and stats (very verbose).
 */
OPENPF2CORE_API DECLARE_LOG_CATEGORY_EXTERN(LogPf2CoreStatsDebug, VeryVerbose, VeryVerbose);

/**
 * Top-level module for responding to events for the OpenPF2 plug-in.
 */
class FOpenPF2CoreModule : public IModuleInterface
{
public:
	// =================================================================================================================
	// Public Methods - IModuleInterface Implementation
	// =================================================================================================================
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

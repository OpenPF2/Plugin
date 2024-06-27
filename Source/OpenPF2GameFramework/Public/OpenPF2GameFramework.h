// OpenPF2 for UE Game Logic, Copyright 2021-2024, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#pragma once

#include <Modules/ModuleManager.h>

/**
 * Log category for logic evaluated by OpenPF2 blueprint nodes.
 */
OPENPF2GAMEFRAMEWORK_API DECLARE_LOG_CATEGORY_EXTERN(LogPf2BlueprintNodes, Log, VeryVerbose);

/**
 * Log category for logic evaluated by the OpenPF2 core code.
 */
OPENPF2GAMEFRAMEWORK_API DECLARE_LOG_CATEGORY_EXTERN(LogPf2Core, Log, VeryVerbose);

/**
 * Log category for logic evaluated by OpenPF2 code that executes abilities and actions.
 */
OPENPF2GAMEFRAMEWORK_API DECLARE_LOG_CATEGORY_EXTERN(LogPf2Abilities, Log, VeryVerbose);

/**
 * Log category for logic evaluated by OpenPF2 during encounters.
 */
OPENPF2GAMEFRAMEWORK_API DECLARE_LOG_CATEGORY_EXTERN(LogPf2Encounters, Log, VeryVerbose);

/**
 * Log category for character-initiative management logic evaluated by OpenPF2, usually during encounters.
 */
OPENPF2GAMEFRAMEWORK_API DECLARE_LOG_CATEGORY_EXTERN(LogPf2Initiative, Log, VeryVerbose);

/**
 * Log category for inventory management logic evaluated by OpenPF2.
 */
OPENPF2GAMEFRAMEWORK_API DECLARE_LOG_CATEGORY_EXTERN(LogPf2Inventory, Log, VeryVerbose);

/**
 * Log category for logging character abilities and stats (very verbose).
 */
OPENPF2GAMEFRAMEWORK_API DECLARE_LOG_CATEGORY_EXTERN(LogPf2Stats, Log, VeryVerbose);

/**
 * Log category for logging input from a player.
 */
OPENPF2GAMEFRAMEWORK_API DECLARE_LOG_CATEGORY_EXTERN(LogPf2Input, Log, VeryVerbose);

/**
 * Top-level module for responding to events for the OpenPF2 plug-in.
 */
class FOpenPF2GameFrameworkModule final : public IModuleInterface
{
public:
	// =================================================================================================================
	// Public Methods - IModuleInterface Implementation
	// =================================================================================================================
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

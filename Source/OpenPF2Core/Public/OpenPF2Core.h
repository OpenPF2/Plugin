// OpenPF2 for UE Game Logic, Copyright 2021, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

OPENPF2CORE_API DECLARE_LOG_CATEGORY_EXTERN(LogPf2Core, VeryVerbose, VeryVerbose);
OPENPF2CORE_API DECLARE_LOG_CATEGORY_EXTERN(LogPf2CoreStatsDebug, VeryVerbose, VeryVerbose);

class FOpenPF2CoreModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

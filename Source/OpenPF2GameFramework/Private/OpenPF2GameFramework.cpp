// OpenPF2 for UE Game Logic, Copyright 2021-2024, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "OpenPF2GameFramework.h"

#define LOCTEXT_NAMESPACE "FOpenPF2GameFrameworkModule"

void FOpenPF2GameFrameworkModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin
	// file per-module
}

void FOpenPF2GameFrameworkModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FOpenPF2GameFrameworkModule, OpenPF2Core)

// =====================================================================================================================
// Logging Definitions
// =====================================================================================================================
DEFINE_LOG_CATEGORY(LogPf2BlueprintNodes);
DEFINE_LOG_CATEGORY(LogPf2Core);
DEFINE_LOG_CATEGORY(LogPf2Abilities);
DEFINE_LOG_CATEGORY(LogPf2Encounters);
DEFINE_LOG_CATEGORY(LogPf2Initiative);
DEFINE_LOG_CATEGORY(LogPf2Inventory);
DEFINE_LOG_CATEGORY(LogPf2Stats);
DEFINE_LOG_CATEGORY(LogPf2Input);

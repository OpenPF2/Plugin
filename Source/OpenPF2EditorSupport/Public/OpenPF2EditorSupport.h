// OpenPF2 for UE Game Logic, Copyright 2023, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#pragma once

#include <PropertyEditorModule.h>

#include <Modules/ModuleManager.h>

/**
 * Log category for logic evaluated by OpenPF2 Editor Support code.
 */
OPENPF2EDITORSUPPORT_API DECLARE_LOG_CATEGORY_EXTERN(LogPf2EditorSupport, Log, VeryVerbose);

/**
 * Top-level module for the OpenPF2 Editor Support plug-in.
 */
class FOpenPF2EditorSupport final : public IModuleInterface
{
protected:
	// =================================================================================================================
	// Protected Static Methods
	// =================================================================================================================
	static TArray<UClass*> GetClassesWithInterfaceEvents();

public:
	// =================================================================================================================
	// Public Methods - IModuleInterface Implementation
	// =================================================================================================================
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

protected:
	// =================================================================================================================
	// Protected Instance Methods
	// =================================================================================================================
	void InitializeInterfaceEventsCustomizations(FPropertyEditorModule& PropertyModule) const;
	void UnregisterInterfaceEventsCustomizations(FPropertyEditorModule& PropertyModule) const;
};

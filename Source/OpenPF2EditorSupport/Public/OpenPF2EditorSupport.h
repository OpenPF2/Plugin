// OpenPF2 Game Framework for Unreal Engine, Copyright 2023-2024, Guy Elsmore-Paddock. All Rights Reserved.
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
 *
 * This exposes UI elements for use by game designers while editing Blueprints. It is not used in a shipping build.
 */
class FOpenPF2EditorSupport final : public IModuleInterface
{
protected:
	// =================================================================================================================
	// Protected Static Methods
	// =================================================================================================================
	/**
	 * Registers a customization of the "Details" panel in the Blueprint Editor for every OpenPF2 event emitter.
	 *
	 * @param PropertyModule
	 *	The loaded instance of the editor's property editing module.
	 */
	static void RegisterEmitterEventsCustomizations(FPropertyEditorModule& PropertyModule);

	/**
	 * Unregisters all customizations of the "Details" panel from the Blueprint Editor.
	 *
	 * @param PropertyModule
	 *	The loaded instance of the editor's property editing module.
	 */
	static void UnregisterEmitterEventsCustomizations(FPropertyEditorModule& PropertyModule);

	/**
	 * Identifies all classes that implement the event emitter interface.
	 *
	 * These classes return an Events Object to which delegates can be bound so that consumers of those classes can
	 * depend only on the interfaces of the objects rather than their concrete types.
	 *
	 * @return
	 *	An array of classes that implement the UPF2EventEmitterInterface.
	 */
	static TArray<UClass*> GetEventEmitterClasses();

public:
	// =================================================================================================================
	// Public Methods - IModuleInterface Implementation
	// =================================================================================================================
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

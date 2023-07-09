// OpenPF2 for UE Game Logic, Copyright 2021-2023, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "OpenPF2EditorSupport.h"

#include <PropertyEditorModule.h>

#include "InterfaceEventsDetailCustomization.h"
#include "PF2EventEmitterInterface.h"

#define LOCTEXT_NAMESPACE "FOpenPF2EditorSupport"

void FOpenPF2EditorSupport::RegisterEmitterEventsCustomizations(FPropertyEditorModule& PropertyModule)
{
	for (const UClass* DerivedClass : GetEventEmitterClasses())
	{
		PropertyModule.RegisterCustomClassLayout(
			DerivedClass->GetFName(),
			FOnGetDetailCustomizationInstance::CreateStatic(&FInterfaceEventsDetailCustomization::MakeInstance)
		);
	}
}

void FOpenPF2EditorSupport::UnregisterEmitterEventsCustomizations(FPropertyEditorModule& PropertyModule)
{
	for (const UClass* DerivedClass : GetEventEmitterClasses())
	{
		PropertyModule.UnregisterCustomClassLayout(DerivedClass->GetFName());
	}
}

TArray<UClass*> FOpenPF2EditorSupport::GetEventEmitterClasses()
{
	TArray<UClass*> Implementors;

	for (TObjectIterator<UClass> It; It; ++It)
	{
		UClass* Class = *It;

		if (Class->ImplementsInterface(UPF2EventEmitterInterface::StaticClass()))
		{
			Implementors.Add(Class);
		}
	}

	return Implementors;
}

void FOpenPF2EditorSupport::StartupModule()
{
	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");

	this->RegisterEmitterEventsCustomizations(PropertyModule);

	PropertyModule.NotifyCustomizationModuleChanged();
}

void FOpenPF2EditorSupport::ShutdownModule()
{
	if (FModuleManager::Get().IsModuleLoaded("PropertyEditor"))
	{
		FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");

		this->UnregisterEmitterEventsCustomizations(PropertyModule);
	}
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FOpenPF2EditorSupport, OpenPF2EditorSupport)

// =====================================================================================================================
// Logging Definitions
// =====================================================================================================================
DEFINE_LOG_CATEGORY(LogPf2EditorSupport);

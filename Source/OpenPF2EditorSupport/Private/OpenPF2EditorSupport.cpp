// OpenPF2 for UE Game Logic, Copyright 2021-2023, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "OpenPF2EditorSupport.h"

#include <PropertyEditorModule.h>

#include "InterfaceEventsDetailCustomization.h"
#include "PF2CharacterQueueComponent.h"
#include "PF2EventsInterface.h"

#define LOCTEXT_NAMESPACE "FOpenPF2EditorSupport"

void FOpenPF2EditorSupport::StartupModule()
{
	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");

	this->InitializeInterfaceEventsCustomizations(PropertyModule);

	PropertyModule.NotifyCustomizationModuleChanged();
}

void FOpenPF2EditorSupport::ShutdownModule()
{
	if (FModuleManager::Get().IsModuleLoaded("PropertyEditor"))
	{
		FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");

		this->UnregisterInterfaceEventsCustomizations(PropertyModule);
	}
}

TArray<UClass*> FOpenPF2EditorSupport::GetClassesWithInterfaceEvents()
{
	TArray<UClass*> Implementors;

	for (TObjectIterator<UClass> It; It; ++It)
	{
		UClass* Class = *It;

		if (Class->ImplementsInterface(UPF2EventsInterface::StaticClass()))
		{
			Implementors.Add(Class);
		}
	}

	return Implementors;
}

// ReSharper disable once CppMemberFunctionMayBeStatic
void FOpenPF2EditorSupport::InitializeInterfaceEventsCustomizations(FPropertyEditorModule& PropertyModule) const
{
	for (const UClass* DerivedClass : GetClassesWithInterfaceEvents())
	{
		PropertyModule.RegisterCustomClassLayout(
			DerivedClass->GetFName(),
			FOnGetDetailCustomizationInstance::CreateStatic(&FInterfaceEventsDetailCustomization::MakeInstance)
		);
	}
}

// ReSharper disable once CppMemberFunctionMayBeStatic
void FOpenPF2EditorSupport::UnregisterInterfaceEventsCustomizations(FPropertyEditorModule& PropertyModule) const
{
	for (const UClass* DerivedClass : GetClassesWithInterfaceEvents())
	{
		PropertyModule.UnregisterCustomClassLayout(DerivedClass->GetFName());
	}
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FOpenPF2EditorSupport, OpenPF2EditorSupport)

// =====================================================================================================================
// Logging Definitions
// =====================================================================================================================
DEFINE_LOG_CATEGORY(LogPf2EditorSupport);

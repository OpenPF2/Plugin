// OpenPF2 for UE Game Logic, Copyright 2023, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#pragma once

#include <IDetailCustomization.h>
#include <SMyBlueprint.h>
#include <SSubobjectEditor.h>

#include <Input/Reply.h>

class IPF2EventsInterface;

// ReSharper disable once CppClassCanBeFinal
class FInterfaceEventsDetailCustomization : public IDetailCustomization
{
public:
	// =================================================================================================================
	// Public Static Methods
	// =================================================================================================================
	/**
	 * Makes a new instance of this detail layout class for a specific detail view requesting it.
	 */
	static TSharedRef<IDetailCustomization> MakeInstance()
	{
		return MakeShareable(new FInterfaceEventsDetailCustomization());
	}

protected:
	// =================================================================================================================
	// Protected Fields
	// =================================================================================================================
	TWeakObjectPtr<UBlueprint> Blueprint;

public:
	explicit FInterfaceEventsDetailCustomization() : Blueprint(nullptr)
	{
	}

	// =================================================================================================================
	// Public Methods - IDetailCustomization Implementation
	// =================================================================================================================
	virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;

	// =================================================================================================================
	// Protected Instance Methods
	// =================================================================================================================
	FORCEINLINE UBlueprint* GetBlueprint() const
	{
		return Blueprint.Get();
	}

protected:
	void AddEventsCategory(IDetailLayoutBuilder& DetailBuilder,
	                       const UObject*        SelectedObject,
	                       const FName           SelectedVariableName) const;

	FReply HandleAddOrViewEventForVariable(const FName                  EventName,
	                                       const FName                  PropertyName,
	                                       const TWeakObjectPtr<UClass> PropertyClass) const;

	int32 GetAddOrViewIndexForButton(const FName EventName,
	                                 const FName PropertyName) const;

	static UBlueprint* GetBlueprintContainingObject(const UObject* SelectedObject);

	static FSubobjectEditorTreeNodePtrType GetSelectedTreeNodeInBlueprint(const UBlueprint* Blueprint);

	static TSharedPtr<SSubobjectEditor> GetSubobjectEditorForBlueprint(const UBlueprint* Blueprint);

	static FBlueprintEditor* GetBlueprintEditorForBlueprint(const UBlueprint* Blueprint);

	static FBlueprintEditor* GetBlueprintEditorForGraph(const UEdGraph* Graph);
};

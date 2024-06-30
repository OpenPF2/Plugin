// OpenPF2 Game Framework for Unreal Engine, Copyright 2023-2024, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#pragma once

#include <SSubobjectEditor.h>

/**
 * Various utilities for functional programming with arrays and similar structures.
 */
namespace PF2BlueprintEditorUtilities
{
	/**
	 * Identifies the Blueprint (if applicable) that contains the given object.
	 *
	 * This is typically only useful for logic that interacts with the Blueprint editor.
	 *
	 * This is null safe. If Object is a null pointer, the result will be a null pointer.
	 *
	 * @param Object
	 *	The object for which a containing blueprint is desired,
	 *
	 * @return
	 *	Either a pointer to the outermost blueprint that contains the given object, or nullptr if the object is not
	 *	contained in a Blueprinted class.
	 */
	OPENPF2EDITORSUPPORT_API UBlueprint* GetBlueprintContainingObject(const UObject* Object);

	/**
	 * Gets the object that is selected (if any) in the "My Blueprint" view of the Blueprint Editor.
	 *
	 * This is null-safe. If Object is a null pointer, the result will be a null pointer.
	 *
	 * @param Blueprint
	 *	The blueprint being edited.
	 *
	 * @return
	 *	Either a pointer to the selected tree node, or nullptr if the given blueprint is not being edited or has no
	 *	active selection.
	 */
	OPENPF2EDITORSUPPORT_API FSubobjectEditorTreeNode* GetSelectedTreeNodeInBlueprint(UBlueprint* Blueprint);

	/**
	 * Gets a reference to the Slate widget for the sub-object editor of the given blueprint.
	 *
	 * This is null safe. If Blueprint is a null pointer, the result will be a null pointer.
	 *
	 * @param Blueprint
	 *	The blueprint being edited.
	 *
	 * @return
	 *	Either a pointer to the sub-object editor of the given blueprint, or nullptr if the given blueprint is not being
	 *	edited.
	 */
	OPENPF2EDITORSUPPORT_API TSharedPtr<SSubobjectEditor> GetSubobjectEditorForBlueprint(UBlueprint* Blueprint);

	/**
	 * Gets the state of the Blueprint/Kismet editor for the given blueprint.
	 *
	 * This is null safe. If Blueprint is a null pointer, the result will be a null pointer.
	 *
	 * @param Blueprint
	 *	The blueprint being edited.
	 *
	 * @return
	 *	Either a pointer to the Blueprint editor state of the given blueprint, or nullptr if the given blueprint is not
	 *	being edited.
	 */
	OPENPF2EDITORSUPPORT_API FBlueprintEditor* GetBlueprintEditorForBlueprint(UBlueprint* Blueprint);
}

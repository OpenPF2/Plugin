// OpenPF2 for UE Game Logic, Copyright 2023, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

// ReSharper disable CppUEBlueprintCallableFunctionUnused
#pragma once

#include <GameplayTagContainer.h>

#include <Kismet/BlueprintFunctionLibrary.h>

#include "PF2TagLibrary.generated.h"

// =====================================================================================================================
// Forward Declarations (to minimize header dependencies)
// =====================================================================================================================

// =====================================================================================================================
// Normal Declarations
// =====================================================================================================================
/**
 * Function library for working with gameplay abilities in OpenPF2.
 */
UCLASS()
class OPENPF2CORE_API UPF2TagLibrary final : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/**
	 * Locates the tag within the specified tag container that is a child of another tag.
	 *
	 * If there are multiple tags in the container that are children or grandchildren of the given tag, only the first
	 * one gets returned.
	 *
	 * @param [in] AllTags
	 *	The tags to search.
	 * @param [in] ParentTag
	 *	The parent (or grandparent) tag of the desired tag.
	 * @param [out] bMatchFound
	 *	Whether a tag was found that is a child of the specified tag.
	 *
	 * @return
	 *	Either the matching tag; or a gameplay tag that is not valid if there is no tag that matches.
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta=(AutoCreateRefTerm="ParentTag"), Category="OpenPF2|Gameplay Tags")
	static FGameplayTag FindChildTag(const FGameplayTagContainer& AllTags,
	                                 const FGameplayTag&          ParentTag,
	                                 bool&                        bMatchFound);
};

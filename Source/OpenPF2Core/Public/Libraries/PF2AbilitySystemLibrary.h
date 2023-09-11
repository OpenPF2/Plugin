// OpenPF2 for UE Game Logic, Copyright 2023, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#pragma once

#include <Kismet/BlueprintFunctionLibrary.h>

#include "PF2PlayerControllerInterface.h"
#include "PF2TargetSelectionType.h"

#include "PF2AbilitySystemLibrary.generated.h"

// =====================================================================================================================
// Normal Declarations
// =====================================================================================================================
/**
 * Function library for working with gameplay abilities in OpenPF2.
 */
UCLASS()
class OPENPF2CORE_API UPF2AbilitySystemLibrary final : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/**
	 * Creates target data from whichever location or character the player has selected through the UI.
	 *
	 * This is usually selected via a movement grid.
	 *
	 * @return
	 *	The handle for the new gameplay ability target data.
	 */
	UFUNCTION(BlueprintPure, Category="OpenPF2|Gameplay Abilities|Target Data")
	static FGameplayAbilityTargetDataHandle CreateAbilityTargetDataFromPlayerControllerTargetSelection(
		const TScriptInterface<IPF2PlayerControllerInterface> PlayerController);

	/**
	 * Gets the type of selection a player has made for a target selection.
	 *
	 * If a target does not exist for the specified handle under the given index, or the target did not originate from
	 * a target selection through an OpenPF2-compatible method, the result is EPF2TargetSelectionType::None.
	 *
	 * @param TargetDataHandle
	 *	The handle to the target data for which a target type is desired.
	 * @param Index
	 *	The index of the data for which a target type is desired.
	 *
	 * @return
	 *	The type of the target selection.
	 */
	UFUNCTION(BlueprintPure, Category="OpenPF2|Gameplay Abilities|Target Data")
	static EPF2TargetSelectionType GetTargetSelectionType(const FGameplayAbilityTargetDataHandle& TargetDataHandle,
	                                                      const int32                             Index);
};

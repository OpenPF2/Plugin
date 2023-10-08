// OpenPF2 for UE Game Logic, Copyright 2023, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#pragma once

#include <Kismet/BlueprintFunctionLibrary.h>

#include "PF2GameplayEffectContainerSpec.h"
#include "PF2PlayerControllerInterface.h"
#include "PF2TargetSelectionType.h"

#include "PF2AbilitySystemLibrary.generated.h"

// =====================================================================================================================
// Forward Declarations (to minimize header dependencies)
// =====================================================================================================================
struct FPF2GameplayEffectContainerSpec;

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

	/**
	 * Gets whether the specified Gameplay Effect (GE) container currently has any gameplay effects to apply.
	 *
	 * @param ContainerSpec
	 *	The gameplay effect container specification to check.
	 *
	 * @return
	 *	- true if the container has at least one GE spec.
	 *	- false if the container has no GE specs.
	 */
	UFUNCTION(BlueprintPure, Category="OpenPF2|Gameplay Effects")
	static FORCEINLINE bool DoesEffectContainerSpecHaveEffects(const FPF2GameplayEffectContainerSpec& ContainerSpec)
	{
		return ContainerSpec.HasEffects();
	}

	/**
	 * Gets whether the specified Gameplay Effect (GE) container currently has any targets (either hits or actors).
	 *
	 * @param ContainerSpec
	 *	The gameplay effect container specification to check.
	 *
	 * @return
	 *	- true if the container has at least one target.
	 *	- false if the container has no targets.
	 */
	UFUNCTION(BlueprintPure, Category="OpenPF2|Gameplay Effects")
	static FORCEINLINE bool DoesEffectContainerSpecHaveTargets(const FPF2GameplayEffectContainerSpec& ContainerSpec)
	{
		return ContainerSpec.HasTargets();
	}

	/**
	 * Returns a copy of the specified Gameplay Effect (GE) container spec with the given hits added as targets.
	 *
	 * @param ContainerSpec
	 *	The original gameplay effect container specification from which to start from.
	 * @param HitResults
	 *	The list of hit results to add as targets of this container.
	 *
	 * @return
	 *	The modified GE container spec.
	 */
	UFUNCTION(BlueprintCallable, Category="OpenPF2|Gameplay Effects")
	static FPF2GameplayEffectContainerSpec AddHitTargetsToEffectContainerSpec(
		const FPF2GameplayEffectContainerSpec& ContainerSpec,
		const TArray<FHitResult>&              HitResults);

	/**
	 * Returns a copy of the specified Gameplay Effect (GE) container spec with the given actors added as targets.
	 *
	 * @param ContainerSpec
	 *	The original gameplay effect container specification from which to start from.
	 * @param TargetActors
	 *	The list of actors to add as targets of the container.
	 *
	 * @return
	 *	The modified GE container spec.
	 */
	UFUNCTION(BlueprintCallable, Category="OpenPF2|Gameplay Effects")
	static FPF2GameplayEffectContainerSpec AddActorTargetsToEffectContainerSpec(
		const FPF2GameplayEffectContainerSpec& ContainerSpec,
		const TArray<AActor*>&                 TargetActors);
};

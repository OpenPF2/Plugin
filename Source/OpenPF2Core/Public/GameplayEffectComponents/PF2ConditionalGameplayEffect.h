// OpenPF2 for UE Game Logic, Copyright 2023, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#pragma once

#include <GameplayEffect.h>

#include <Templates/SubclassOf.h>

#include "PF2ConditionalGameplayEffect.generated.h"

/**
 * Struct for a Gameplay Effect (GE) that can be chained onto the application of another GE.
 *
 * This is modeled after the stock "FConditionalGameplayEffect" struct in the engine, while adding support for game
 * designers to specify additional tags that the source MUST NOT have in order for conditional GEs to be applied and/or
 * provide a tag query for more complex business requirements.
 */
USTRUCT(BlueprintType)
struct OPENPF2CORE_API FPF2ConditionalGameplayEffect
{
	GENERATED_BODY()

protected:
	// =================================================================================================================
	// Public Fields
	// =================================================================================================================
	/**
	 * The conditional Gameplay Effect (GE) to apply to the target if the owning GE applies successfully to the target.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Gameplay Effect")
	TSubclassOf<UGameplayEffect> EffectClass;

	/**
	 * All tags the source must have in order for the conditional Gameplay Effect (GE) to apply.
	 *
	 * If this is blank, the source is not required to have any tags in order for the conditional GE to apply. If the
	 * source has some but not all of these tags, the conditional GE is not applied.
	 *
	 * The source tags are snapshotted at the time that the owning GE gets applied. Therefore, they are not affected by
	 * other conditional GEs on the same owning GE.
	 */
	UPROPERTY(
		EditDefaultsOnly,
		BlueprintReadOnly,
		Category="Gameplay Effect",
		meta=(DisplayName="Source Must Have Tags")
	)
	FGameplayTagContainer RequiredSourceTags;

	/**
	 * All tags the source must NOT have in order for the conditional Gameplay Effect (GE) to apply.
	 *
	 * None of these tags may be present. If the source has at least one of the listed tags, the conditional GE is not
	 * applied.
	 *
	 * The source tags are snapshotted at the time that the owning GE gets applied. Therefore, they are not affected by
	 * other conditional GEs on the same owning GE.
	 */
	UPROPERTY(
		EditAnywhere,
		BlueprintReadOnly,
		Category="Gameplay Effect",
		meta=(DisplayName="Source Must Not Have Tags")
	)
	FGameplayTagContainer IgnoredSourceTags;

	/**
	 * An optional, more complex query for controlling when the conditional Gameplay Effect (GE) can be applied.
	 *
	 * This enables more advanced logic than can be expressed with "Required Source Tags" / "Ignored Source Tags"
	 * alone.
	 *
	 * The source tags are snapshotted at the time that the owning GE gets applied. Therefore, they are not affected by
	 * other conditional GEs on the same owning GE.
	 */
	UPROPERTY(
		EditAnywhere,
		BlueprintReadOnly,
		Category="Gameplay Effect",
		meta=(DisplayName="Source Must Match Query")
	)
	FGameplayTagQuery SourceTagQuery;

public:
	// =================================================================================================================
	// Public Methods
	// =================================================================================================================
	/**
	 * Gets the conditional Gameplay Effect (GE) to apply to the target if the owning GE applies successfully.
	 *
	 * @return
	 *	The conditional Gameplay Effect (GE) to apply to the target if the owning GE applies successfully to the target.
	 */
	FORCEINLINE const TSubclassOf<UGameplayEffect>& GetEffectClass() const
	{
		return this->EffectClass;
	}

	/**
	 * Checks whether tags on the source meet all requirements, enabling the conditional GE to be applied.
	 *
	 * The source must:
	 * - Have all required tags (if any).
	 * - Must have none of the "ignored" tags.
	 * - Must satisfy the tag query (if any).
	 *
	 * The source tags are snapshotted at the time that the owning GE gets applied. Therefore, they are not affected by
	 * other conditional GEs on the same owning GE.
	 *
	 * @param SourceTags
	 *	All of the tags on the source.
	 * @param SourceLevel
	 *	The level of the owning GE that is attempting to invoke the conditional GE.
	 *
	 * @return
	 *	true if the conditional GEs can be invoked because all source tags satisfy requirements; or, false, otherwise.
	 */
	bool CanApply(const FGameplayTagContainer& SourceTags, const float SourceLevel) const;

	/**
	 * Creates a new Gameplay Effect (GE) spec for applying the conditional GE.
	 *
	 * @param EffectContext
	 *	The context of the owning GE that was applied and is the one activating the conditional GE.
	 * @param SourceLevel
	 *	The level of the owning GE that is invoking the conditional GE.
	 *
	 * @return
	 *	A new spec for the conditional GE.
	 */
	FGameplayEffectSpecHandle CreateSpec(const FGameplayEffectContextHandle& EffectContext,
	                                     const float                         SourceLevel) const;

	/**
	 * Overloads equality operator to ensure all fields are equal.
	 *
	 * @param Other
	 *	The other instance to which to compare.
	 *
	 * @return
	 *	true if the two instances have the same values in all fields; or, false, otherwise.
	 */
	bool operator==(const FPF2ConditionalGameplayEffect& Other) const;

	/**
	 * Overloads inequality operator to ensure at least one field is not equal.
	 *
	 * @param Other
	 *	The other instance to which to compare.
	 *
	 * @return
	 *	true if at least one field of the two instances do not have the same values; or, false, otherwise.
	 */
	bool operator!=(const FPF2ConditionalGameplayEffect& Other) const;
};

// OpenPF2 for UE Game Logic, Copyright 2021, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#pragma once

#include <AbilitySystemComponent.h>

#include "PF2CharacterAbilitySystemComponentInterface.h"

#include "PF2AbilitySystemComponent.generated.h"

UCLASS()
class OPENPF2CORE_API UPF2AbilitySystemComponent :
	public UAbilitySystemComponent, public IPF2CharacterAbilitySystemComponentInterface
{
	GENERATED_BODY()

public:
	UPF2AbilitySystemComponent();

	// =================================================================================================================
	// Public Methods - IPF2AbilitySystemComponentInterface Implementation
	// =================================================================================================================
	UFUNCTION(BlueprintGetter)
	virtual bool ArePassiveGameplayEffectsActive() override
	{
		return this->bPassiveEffectsActivated;
	}

	UFUNCTION(BlueprintCallable)
	virtual void AddPassiveGameplayEffect(const int32 Weight, const TSubclassOf<UGameplayEffect> Effect) override;

	virtual void SetPassiveGameplayEffects(const TMultiMap<int32, TSubclassOf<UGameplayEffect>> Effects) override;

	UFUNCTION(BlueprintCallable)
	virtual void RemoveAllPassiveGameplayEffects() override;

	UFUNCTION(BlueprintCallable)
	virtual void ActivatePassiveGameplayEffects() override;

	UFUNCTION(BlueprintCallable)
	virtual void DeactivatePassiveGameplayEffects() override;

	UFUNCTION(BlueprintCallable)
	virtual void AddDynamicTag(const FGameplayTag Tag) override;

	UFUNCTION(BlueprintCallable)
	virtual void AppendDynamicTags(const FGameplayTagContainer Tags) override;

	UFUNCTION(BlueprintCallable)
	virtual void SetDynamicTags(const FGameplayTagContainer Tags) override;

	UFUNCTION(BlueprintCallable)
	virtual void RemoveDynamicTag(const FGameplayTag Tag) override;

	UFUNCTION(BlueprintCallable)
	virtual void RemoveDynamicTags(const FGameplayTagContainer Tags) override;

	UFUNCTION(BlueprintCallable)
	virtual void RemoveAllDynamicTags() override;

	// =================================================================================================================
	// Public Methods - IPF2CharacterAbilitySystemComponentInterface Implementation
	// =================================================================================================================
	UFUNCTION(BlueprintCallable)
    virtual void ApplyAbilityBoost(const EPF2CharacterAbilityScoreType TargetAbilityScore) override;

	UFUNCTION(BlueprintCallable)
	virtual TSubclassOf<UGameplayEffect> GetBoostEffectForAbility(const EPF2CharacterAbilityScoreType AbilityScore) override;

protected:
	// =================================================================================================================
	// Protected Properties - Blueprint Accessible
	// =================================================================================================================
	/**
	 * The Gameplay Effects used to boost abilities.
	 *
	 * For each pair in the map, the key is the type ability score that the effect boosts and the value is the GE for
	 * boosting that ability.
	 */
	UPROPERTY()
	TMap<EPF2CharacterAbilityScoreType, TSubclassOf<UGameplayEffect>> AbilityBoostEffects;

	/**
	 * The list of tags on this ASC that are otherwise not granted by a GE.
	 *
	 * These are used to apply replicated tags that are specific to a particular character instance, such as age, size,
	 * skill proficiency, etc.
	 */
	UPROPERTY(VisibleAnywhere)
	FGameplayTagContainer DynamicTags;

	/**
	 * Whether or not passive Gameplay Effects have been activated on this ASC.
	 */
	UPROPERTY(VisibleAnywhere, BlueprintGetter=ArePassiveGameplayEffectsActive)
	// ReSharper disable once CppUE4CodingStandardNamingViolationWarning
	bool bPassiveEffectsActivated;

	/**
	 * A special, "dummy" GE that is used for applying dynamic tags.
	 *
	 * TODO: Find a different way to accomplish this without a GE. This feels very much like a kludge.
	 */
	UPROPERTY()
	TSubclassOf<UGameplayEffect> DynamicTagsEffect;

	/**
	 * The list of Gameplay Effects (GEs) that are always passively applied to this ASC.
	 *
	 * This is typically a superset of the owning character's managed passive GEs and additional passive GEs. Each value
	 * is a gameplay effect and the key is the weight of that GE. The weight controls the order that all GEs are
	 * applied. Lower weights are applied earlier than higher weights.
	 */
	TMultiMap<int32, TSubclassOf<UGameplayEffect>> PassiveGameplayEffects;

	// =================================================================================================================
	// Protected Methods
	// =================================================================================================================
	/**
	 * Gets the level of the owning character.
	 *
	 * This requires the owning actor to implement IPF2CharacterInterface. If the owning actor does not implement that
	 * interface, the default level of 1 is returned instead.
	 *
	 * @return
	 *	The level of the owning character actor.
	 */
	int GetCharacterLevel() const;

	/**
	 * Invokes the logic of the specified callable, with special handling if passive GEs are already active on this ASC.
	 *
	 * If passive GEs are active on this ASC before this call, they are deactivated; then the callable is invoked, and
	 * passive GEs are re-activated. If passive GEs are not active before this call, then they are not activated at the
	 * end of this call.
	 *
	 * @param Callable
	 *   A lambda that is invoked to perform the task.
	 */
	template<typename Func>
	void InvokeAndReapplyPassiveGEs(Func Callable);
};

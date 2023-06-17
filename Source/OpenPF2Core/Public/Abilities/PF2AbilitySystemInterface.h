// OpenPF2 for UE Game Logic, Copyright 2021-2022, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#pragma once

#include <GameplayEffect.h>
#include <GameplayTagContainer.h>

#include "PF2ActorComponentInterface.h"
#include "PF2AbilitySystemInterface.generated.h"

// =====================================================================================================================
// Forward Declarations (to minimize header dependencies)
// =====================================================================================================================
class IPF2GameplayAbilityInterface;

// =====================================================================================================================
// Delegate Declarations
// =====================================================================================================================
/**
 * Delegate for reacting to abilities changing on the client after replication from the server.
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPF2ClientAbilitiesChangeDelegate);

// =====================================================================================================================
// Normal Declarations
// =====================================================================================================================
UINTERFACE(MinimalAPI, BlueprintType, meta=(CannotImplementInterfaceInBlueprint))
class UPF2AbilitySystemInterface : public UPF2ActorComponentInterface
{
    GENERATED_BODY()
};

/**
 * An interface for OpenPF2-compatible Ability System Components.
 *
 * This interface extends ASCs to support additional, dynamic logic for adding and removing passive GEs and replicated
 * tags, which are commonly generated from settings added to characters and other objects that have an ASC by game
 * designers using Blueprint.
 *
 * Epic places logic like this on the character base object, but that isn't the ideal place because the logic has to
 * interact closely with the ASC on the character to have an effect. So, in OpenPF2, that logic lives in ASCs instead to
 * cut down on the number of concerns character base classes are managing.
 */
class OPENPF2CORE_API IPF2AbilitySystemInterface : public IPF2ActorComponentInterface
{
    GENERATED_BODY()

public:
    /**
     * Gets the activatable OpenPF2-compatible abilities that have been granted to this character.
     *
     * @return
     *	The abilities this character possesses.
     */
    UFUNCTION(BlueprintCallable, Category="OpenPF2|Components|Characters|Ability System")
	virtual TArray<TScriptInterface<IPF2GameplayAbilityInterface>> GetAbilities() const = 0;

	/**
	 * Gets whether passively-applied Gameplay Effects are currently active on this ASC.
	 *
	 * @return
	 *	Whether passive gameplay effects have been activated on this ASC.
	 */
	virtual bool ArePassiveGameplayEffectsActive() const = 0;

	/**
	 * Gets this Ability System Component as a standard ASC.
	 *
	 * @return
	 *	This ASC, as a UObject.
	 */
	UFUNCTION(BlueprintCallable, Category="OpenPF2|Components|Characters|Ability System")
	virtual UAbilitySystemComponent* ToAbilitySystemComponent() = 0;

	/**
	 * Finds one or more granted abilities by their tags.
	 *
	 * @param Tags
	 *	All of the tags that a granted ability must possess in order for it to be returned.
	 * @param bOnlyAbilitiesThatSatisfyTagRequirements
	 *	Only return a match for an ability that has its tag requirements satisfied and is not blocked.
	 *
	 * @return
	 *	The abilities granted to this ASC that have the specified tags.
	 */
	UFUNCTION(BlueprintCallable, Category="OpenPF2|Components|Characters|Ability System")
	virtual TArray<FGameplayAbilitySpec> FindAbilitySpecsByTags(
	    const FGameplayTagContainer& Tags,
	    bool                         bOnlyAbilitiesThatSatisfyTagRequirements = true) const = 0;

	/**
	 * Finds the first granted ability having the specified tags.
	 *
	 * @param InTags
	 *	All of the tags that a granted ability must possess in order for it to be returned.
	 * @param OutMatchFound
	 *	An output parameter that receives whether an ability spec with the specified tags was found.
	 * @param bInOnlyAbilitiesThatSatisfyTagRequirements
	 *	Only return a match for an ability that has its tag requirements satisfied and is not blocked.
	 *
	 * @return
	 *	The first ability granted to this ASC that has the specified tags.
	 */
	UFUNCTION(BlueprintCallable, Category="OpenPF2|Components|Characters|Ability System")
	virtual FGameplayAbilitySpec FindAbilitySpecByTags(
		UPARAM(DisplayName="Tags")
		const FGameplayTagContainer& InTags,

		UPARAM(DisplayName="Match Found")
		bool& OutMatchFound,

		UPARAM(DisplayName="Only Abilities that Satisfy Tag Requirements")
		const bool bInOnlyAbilitiesThatSatisfyTagRequirements = true
	) const = 0;

	/**
	 * Finds the handles of one or more granted abilities by their tags.
	 *
	 * @param Tags
	 *	All of the tags that a granted ability must possess in order for it to be returned.
	 * @param bOnlyAbilitiesThatSatisfyTagRequirements
	 *	Only return a match for an ability that has its tag requirements satisfied and is not blocked.
	 *
	 * @return
	 *	The handles of the abilities granted to this ASC that have the specified tags.
	 */
	UFUNCTION(BlueprintCallable, Category="OpenPF2|Components|Characters|Ability System")
	virtual TArray<FGameplayAbilitySpecHandle> FindAbilityHandlesByTags(
	    const FGameplayTagContainer& Tags,
	    const bool                   bOnlyAbilitiesThatSatisfyTagRequirements = true
	) const = 0;

	/**
	 * Finds the handle of the first granted ability having the specified tags.
	 *
	 * @param InTags
	 *	All of the tags that a granted ability must possess in order for it to be returned.
	 * @param OutMatchFound
	 *	An output parameter that receives whether an ability spec with the specified tags was found.
	 * @param bInOnlyAbilitiesThatSatisfyTagRequirements
	 *	Only return a match for an ability that has its tag requirements satisfied and is not blocked.
	 *
	 * @return
	 *	The handle of the first ability granted to this ASC that has the specified tags.
	 */
	UFUNCTION(BlueprintCallable, Category="OpenPF2|Components|Characters|Ability System")
	virtual FGameplayAbilitySpecHandle FindAbilityHandleByTags(
		UPARAM(DisplayName="Tags")
		const FGameplayTagContainer& InTags,

		UPARAM(DisplayName="Match Found")
		bool& OutMatchFound,

		UPARAM(DisplayName="Only Abilities that Satisfy Tag Requirements")
		const bool bInOnlyAbilitiesThatSatisfyTagRequirements = true
	) const = 0;

	/**
	 * Triggers an ability by handle, providing the given payload as event data.
	 *
	 * This can be used to invoke a specific ability by its handle rather than relying on triggering it indirectly via
	 * an event tag.
	 *
	 * @param AbilitySpecHandle
	 *	The handle of the gameplay ability to invoke.
	 * @param Payload
	 *	The payload to pass to the gameplay ability.
	 *
	 * @return
	 *	- true if the ASC believes that the ability was activated (this may return false positives due to failures later
	 *	  in activation).
	 *	- false if the ASC knows that the ability is not activated.
	 */
	UFUNCTION(BlueprintCallable, Category="OpenPF2|Components|Characters|Ability System")
    virtual bool TriggerAbilityWithPayload(FGameplayAbilitySpecHandle AbilitySpecHandle,
                                           const FGameplayEventData   Payload) = 0;

	/**
	 * Adds a passively-applied Gameplay Effect to this ASC.
	 *
	 * The GE is added to the weight group specified by a tag on GE; this is known as the "default" weight group of the
	 * GE.
	 *
	 * Different instances of the same type of GE can be added multiple times, even with the same weight group. Each
	 * call adds an additional entry for that GE under the default weight.
	 *
	 * Any Passive GEs in weight groups after the default weight group of the GE are automatically re-applied.
	 *
	 * @param Effect
	 *	The gameplay effect to add under the default weight of the GE.
	 */
	UFUNCTION(BlueprintCallable, Category="OpenPF2|Components|Characters|Ability System")
	virtual void AddPassiveGameplayEffect(const TSubclassOf<UGameplayEffect> Effect) = 0;

	/**
	 * Adds a passively-applied Gameplay Effect with the given weight to this ASC.
	 *
	 * Different instances of the same type of GE can be added multiple times, even with the same weight group. Each
	 * call adds an additional entry for that GE under the given weight.
	 *
	 * Any Passive GEs in weight groups after the target weight group are automatically re-applied.
	 *
	 * @param WeightGroup
	 *	The weight group of the GE. This controls how early or late the GE is evaluated, relative to other passive GEs
	 *	on the ASC.
	 * @param Effect
	 *	The gameplay effect to add under the given weight.
	 */
	UFUNCTION(BlueprintCallable, Category="OpenPF2|Components|Characters|Ability System")
	virtual void AddPassiveGameplayEffectWithWeight(
		const FName WeightGroup,
		const TSubclassOf<UGameplayEffect> Effect
	) = 0;

	/**
	 * Sets all of the passive Gameplay Effects on this ASC to the given set.
	 *
	 * If passive GEs are currently active on this ASC, they will be removed and the new GEs will be applied as part of
	 * this call.
	 *
	 * @param Effects
	 *	The list of Gameplay Effects (GEs) to always passively apply to this ASC. Each value must be a gameplay effect
	 *	and the key must be the weight group of that GE. The weight controls the order that all GEs are applied. Lower
	 *	weights are applied earlier than higher weights.
	 */
	virtual void SetPassiveGameplayEffects(const TMultiMap<FName, TSubclassOf<UGameplayEffect>> Effects) = 0;

	/**
	 * Clears all of the passive Gameplay Effects on this ASC.
	 *
	 * If passive GEs are currently active on this ASC, they will be removed and deactivated as part of this call.
	 */
	UFUNCTION(BlueprintCallable, Category="OpenPF2|Components|Characters|Ability System")
	virtual void RemoveAllPassiveGameplayEffects() = 0;

	/**
	 * Activates Gameplay Effects that should remain passively applied on this ASC until deactivated.
	 */
	UFUNCTION(BlueprintCallable, Category="OpenPF2|Components|Characters|Ability System")
	virtual void ActivateAllPassiveGameplayEffects() = 0;

	/**
	 * Removes all passive Gameplay Effects that were previously activated on this ASC.
	 */
	UFUNCTION(BlueprintCallable, Category="OpenPF2|Components|Characters|Ability System")
	virtual void DeactivateAllPassiveGameplayEffects() = 0;

	/**
	 * Activates only Gameplay Effects that exist after the given weight group.
	 *
	 * The weight group itself is not activated.
	 *
	 * @param WeightGroup
	 *	The weight group after which GEs should be activated.
	 *
	 * @return
	 *	The names of all weight groups that were activated.
	 */
	UFUNCTION(BlueprintCallable, Category="OpenPF2|Components|Characters|Ability System")
	virtual TSet<FName> ActivatePassiveGameplayEffectsAfter(const FName WeightGroup) = 0;

	/**
	 * Deactivates only Gameplay Effects that exist after the given weight group.
	 *
	 * The weight group itself is not deactivated. This method has no effect if passive GEs have not been activated
	 * previously.
	 *
	 * @param WeightGroup
	 *	The weight group after which GEs should be deactivated.
	 *
	 * @return
	 *	The names of all weight groups that were deactivated.
	 */
	UFUNCTION(BlueprintCallable, Category="OpenPF2|Components|Characters|Ability System")
	virtual TSet<FName> DeactivatePassiveGameplayEffectsAfter(const FName WeightGroup) = 0;

	/**
	 * Activates the specified weight group of Gameplay Effects.
	 *
	 * @param WeightGroup
	 *	The name of the group to activate.
	 *
	 * @return
	 *	true if the group was activated; or, false, if the group was not activated because it was already activated.
	 */
	UFUNCTION(BlueprintCallable, Category="OpenPF2|Components|Characters|Ability System")
	virtual bool ActivatePassiveGameplayEffects(const FName WeightGroup) = 0;

	/**
	 * Deactivates the specified weight group of Gameplay Effects.
	 *
	 * @param WeightGroup
	 *	The name of the group to deactivate.
	 *
	 * @return
	 *	true if the group was deactivated; or, false, if the group was not deactivated because it was already
	 *	deactivated.
	 */
	UFUNCTION(BlueprintCallable, Category="OpenPF2|Components|Characters|Ability System")
	virtual bool DeactivatePassiveGameplayEffects(const FName WeightGroup) = 0;

	/**
	 * Applies a tag to this ASC that is otherwise not granted by a GE.
	 *
	 * This can be used to apply a replicated tag that is specific to a particular character instance, such as age,
	 * size, skill proficiency, etc. If passive GEs are currently active on this ASC, they will be re-applied when this
	 * method is called. Consequently, calling AppendDynamicTags() is preferred over this method when there are multiple
	 * tags that should be applied at the same time, to avoid unnecessary overhead from re-applying all passive GEs.
	 *
	 * @param Tag
	 *	The tag to apply to this Ability System Component.
	 */
	UFUNCTION(BlueprintCallable, Category="OpenPF2|Components|Characters|Ability System")
	virtual void AddDynamicTag(const FGameplayTag Tag) = 0;

	/**
	 * Applies multiple replicated tags to this ASC that are otherwise not granted by a GE.
	 *
	 * This can be used to apply replicated tags that are specific to a particular character instance, such as age,
	 * size, skill proficiency, etc. If passive GEs are currently active on this ASC, they will be re-applied when this
	 * method is called. Consequently, calling this method is preferred over AddDynamicTag() when there are multiple
	 * tags that should be applied at the same time, to avoid unnecessary overhead from re-applying all passive GEs.
	 *
	 * @param Tags
	 *	The tag to apply to this Ability System Component.
	 */
	UFUNCTION(BlueprintCallable, Category="OpenPF2|Components|Characters|Ability System")
	virtual void AppendDynamicTags(const FGameplayTagContainer Tags) = 0;

	/**
	 * Sets all of the replicated tags in this ASC that are otherwise not granted by a GE.
	 *
	 * This can be used to apply replicated tags that are specific to a particular character instance, such as age,
	 * size, skill proficiency, etc. If passive GEs are currently active on this ASC, they will be re-applied when this
	 * method is called.
	 *
	 * @param Tags
	 *	The new collection of all the tags that should be applied on this Ability System Component.
	 */
	UFUNCTION(BlueprintCallable, Category="OpenPF2|Components|Characters|Ability System")
	virtual void SetDynamicTags(const FGameplayTagContainer Tags) = 0;

	/**
	 * Removes a tag from this ASC that was previously added with AddDynamicTag() or AppendDynamicTags().
	 *
	 * This can be used to remove a tag that is specific to a particular character instance, such as age, size, skill
	 * proficiency, etc. If passive GEs are currently active on this ASC, they will be re-applied when this method is
	 * called. Consequently, calling RemoveDynamicTags() is preferred over this method when there are multiple tags that
	 * should be removed at the same time, to avoid unnecessary overhead from re-applying all passive GEs.
	 *
	 * @param Tag
	 *	The tag to remove from this Ability System Component.
	 */
	UFUNCTION(BlueprintCallable, Category="OpenPF2|Components|Characters|Ability System")
	virtual void RemoveDynamicTag(const FGameplayTag Tag) = 0;

	/**
	 * Removes multiple tags from this ASC that were previously added with AddDynamicTag() or AppendDynamicTags().
	 *
	 * This can be used to remove tags that are specific to a particular character instance, such as age, size, skill
	 * proficiency, etc. If passive GEs are currently active on this ASC, they will be re-applied when this method is
	 * called. Consequently, calling this method is preferred over RemoveDynamicTag() when there are multiple tags that
	 * should be applied at the same time, to avoid unnecessary overhead from re-applying all passive GEs.
	 *
	 * @param Tags
	 *	The tags to remove from this Ability System Component.
	 */
	UFUNCTION(BlueprintCallable, Category="OpenPF2|Components|Characters|Ability System")
	virtual void RemoveDynamicTags(const FGameplayTagContainer Tags) = 0;

	/**
	 * Clears all of the dynamic tags that were previously added to this ASC.
	 *
	 * If passive GEs are currently active on this ASC, they will be re-applied when this method is called.
	 */
	UFUNCTION(BlueprintCallable, Category="OpenPF2|Components|Characters|Ability System")
	virtual void RemoveAllDynamicTags() = 0;

	/**
	 * Gets all of the tags that are active on this ASC as a result of active GEs and Gameplay Cues.
	 *
	 * @return
	 *	A container wrapping the active tags.
	 */
	UFUNCTION(BlueprintCallable, Category="OpenPF2|Components|Characters|Ability System")
	virtual FGameplayTagContainer GetActiveGameplayTags() const = 0;

	/**
	 * Gets the dynamic delegate that listeners can use to be notified when abilities are loaded client-side.
	 *
	 * @return
	 *	Direct access to the multicast change delegate.
	 */
	virtual FPF2ClientAbilitiesChangeDelegate* GetClientAbilityChangeDelegate() = 0;
};

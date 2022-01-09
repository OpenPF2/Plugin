// OpenPF2 for UE Game Logic, Copyright 2021, Guy Elsmore-Paddock. All Rights Reserved.
//
// Content from Pathfinder 2nd Edition is licensed under the Open Game License (OGL) v1.0a, subject to the following:
//   - Open Game License v 1.0a, Copyright 2000, Wizards of the Coast, Inc.
//   - System Reference Document, Copyright 2000, Wizards of the Coast, Inc.
//   - Pathfinder Core Rulebook (Second Edition), Copyright 2019, Paizo Inc.
//
// Except for material designated as Product Identity, the game mechanics and logic in this file are Open Game Content,
// as defined in the Open Game License version 1.0a, Section 1(d) (see accompanying LICENSE.TXT). No portion of this
// file other than the material designated as Open Game Content may be reproduced in any form without written
// permission.

#pragma once

#include <AbilitySystemInterface.h>
#include <UObject/ScriptInterface.h>

#include "Abilities/PF2AbilityBoostBase.h"

#include "PF2CharacterInterface.generated.h"

UINTERFACE(MinimalAPI, meta=(CannotImplementInterfaceInBlueprint))
class UPF2CharacterInterface : public UAbilitySystemInterface
{
    GENERATED_BODY()
};

/**
 * An interface for OpenPF2 characters.
 */
class OPENPF2CORE_API IPF2CharacterInterface: public IAbilitySystemInterface
{
    GENERATED_BODY()

public:
	/**
	 * Returns the name of this character, as set by the game designer.
	 *
	 * If no name has been set, then the UObject name of the character is returned instead.
	 *
	 * @return
	 *	The name of this character.
	 */
	UFUNCTION(BlueprintCallable)
	virtual FText GetCharacterName() const = 0;

	/**
	 * Gets the current level of this character.
	 *
	 * The character level impacts the character's stats and how many boosts and feats the character can have.
	 *
	 * From the Pathfinder 2E Core Rulebook, page 31, "Leveling Up":
	 * "Each level grants greater skill, increased resiliency, and new capabilities, allowing your character to face
	 * even greater challenges and go on to earn even more impressive rewards."
	 */
	UFUNCTION(BlueprintCallable)
	virtual int32 GetCharacterLevel() const = 0;

	/**
	 * Gets the UObject version of the Ability System Component (ASC) for this character.
	 *
	 * @return
	 *	The ASC for this character.
	 */
	UFUNCTION(BlueprintCallable, Category="OpenPF2|Characters")
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override = 0;

	/**
	 * Gets a PF2-specific version of the Ability System Component (ASC) for this character.
	 *
	 * @param Output
	 *	The ASC, as an implementation of the interface for character ASCs.
	 */
	UFUNCTION(BlueprintCallable)
	virtual void GetCharacterAbilitySystemComponent(
		TScriptInterface<IPF2CharacterAbilitySystemComponentInterface>& Output) const = 0;

	/**
	 * Gets a PF2-specific version of the ASC sub-component of this character.
	 *
	 * @return
	 *	The ASC, as an implementation of the interface for character ASCs.
	 */
	virtual IPF2CharacterAbilitySystemComponentInterface* GetCharacterAbilitySystemComponent() const = 0;

	/**
	 * Gets all of the ability boosts that have been granted to this character that require choices from the player.
	 *
	 * @return
	 *	The ability boost GAs that are still pending for this character.
	 */
	UFUNCTION(BlueprintCallable)
	virtual TArray<UPF2AbilityBoostBase*> GetPendingAbilityBoosts() const = 0;

	/**
	 * Gets the actor that is implementing this interface.
	 *
	 * @return
	 *	This character, as an actor.
	 */
	UFUNCTION(BlueprintCallable)
	virtual AActor* ToActor() = 0;

	/**
	 * Applies a single ability boost selection to this character.
	 *
	 * The ability score selections must be compatible with the rule options of the Boost GA.
	 *
	 * The ability boost does not take effect immediately. Invoke ApplyAbilityBoostSelections() to apply all of the
	 * selections that have been added.
	 *
	 * @param BoostGameplayAbility
	 *	The "Boost GA" -- the Gameplay Ability for which ability score boost selections are being applied.
	 * @param SelectedAbilities
	 *	The ability scores that the player selected, out of the options offered by the Boost GA.
	 */
	UFUNCTION(BlueprintCallable)
	virtual void AddAbilityBoostSelection(
	    const TSubclassOf<class UPF2AbilityBoostBase> BoostGameplayAbility,
	    const TSet<EPF2CharacterAbilityScoreType>     SelectedAbilities) = 0;

	/**
	 * Attempts to find and activate a pending ability boost Gameplay Ability for each Ability Boost selection on this
	 * character.
	 *
	 * Pending ability boosts are registered on this character via calls to AddAbilityBoostSelection() before a call to
	 * this method.
	 */
	UFUNCTION(BlueprintCallable)
	virtual void ApplyAbilityBoostSelections() = 0;

	/**
	 * Activates Gameplay Effects that are always passively applied to the character.
	 *
	 * This is the preferred method for toggling passive GEs on for a character that supports ability boosts instead of
	 * toggling passive GEs on the character's ASC, as this method automatically skips out of offering boost selections
	 * for which a player or game designer has already made choices.
	 */
	UFUNCTION(BlueprintCallable)
	virtual void ActivatePassiveGameplayEffects() = 0;

	/**
	 * Removes all passive Gameplay Effects that were previously activated for this character.
	 *
	 * This is the preferred method for toggling passive GEs off for a character that supports ability boosts (e.g.,
	 * during a character level-up) instead of toggling passive GEs off at the character's ASC, as it gives the code for
	 * the character a chance to react to the change before involving the ASC. For example, if the state of any GAs
	 * needs to be recorded so that they are re-applied correctly after passive GEs are re-activated.
	 */
	UFUNCTION(BlueprintCallable)
	virtual void DeactivatePassiveGameplayEffects() = 0;

	/**
	 * Adds a Gameplay Ability (GA) to this character and then immediately activates it.
	 *
	 * This method is intended for use by one-shot GAs that react to events in the environment or game story. As such,
	 * the GA is NOT added to the character's "AdditionalGameplayAbilities" property, as that property is intended to
	 * control the GAs that are added to the character at creation time.
	 *
	 * @param Ability
	 *	The type of ability to add and activate on the character.
	 */
	UFUNCTION(BlueprintCallable)
	virtual void AddAndActivateGameplayAbility(const TSubclassOf<UGameplayAbility> Ability) = 0;

	/**
	 * Notifies this character that it has received damage.
	 *
	 * This should only be invoked by the character's attribute set. This does NOT actually modify the character's
	 * stats. Once invoked, this method fires off appropriate callbacks into the character's Blueprint event graph.
	 *
	 * @param Damage
	 *	The amount of the damage.
	 * @param InstigatorCharacter
	 *	The character that is ultimately responsible for the damage. This can be null if the damage is caused by the
	 *	environment.
	 * @param DamageSource
	 *	The actor that directly inflicted the damage, such as a weapon or projectile.
	 * @param EventTags
	 *	Tags passed along with the damage Gameplay Event. This is typically set by an attack montage to indicate the
	 *	nature of the attack that was performed.
	 * @param HitInfo
	 *	Hit result information, including who was hit and where the damage was inflicted.
	 */
    virtual void HandleDamageReceived(const float                  Damage,
                                      IPF2CharacterInterface*      InstigatorCharacter,
                                      AActor*                      DamageSource,
                                      const FGameplayTagContainer* EventTags,
                                      const FHitResult             HitInfo) = 0;

	/**
	 * Notifies this character that its hit points (i.e., health) have changed.
	 *
	 * This should only be invoked by the character's attribute set. This does NOT actually modify the character's
	 * stats. Once invoked, this method fires off appropriate callbacks into the character's Blueprint event graph.
	 *
	 * @param Delta
	 *	The amount that the character's hit points should change.
	 * @param EventTags
	 *	Tags passed along with the Gameplay Event as metadata about the cause of the change to hit points.
	 */
    virtual void HandleHitPointsChanged(const float Delta, const FGameplayTagContainer* EventTags) = 0;
};

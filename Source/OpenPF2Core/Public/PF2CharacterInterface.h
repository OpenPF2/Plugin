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

#include <UObject/Interface.h>

#include "Abilities/PF2AbilityBoostBase.h"

#include "PF2CharacterInterface.generated.h"

UINTERFACE(MinimalAPI, meta = (CannotImplementInterfaceInBlueprint))
class UPF2CharacterInterface : public UInterface
{
    GENERATED_BODY()
};

/**
 * An interface for OpenPF2 characters.
 */
class OPENPF2CORE_API IPF2CharacterInterface
{
    GENERATED_BODY()

public:
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
	 * Gets a PF2-specific version of the ASC sub-component of this character.
	 *
	 * @param Output
	 *	The ASC, as an implementation of the interface for character ASCs.
	 */
	UFUNCTION(BlueprintCallable)
	virtual void GetCharacterAbilitySystemComponent(TScriptInterface<IPF2CharacterAbilitySystemComponentInterface>& Output) const = 0;

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
};

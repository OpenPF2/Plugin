// OpenPF2 for UE Game Logic, Copyright 2021, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#pragma once

#include "PF2AbilitySystemComponentInterface.h"
#include "Abilities/PF2CharacterAbilityScoreType.h"

#include "PF2CharacterAbilitySystemComponentInterface.generated.h"

// Forward declaration; this is defined in "Abilities/PF2GameplayAbility_BoostAbilityBase.h", but that file depends on
// this header file, so we have to break the recursive dependency.
class UPF2GameplayAbility_BoostAbilityBase;

UINTERFACE(MinimalAPI, meta = (CannotImplementInterfaceInBlueprint))
class UPF2CharacterAbilitySystemComponentInterface : public UPF2AbilitySystemComponentInterface
{
    GENERATED_BODY()
};

/**
 * A more specific OpenPF2 interface for Ability System Components that are owned by characters having ability scores.
 *
 * This interface provides some additional convenience/utility functionality that allows direct manipulation of the
 * ability scores of a character by means of activating passive GEs on the ASC.
 */
class OPENPF2CORE_API IPF2CharacterAbilitySystemComponentInterface : public IPF2AbilitySystemComponentInterface
{
    GENERATED_BODY()

public:
	/**
	 * Adds a boost of the specified ability to the attribute set of the owning character.
	 *
	 * This results in a passive GE being added to the ASC of the character. The GE is added to the weight group
	 * specified by a tag on GE; this is known as the "default" weight group of the GE. Any Passive GEs in weight
	 * groups after the default weight group of the GE are automatically re-applied.
	 *
	 * @param TargetAbilityScore
	 *	The ability score that will be boosted.
	 */
	UFUNCTION(BlueprintCallable)
    virtual void ApplyAbilityBoost(const EPF2CharacterAbilityScoreType TargetAbilityScore) = 0;

	/**
	 * Gets the Gameplay Effect to use as a passive GE when boosting the specified character ability score.
	 *
	 * @param AbilityScore
	 *	The ability score for which a boost is desired.
	 *
	 * @return
	 *	The blueprint to apply as a passive GE to boost that ability.
	 */
	UFUNCTION(BlueprintCallable)
	virtual TSubclassOf<UGameplayEffect> GetBoostEffectForAbility(const EPF2CharacterAbilityScoreType AbilityScore) = 0;

	/**
	 * Gets all of the ability boosts that have been granted to this ASC.
	 *
	 * @return
	 *	The ability boost GAs that are still pending for this character.
	 */
	UFUNCTION(BlueprintCallable)
	virtual TArray<UPF2GameplayAbility_BoostAbilityBase *> GetPendingAbilityBoosts() const = 0;
};

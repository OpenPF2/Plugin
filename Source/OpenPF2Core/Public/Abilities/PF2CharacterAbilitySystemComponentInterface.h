#pragma once

#include "PF2AbilitySystemComponentInterface.h"
#include "Abilities/PF2CharacterAbilityScoreType.h"

#include "PF2CharacterAbilitySystemComponentInterface.generated.h"

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
};

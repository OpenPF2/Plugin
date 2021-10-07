#pragma once

#include <UObject/Interface.h>

#include "Abilities/PF2CharacterAbilityScoreType.h"
#include "Abilities/PF2CharacterAbilitySystemComponentInterface.h"

#include "PF2CharacterAbilityEventsInterface.generated.h"

UINTERFACE(MinimalAPI, meta = (CannotImplementInterfaceInBlueprint))
class UPF2CharacterAbilityEventsInterface : public UInterface
{
    GENERATED_BODY()
};

/**
 * An interface for OpenPF2 objects that need to receive events related to abilities and ability scores.
 */
class OPENPF2CORE_API IPF2CharacterAbilityEventsInterface
{
    GENERATED_BODY()

public:
	/**
	 * Event callback fired when an ability boost has been added to the ASC for the associated character.
	 *
	 * This is invoked by the ASCs that implement IPF2CharacterAbilitySystemComponentInterface.
	 *
	 * @param TargetAsc
	 *	The Ability System Component (ASC) to which the ability boost was added.
	 * @param TargetActor
	 *	The character who owns the ASC.
	 * @param TargetAbilityScore
	 *	The ability score that was boosted.
	 */
    virtual void OnAbilityBoostAdded(const TScriptInterface<IPF2CharacterAbilitySystemComponentInterface> TargetAsc,
                                     const AActor*                                               TargetActor,
                                     const EPF2CharacterAbilityScoreType                         TargetAbilityScore) = 0;
};

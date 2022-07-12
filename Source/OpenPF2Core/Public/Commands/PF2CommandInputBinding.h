// OpenPF2 for UE Game Logic, Copyright 2022, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#pragma once

#include <Templates/SubclassOf.h>

#include "PF2CharacterInterface.h"

#include "PF2CommandInputBinding.generated.h"

class UGameplayAbility;

/**
 * A single binding between an input action and an ability that can be activated.
 */
USTRUCT(BlueprintType)
struct FPF2CommandInputBinding
{
	GENERATED_BODY()

	// =================================================================================================================
	// Public Properties - Blueprint Accessible
	// =================================================================================================================
	/**
	 * The human-friendly name of the action, as configured in project input settings (e.g "Jump", "Fire", etc.).
	 */
	UPROPERTY(EditDefaultsOnly)
	FName ActionName;

	/**
	 * The Gameplay Ability to activate when the action/key is triggered.
	 */
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayAbility> Ability;

protected:
	// =================================================================================================================
	// Protected Properties - Blueprint Accessible
	// =================================================================================================================
	/**
	 * The handle for the corresponding ability, after it has been granted to a character's ASC.
	 */
	UPROPERTY()
	FGameplayAbilitySpecHandle GrantedAbilitySpecHandle;

	// =================================================================================================================
	// Protected Properties
	// =================================================================================================================
	/**
	 * The character to which the ability has been granted.
	 */
	IPF2CharacterInterface* GrantedCharacter;

public:
	// =================================================================================================================
	// Public Constructors
	// =================================================================================================================
	/**
	 * Default constructor (used by Blueprint).
	 */
	explicit FPF2CommandInputBinding() : GrantedCharacter(nullptr)
	{
	}

	/**
	 * Constructor for initializing a FPF2CommandInputBinding from a Gameplay Ability blueprint.
	 *
	 * @param ActionName
	 *	The human-friendly name of the action, as configured in project settings (e.g "Jump").
	 * @param Ability
	 *	The Gameplay Ability to activate when the action/key is triggered.
	 */
	explicit FPF2CommandInputBinding(const FName& ActionName, const TSubclassOf<UGameplayAbility>& Ability) :
		ActionName(ActionName),
		Ability(Ability),
		GrantedCharacter(nullptr)
	{
	}

	/**
	 * Constructor for initializing a FPF2CommandInputBinding from an ability that has already been granted.
	 *
	 * @param ActionName
	 *	The human-friendly name of the action, as configured in project settings (e.g "Jump").
	 * @param AbilitySpec
	 *	The specification for the ability.
	 * @param Character
	 *	The character to which the ability has been granted.
	 */
	explicit FPF2CommandInputBinding(const FName&               ActionName,
	                                 const FGameplayAbilitySpec AbilitySpec,
	                                 IPF2CharacterInterface*    Character) :
		ActionName(ActionName),
		Ability(AbilitySpec.Ability->GetClass()),
		GrantedAbilitySpecHandle(AbilitySpec.Handle),
		GrantedCharacter(Character)
	{
	}

	// =================================================================================================================
	// Public Destructors
	// =================================================================================================================
	/**
	 * Default destructor.
	 */
	virtual ~FPF2CommandInputBinding() = default;

	// =================================================================================================================
	// Public Methods
	// =================================================================================================================
	/**
	 * Determines whether the ability in this binding has been granted to a character.
	 *
	 * @return
	 *	- true if this binding corresponds to a granted ability.
	 *	- false if this binding corresponds to an ability that has not yet been granted.
	 */
	FORCEINLINE bool HasBeenGranted() const
	{
		return this->GrantedAbilitySpecHandle.IsValid();
	}

	/**
	 * Gives this ability to the specified PF2 character.
	 *
	 * This can only be run on the server. If this ability has already been given to the specified character, it is not
	 * granted again. The ability must not have already been given to a different character than the specified
	 * character.
	 *
	 * @param Character
	 *	The PF2-compatible character to which the ability should be given.
	 */
	void GiveAbilityToCharacter(IPF2CharacterInterface* Character);

	/**
	 * Assembles and executes a command that invokes the ability associated with this binding.
	 *
	 * The ability may be queued if the active MoPRS is requiring abilities to be queued (e.g., encounters). The ability
	 * is only invoked if it has been granted to the character. If the ability has not yet been granted, the attempt to
	 * execute the ability is ignored and a warning is logged.
	 */
	virtual void InvokeAbility();

	/**
	 * Notifies the ability that the player is no longer pressing the keys for this binding.
	 *
	 * (The default implementation does nothing, so this call has no effect).
	 */
	virtual void ReleaseAbility();
};

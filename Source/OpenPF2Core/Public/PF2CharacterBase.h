// OpenPF2 for UE Game Logic, Copyright 2021, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#pragma once

#include <GameFramework/Character.h>
#include <AbilitySystemInterface.h>

#include "Abilities/PF2AbilitySystemComponent.h"
#include "Abilities/PF2AttributeSet.h"
#include "PF2CharacterBase.generated.h"

class UGameplayEffect;

/**
 * Base class for both playable and non-playable characters in OpenPF2.
 *
 * PF2-based games should extend this class if they need to provide custom character ability initialization logic.
 */
UCLASS()
class OPENPF2CORE_API APF2CharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// =================================================================================================================
	// Constructors
	// =================================================================================================================
	explicit APF2CharacterBase();

	// =================================================================================================================
	// Public Methods
	// =================================================================================================================
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_Controller() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	// =================================================================================================================
	// Public Methods - IAbilitySystemInterface Implementation
	// =================================================================================================================
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	// =================================================================================================================
	// Public Methods - Blueprint Callable
	// =================================================================================================================
	UFUNCTION(BlueprintCallable)
	virtual int32 GetCharacterLevel() const;

	UFUNCTION(BlueprintCallable)
	virtual bool SetCharacterLevel(int32 NewLevel);

protected:
	// =================================================================================================================
	// Protected Properties - Blueprint Accessible
	// =================================================================================================================
	/**
	 * The Ability System Component (ASC) used for interfacing this character with the Gameplay Abilities System (GAS).
	 */
	UPROPERTY()
	UPF2AbilitySystemComponent* AbilitySystemComponent;

	/**
	 * The attributes of this character.
	 */
	UPROPERTY()
	UPF2AttributeSet* AttributeSet;

	/**
	 * The current level of this character.
	 */
	UPROPERTY(EditAnywhere, Replicated, Category = Abilities, ClampMin = 1)
	int32 CharacterLevel;

	/**
	 * Gameplay Effects that are always passively applied to the character (not dependent on the environment or
	 * abilities).
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Abilities)
	TArray<TSubclassOf<UGameplayEffect>> PassiveGameplayEffects;

	/**
	 * Whether or not passive gameplay effects have been initialized for this character.
	 */
	UPROPERTY()
	// ReSharper disable once CppUE4CodingStandardNamingViolationWarning
	int32 bPassiveEffectsInitialized;

	// =================================================================================================================
	// Protected Methods
	// =================================================================================================================
	/**
	 * Activates gameplay effects that are always passively applied to the character.
	 */
	void AddStartupPassiveGameplayEffects();

	/**
	 * Removes all passive gameplay effects that were previously activated for this character.
	 */
	void RemoveStartupPassiveGameplayEffects();

	/**
	 * Callback invoked when a character's level has changed, to allow logic that depends on levels to be refreshed.
	 *
	 * @param OldLevel
	 *	The previous level of the character.
	 * @param NewLevel
	 *	The new level for the character.
	 */
	virtual void HandleCharacterLevelChanged(float OldLevel, float NewLevel);

	// =================================================================================================================
	// Blueprint Event Callbacks
	// =================================================================================================================
	/**
	 * BP event invoked when a character's level has changed, to allow logic that depends on levels to be refreshed.
	 *
	 * @param OldLevel
	 *	The previous level of the character.
	 * @param NewLevel
	 *	The new level for the character.
	 */
	UFUNCTION(BlueprintImplementableEvent)
	void OnCharacterLevelChanged(float OldLevel, float NewLevel);
};

// OpenPF2 for UE Game Logic, Copyright 2022, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#pragma once

#include <Abilities/GameplayAbility.h>

#include "Abilities/PF2GameplayAbilityInterface.h"

#include "PF2GameplayAbilityBase.generated.h"

// =====================================================================================================================
// Forward Declarations (to minimize header dependencies)
// =====================================================================================================================
class IPF2CharacterInterface;
class UInputAction;

// =====================================================================================================================
// Normal Declarations
// =====================================================================================================================
/**
 * Abstract base class for OpenPF2-enabled gameplay abilities.
 *
 * GAs that extend from this base class automatically get the ability to expose an icon, label, and description, and
 * support a default automatic binding to input.
 */
UCLASS(Abstract)
// ReSharper disable once CppClassCanBeFinal
class UPF2GameplayAbilityBase :
	public UGameplayAbility,
	public IPF2GameplayAbilityInterface
{
	GENERATED_BODY()

protected:
	// =================================================================================================================
	// Protected Fields
	// =================================================================================================================
	/**
	 * The icon to represent this ability, for whenever it is displayed to players/users.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="OpenPF2 Appearance")
	UTexture2D* Icon;

	/**
	 * The name of this ability, for whenever it is displayed to players/users.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="OpenPF2 Appearance")
	FText Label;

	/**
	 * The description of this ability, for whenever it is displayed to players/users.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="OpenPF2 Appearance")
	FText Description;

	/**
	 * The default input action that triggers this ability (if applicable).
	 *
	 * This is used to pre-populate bindings for this ability. If left blank, this ability has no default binding and
	 * must be assigned a binding at run-time. If populated, the input action can still be overridden at run-time (e.g.,
	 * if you are writing a game in which the player can remap keys).
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="OpenPF2 Input")
	UInputAction* DefaultInputActionMapping;

public:
	// =================================================================================================================
	// Public Methods - IPF2LogIdentifiableInterface Implementation
	// =================================================================================================================
	UFUNCTION(BlueprintCallable)
	virtual FString GetIdForLogs() const override;

	// =================================================================================================================
	// Public Methods - IPF2GameplayAbilityInterface Implementation
	// =================================================================================================================
	UFUNCTION(BlueprintCallable)
	virtual UTexture2D* GetAbilityIcon() const override;

	UFUNCTION(BlueprintCallable)
	virtual FText GetAbilityLabel() const override;

	UFUNCTION(BlueprintCallable)
	virtual FText GetAbilityDescription() const override;

	UFUNCTION(BlueprintCallable)
	virtual UInputAction* GetDefaultInputActionMapping() const override;

	UFUNCTION(BlueprintCallable)
	virtual FGameplayAbilitySpec ToGameplayAbilitySpecForCharacter(
		const TScriptInterface<IPF2CharacterInterface> Character,
		bool& bOutSpecFound
	) const override;

	UFUNCTION(BlueprintCallable)
	virtual FGameplayAbilitySpecHandle ToGameplayAbilitySpecHandleForCharacter(
		const TScriptInterface<IPF2CharacterInterface> Character,
		bool& bOutSpecHandleFound
	) const override;

protected:
	// =================================================================================================================
	// Protected Methods
	// =================================================================================================================
	/**
	 * Gets the OpenPF2-compatible character to which this ability has been granted.
	 *
	 * May be null if this ability has been instantiated but not yet been granted to a character.
	 */
	UFUNCTION(BlueprintCallable, Category="OpenPF2|Gameplay Abilities")
	TScriptInterface<IPF2CharacterInterface> GetOwningCharacterFromActorInfo() const;
};

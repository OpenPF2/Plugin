// OpenPF2 Game Framework for Unreal Engine, Copyright 2022-2024, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#pragma once

#include "PF2GameplayAbilityBase.h"

#include <UObject/ScriptInterface.h>

#include "PF2InteractableAbilityBase.generated.h"

// =====================================================================================================================
// Forward Declarations (to minimize header dependencies)
// =====================================================================================================================
class IPF2CharacterInterface;
class UTexture2D;

// =====================================================================================================================
// Normal Declarations
// =====================================================================================================================
/**
 * Abstract base class for OpenPF2 gameplay abilities that the player can interact with and see in the UI.
 *
 * GAs that extend from this base class automatically get the ability to expose an icon, label, and description, and
 * support a default automatic binding to input.
 */
UCLASS(Abstract)
// ReSharper disable once CppClassCanBeFinal
class UPF2InteractableAbilityBase :
	public UPF2GameplayAbilityBase,
	public IPF2InteractableAbilityInterface
{
	GENERATED_BODY()

protected:
	// =================================================================================================================
	// Protected Constants
	// =================================================================================================================
	/**
	 * The name of the gameplay tag that is applied to abilities any player can activate.
	 */
	static inline FName CommonAbilityTagName = FName(TEXT("Trait.Ability.Common"));

	// =================================================================================================================
	// Protected Static Fields
	// =================================================================================================================
	/**
	 * The gameplay tag that applies to "common" abilities, which is the default for interactable abilities.
	 *
	 * This is cached for performance.
	 */
	inline static FGameplayTag CommonAbilityTag = FGameplayTag();

	// =================================================================================================================
	// Protected Fields
	// =================================================================================================================
	/**
	 * The icon to represent this ability, for whenever it is displayed to players/users.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="OpenPF2 - Ability Appearance")
	UTexture2D* Icon;

	/**
	 * The name of this ability, for whenever it is displayed to players/users.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="OpenPF2 - Ability Appearance")
	FText Label;

	/**
	 * The description of this ability, for whenever it is displayed to players/users.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="OpenPF2 - Ability Appearance")
	FText Description;

public:
	// =================================================================================================================
	// Public Constructors
	// =================================================================================================================
	/**
	 * Default constructor for UPF2InteractableAbilityBase.
	 */
	explicit UPF2InteractableAbilityBase();

	// =================================================================================================================
	// Public Methods - IPF2LogIdentifiableInterface Implementation
	// =================================================================================================================
	virtual FString GetIdForLogs() const override;

	// =================================================================================================================
	// Public Methods - IPF2GameplayAbilityInterface Implementation
	// =================================================================================================================
	virtual UGameplayAbility* ToGameplayAbility() override;

	virtual FGameplayAbilitySpec ToGameplayAbilitySpecForCharacter(
		const TScriptInterface<IPF2CharacterInterface> Character,
		bool&                                          bOutSpecFound
	) const override;

	virtual FGameplayAbilitySpecHandle ToGameplayAbilitySpecHandleForCharacter(
		const TScriptInterface<IPF2CharacterInterface> Character,
		bool&                                          bOutSpecHandleFound
	) const override;

	// =================================================================================================================
	// Public Methods - IPF2InteractableAbilityInterface Implementation
	// =================================================================================================================
	virtual UTexture2D* GetAbilityIcon() const override;
	virtual FText GetAbilityLabel() const override;
	virtual FText GetAbilityDescription() const override;
};

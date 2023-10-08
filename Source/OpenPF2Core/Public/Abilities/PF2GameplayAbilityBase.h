// OpenPF2 for UE Game Logic, Copyright 2022-2023, Guy Elsmore-Paddock. All Rights Reserved.
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
struct FPF2GameplayEffectContainer;
struct FPF2GameplayEffectContainerSpec;

class IPF2CharacterInterface;
class IPF2WeaponInterface;
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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="OpenPF2 - Appearance")
	UTexture2D* Icon;

	/**
	 * The name of this ability, for whenever it is displayed to players/users.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="OpenPF2 - Appearance")
	FText Label;

	/**
	 * The description of this ability, for whenever it is displayed to players/users.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="OpenPF2 - Appearance")
	FText Description;

public:
	// =================================================================================================================
	// Public Methods - IPF2LogIdentifiableInterface Implementation
	// =================================================================================================================
	virtual FString GetIdForLogs() const override;

	// =================================================================================================================
	// Public Methods - IPF2GameplayAbilityInterface Implementation
	// =================================================================================================================
	virtual UTexture2D* GetAbilityIcon() const override;

	virtual FText GetAbilityLabel() const override;

	virtual FText GetAbilityDescription() const override;

	virtual UGameplayAbility* ToGameplayAbility() override;

	virtual FGameplayAbilitySpec ToGameplayAbilitySpecForCharacter(
		const TScriptInterface<IPF2CharacterInterface> Character,
		bool& bOutSpecFound
	) const override;

	virtual FGameplayAbilitySpecHandle ToGameplayAbilitySpecHandleForCharacter(
		const TScriptInterface<IPF2CharacterInterface> Character,
		bool& bOutSpecHandleFound
	) const override;

protected:
	// =================================================================================================================
	// Protected Methods
	// =================================================================================================================
	/**
	 * Gets the handle of the ability specification for the current activation.
	 *
	 * @return
	 *	The handle of the active ability.
	 */
	UFUNCTION(BlueprintCallable, Category="OpenPF2|Gameplay Abilities")
	FGameplayAbilitySpecHandle GetSpecHandleOfCurrentActivation() const;

	/**
	 * Gets the OpenPF2-compatible character to which this ability has been granted.
	 *
	 * May be null if this ability has been instantiated but not yet been granted to a character.
	 */
	UFUNCTION(BlueprintCallable, Category="OpenPF2|Gameplay Abilities")
	TScriptInterface<IPF2CharacterInterface> GetOwningCharacterFromActorInfo() const;

	/**
	 * Processes a gameplay effect (GE) container into a gameplay effect container spec.
	 *
	 * @param Container
	 *	The GE container to process.
	 *
	 * @return
	 *	The GE container spec created from the GE container.
	 */
	UFUNCTION(BlueprintCallable, Category="OpenPF2|Gameplay Abilities")
	FPF2GameplayEffectContainerSpec MakeEffectContainerSpecFromContainer(
		const FPF2GameplayEffectContainer& Container) const;

	/**
	 * Processes a gameplay effect (GE) container into a gameplay effect container spec with the given weapon as source.
	 *
	 * @param Container
	 *	The GE container to process.
	 * @param Weapon
	 *	The weapon to make the source of all GEs in the resulting spec.
	 * @param Level
	 *
	 * @return
	 *	The GE container spec created from the GE container.
	 */
	UFUNCTION(BlueprintCallable, Category="OpenPF2|Gameplay Abilities")
	FPF2GameplayEffectContainerSpec MakeEffectContainerSpecFromContainerAndWeapon(
		const FPF2GameplayEffectContainer&          Container,
		const TScriptInterface<IPF2WeaponInterface> Weapon,
		const float                                 Level = 1.0f) const;

	/**
	 * Processes a gameplay effect (GE) container into a gameplay effect container spec with the given effect causer.
	 *
	 * @param Container
	 *	The GE container to process.
	 * @param EffectCauser
	 *	The physical actor that is the source of all the effects (e.g., the source of damage), such as a sword or
	 *	projectile. If the effect/damage is being done by bare fists or physical contact rather than a weapon, this
	 *	could be the same actor as the instigator.
	 * @param Level
	 *	The level of the ability (for abilities that increase in damage/effect as they are upgraded, etc.)
	 *
	 * @return
	 *	The GE container spec created from the GE container.
	 */
	UFUNCTION(BlueprintCallable, Category="OpenPF2|Gameplay Abilities")
	FPF2GameplayEffectContainerSpec MakeEffectContainerSpecFromContainerAndCauser(
		const FPF2GameplayEffectContainer& Container,
		AActor*                            EffectCauser,
		const float                        Level = 1.0f) const;

	/**
	 * Applies a gameplay effect (GE) container spec to its targets.
	 *
	 * @param ContainerSpec
	 *	The GE container specification.
	 *
	 * @return
	 *	The list of handles for the GEs created and now active on all targets.
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure=false, Category="OpenPF2|Gameplay Abilities")
	TArray<FActiveGameplayEffectHandle> ApplyEffectContainerSpec(
		const FPF2GameplayEffectContainerSpec& ContainerSpec) const;

	/**
	 * Creates an outgoing gameplay effect spec for damage from a weapon.
	 *
	 * @param GameplayEffectClass
	 *	The type of gameplay effect for which a spec is desired.
	 * @param Weapon
	 *	The weapon that actually caused this effect (e.g., did damage), such as a sword or projectile.
	 * @param Level
	 *	The level of the attack (for weapons that increase in damage as they are upgraded, etc.)
	 */
	UFUNCTION(BlueprintCallable, Category="OpenPF2|Gameplay Abilities")
	FGameplayEffectSpecHandle MakeOutgoingGameplayEffectSpecForWeapon(
		const TSubclassOf<UGameplayEffect>          GameplayEffectClass,
		const TScriptInterface<IPF2WeaponInterface> Weapon,
		const float                                 Level = 1.0f) const;

	/**
	 * Creates an outgoing gameplay effect spec that has a custom effect causer.
	 *
	 * This is similar to MakeOutgoingGameplayEffectSpec() except that the effect causer can be set rather than it being
	 * set to the "avatar actor" which, in many games, is identical to the "owner actor" that is used as the instigator,
	 * which is the actor/character who owns the Ability System Component (ASC).
	 *
	 * @param GameplayEffectClass
	 *	The type of gameplay effect for which a spec is desired.
	 * @param EffectCauser
	 *	The physical actor that actually caused this effect (e.g., did damage), such as a weapon or projectile. If
	 *	the effect/damage is being done by bare fists or physical contact rather than a weapon, this could be the same
	 *	actor as the instigator.
	 * @param Level
	 *	The level of the ability (for abilities that increase in damage/effect as they are upgraded, etc.)
	 */
	UFUNCTION(BlueprintCallable, Category="OpenPF2|Gameplay Abilities")
	FGameplayEffectSpecHandle MakeOutgoingGameplayEffectSpecForCauser(
		const TSubclassOf<UGameplayEffect> GameplayEffectClass,
		AActor*                            EffectCauser,
		const float                        Level = 1.0f) const;

	/**
	 * Creates an outgoing gameplay effect spec that has a custom effect causer.
	 *
	 * This is similar to MakeOutgoingGameplayEffectSpec() except that the effect causer can be set rather than it being
	 * set equal to the "avatar actor" which, in many games, is identical to the "owner actor" that is used as the
	 * instigator, the actor/character who owns the Ability System Component (ASC).
	 *
	 * @param AbilityHandle
	 *	The handle for the current gameplay ability activation, which is generating the outgoing gameplay effect spec.
	 * @param AbilityOwnerInfo
	 *	Information about the actor who activated this gameplay ability.
	 * @param GameplayEffectClass
	 *	The type of gameplay effect for which a spec is desired.
	 * @param EffectCauser
	 *	The physical actor that actually caused this effect (e.g., did damage), such as a weapon or projectile. If
	 *	the effect/damage is being done by bare fists or physical contact rather than a weapon, this could be the same
	 *	actor as the instigator.
	 * @param Level
	 *	The level of the ability (for abilities that increase in damage/effect as they are upgraded, etc.)
	 */
	FGameplayEffectSpecHandle MakeOutgoingGameplayEffectSpecForCauser(
		const FGameplayAbilitySpecHandle   AbilityHandle,
		const FGameplayAbilityActorInfo*   AbilityOwnerInfo,
		const TSubclassOf<UGameplayEffect> GameplayEffectClass,
		AActor*                            EffectCauser,
		const float                        Level = 1.0f) const;

	/**
	 * Builds context for a gameplay effect activation triggered by the specified ability, owner, and effect causer.
	 *
	 * @param AbilityHandle
	 *	The handle for the current gameplay ability activation, which is generating the outgoing gameplay effect spec.
	 * @param AbilityOwnerInfo
	 *	Information about the actor who activated this gameplay ability.
	 * @param EffectCauser
	 *	The physical actor that actually caused this effect (e.g., did damage), such as a weapon or projectile. If
	 *	the effect/damage is being done by bare fists or physical contact rather than a weapon, this could be the same
	 *	actor as the instigator.
	 *
	 * @return
	 *	The new gameplay effect context.
	 */
	FGameplayEffectContextHandle MakeEffectContextForCauser(const FGameplayAbilitySpecHandle AbilityHandle,
	                                                        const FGameplayAbilityActorInfo* AbilityOwnerInfo,
	                                                        AActor*                          EffectCauser) const;
};

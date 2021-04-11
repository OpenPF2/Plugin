// Based on "Action RPG Sample", Copyright 2020, Epic Games, Inc. All Rights Reserved.
// Teen Wolf RPG game logic, Copyright 2021, Teen Wolf RPG. All Rights Reserved.
// Content from Pathfinder 2nd Edition is licensed under the Open Game License (OGL) v1.0a, subject to the following:
//	 - Open Game License v 1.0a, Copyright 2000, Wizards of the Coast, Inc.
//	 - System Reference Document, Copyright 2000, Wizards of the Coast, Inc.
//	 - Pathfinder Core Rulebook (Second Edition), Copyright 2019, Paizo Inc.
// Except for material designated as Product Identity or External Tools, the game mechanics of this Teen Wolf RPG
// product are Open Game Content, as defined in the Open Game License version 1.0a, Section 1(d) (see accompanying
// LICENSE.TXT). No portion of this work other than the material designated as Open Game Content may be reproduced in
// any form without written permission.
#pragma once

#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "RPGAttributeSet.generated.h"

// Uses macros from AttributeSet.h
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/** This holds all of the attributes used by abilities, it instantiates a copy of this on every character */
UCLASS()
class ACTIONRPG_API URPGAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:

	// Constructor and overrides
	URPGAttributeSet();
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	// =================================================================================================================
	// Pathfinder 2e Stats Shared by Both PCs and NPCs
	// =================================================================================================================

	/**
	 * All creatures and objects have Hit Points (HP).
	 *
	 * Creatures cannot be reduced to fewer than 0 Hit Points. When most creatures reach 0 Hit Points, they die and are
	 * removed from play unless the attack was nonlethal, in which case they are instead knocked out for a significant
	 * amount of time (usually 1 minute or more).
	 *
	 * Player characters, their companions, and other significant characters and creatures don’t automatically die when
	 * they reach 0 Hit Points. Instead, they are knocked out and are at risk of death.
	 *
	 * Capped by MaxHitPoints.
	 */
	UPROPERTY(BlueprintReadOnly, Category = "HitPoints", ReplicatedUsing=OnRep_HitPoints)
	FGameplayAttributeData HitPoints;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, HitPoints)

	/** The maximum number of hit points for this character (for modification via GameplayEffects). */
	UPROPERTY(BlueprintReadOnly, Category = "HitPoints", ReplicatedUsing=OnRep_MaxHitPoints)
	FGameplayAttributeData MaxHitPoints;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, MaxHitPoints)

	/**
	 * Strength measures a character’s physical power.
	 *
	 * Strength is important for characters who engage in hand-to-hand combat. The Strength modifier gets added to melee
	 * damage rolls and determines how much a character can carry.
	 */
	UPROPERTY(BlueprintReadOnly, Category = "Ability Scores", ReplicatedUsing=OnRep_AbStrengthModifier)
	FGameplayAttributeData AbStrengthModifier;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, AbStrengthModifier)

	/**
	 * Dexterity measures a character’s agility, balance, and reflexes.
	 *
	 * Dexterity is important if a character makes attacks with ranged weapons or uses stealth to surprise others. The
	 * Dexterity modifier is also added to a character’s AC and Reflex saving throws.
	 */
	UPROPERTY(BlueprintReadOnly, Category = "Ability Scores", ReplicatedUsing=OnRep_AbDexterityModifier)
	FGameplayAttributeData AbDexterityModifier;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, AbDexterityModifier)

	/**
	 * Constitution measures a character’s overall health and stamina.
	 *
	 * Constitution is an important statistic for all characters, especially those who fight in close combat. The
	 * Constitution modifier is added to its Hit Points and Fortitude saving throws.
	 */
	UPROPERTY(BlueprintReadOnly, Category = "Ability Scores", ReplicatedUsing=OnRep_AbConstitutionModifier)
	FGameplayAttributeData AbConstitutionModifier;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, AbConstitutionModifier)

	/**
	* Intelligence measures how well a character can learn and reason.
	*
	* A high Intelligence allows a character to analyze situations and understand patterns, and unlocks the ability to
	* become trained in additional skills and the ability to master additional languages.
	*/
	UPROPERTY(BlueprintReadOnly, Category = "Ability Scores", ReplicatedUsing=OnRep_AbIntelligenceModifier)
	FGameplayAttributeData AbIntelligenceModifier;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, AbIntelligenceModifier)

	/**
	 * Wisdom measures a character’s common sense, awareness, and intuition.
	 *
	 * The Wisdom modifier is added to its Perception and Will saving throws.
	 */
	UPROPERTY(BlueprintReadOnly, Category = "Ability Scores", ReplicatedUsing=OnRep_AbWisdomModifier)
	FGameplayAttributeData AbWisdomModifier;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, AbWisdomModifier)

	/**
	 * Charisma measures a character’s personal magnetism and strength of personality.
	 *
	 * A high Charisma score helps a character influence the thoughts and moods of others.
	 */
	UPROPERTY(BlueprintReadOnly, Category = "Ability Scores", ReplicatedUsing=OnRep_AbCharismaModifier)
	FGameplayAttributeData AbCharismaModifier;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, AbCharismaModifier)

	/**
	 * The Difficulty Class based on this character's class.
	 *
	 * This controls how hard or easy certain types of tasks are for this character.
	 */
	UPROPERTY(BlueprintReadOnly, Category = "Class DC", ReplicatedUsing=OnRep_CdcDifficultyClass)
	FGameplayAttributeData CdcDifficultyClass;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, CdcDifficultyClass)

	/** How fast this character can move. */
	UPROPERTY(BlueprintReadOnly, Category = "Speed", ReplicatedUsing = OnRep_Speed)
	FGameplayAttributeData Speed;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, Speed)

	/** The maximum speed of this character (for modification via GameplayEffects). */
	UPROPERTY(BlueprintReadOnly, Category = "Speed", ReplicatedUsing = OnRep_MaxSpeed)
	FGameplayAttributeData MaxSpeed;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, MaxSpeed)

	/** A character’s Armor Class represents how difficult they are to hit in combat. */
	UPROPERTY(BlueprintReadOnly, Category = "Armor Class", ReplicatedUsing = OnRep_ArmorClass)
	FGameplayAttributeData ArmorClass;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, ArmorClass)

	/** Fortitude saving throws reduce the effects of abilities and afflictions that can debilitate the body. */
	UPROPERTY(BlueprintReadOnly, Category = "Saving Throws", ReplicatedUsing = OnRep_StFortitudeModifier)
	FGameplayAttributeData StFortitudeModifier;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, StFortitudeModifier)

	/** Reflex saving throws measure how quickly and gracefully a character responds to a situation. */
	UPROPERTY(BlueprintReadOnly, Category = "Saving Throws", ReplicatedUsing = OnRep_StReflexModifier)
	FGameplayAttributeData StReflexModifier;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, StReflexModifier)

	/** Will saving throws measure how well a character resists attacks to mind and spirit. */
	UPROPERTY(BlueprintReadOnly, Category = "Saving Throws", ReplicatedUsing = OnRep_StWillModifier)
	FGameplayAttributeData StWillModifier;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, StWillModifier)

	/**
	 * Perception measures a character's ability to notice hidden objects or unusual situations and affects initiative.
	 */
	UPROPERTY(BlueprintReadOnly, Category = "Perception", ReplicatedUsing = OnRep_PcpPerceptionModifier)
	FGameplayAttributeData PcpPerceptionModifier;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, PcpPerceptionModifier)
	
	// =================================================================================================================
	// Legacy Code from Epic (TODO: Remove)
	// =================================================================================================================
	/** AttackPower of the attacker is multiplied by the base Damage to reduce health, so 1.0 means no bonus */
	UPROPERTY(BlueprintReadOnly, Category = "Damage", ReplicatedUsing = OnRep_AttackPower)
	FGameplayAttributeData AttackPower;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, AttackPower)

	/** Base Damage is divided by DefensePower to get actual damage done, so 1.0 means no bonus */
	UPROPERTY(BlueprintReadOnly, Category = "Damage", ReplicatedUsing = OnRep_DefensePower)
	FGameplayAttributeData DefensePower;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, DefensePower)

	/** Damage is a 'temporary' attribute used by the DamageExecution to calculate final damage, which then turns into -HitPoints */
	UPROPERTY(BlueprintReadOnly, Category = "Damage")
	FGameplayAttributeData Damage;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, Damage)

protected:
	/** Helper function to proportionally adjust the value of an attribute when it's associated max attribute changes. (i.e. When MaxHitPoints increases, HitPoints increases by an amount that maintains the same percentage as before) */
	void AdjustAttributeForMaxChange(FGameplayAttributeData& AffectedAttribute, const FGameplayAttributeData& MaxAttribute, float NewMaxValue, const FGameplayAttribute& AffectedAttributeProperty);

	// These OnRep functions exist to make sure that the ability system internal representations are synchronized properly during replication
	UFUNCTION()
	virtual void OnRep_HitPoints(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_MaxHitPoints(const FGameplayAttributeData& OldValue);

	UFUNCTION()
    virtual void OnRep_AbStrengthModifier(const FGameplayAttributeData& OldValue);

	UFUNCTION()
    virtual void OnRep_AbDexterityModifier(const FGameplayAttributeData& OldValue);

	UFUNCTION()
    virtual void OnRep_AbConstitutionModifier(const FGameplayAttributeData& OldValue);

	UFUNCTION()
    virtual void OnRep_AbIntelligenceModifier(const FGameplayAttributeData& OldValue);

	UFUNCTION()
    virtual void OnRep_AbWisdomModifier(const FGameplayAttributeData& OldValue);

	UFUNCTION()
    virtual void OnRep_AbCharismaModifier(const FGameplayAttributeData& OldValue);

	UFUNCTION()
    virtual void OnRep_CdcDifficultyClass(const FGameplayAttributeData& OldValue);

	UFUNCTION()
    virtual void OnRep_Speed(const FGameplayAttributeData& OldValue);

	UFUNCTION()
    virtual void OnRep_MaxSpeed(const FGameplayAttributeData& OldValue);

	UFUNCTION()
    virtual void OnRep_ArmorClass(const FGameplayAttributeData& OldValue);

	UFUNCTION()
    virtual void OnRep_StFortitudeModifier(const FGameplayAttributeData& OldValue);

	UFUNCTION()
    virtual void OnRep_StReflexModifier(const FGameplayAttributeData& OldValue);

	UFUNCTION()
    virtual void OnRep_StWillModifier(const FGameplayAttributeData& OldValue);

	UFUNCTION()
    virtual void OnRep_PcpPerceptionModifier(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_AttackPower(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_DefensePower(const FGameplayAttributeData& OldValue);
};
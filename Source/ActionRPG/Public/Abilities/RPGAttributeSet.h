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

#include <AttributeSet.h>
#include <AbilitySystemComponent.h>
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

	// =================================================================================================================
	// Constructors
	// =================================================================================================================
	URPGAttributeSet();

	// =================================================================================================================
	// Callbacks
	// =================================================================================================================
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	// =================================================================================================================
	// Attributes - Pathfinder 2e Stats Shared by Both PCs and NPCs
	// =================================================================================================================
	/**
	 * Experience Points (XP) track the knowledge a character has earned from facing beasts and traps.
	 *
	 * Each time a character reaches 1,000 XP, their level increases by 1.
	 */
	UPROPERTY(BlueprintReadOnly, Category = "Experience", ReplicatedUsing=OnRep_Experience)
	FGameplayAttributeData Experience;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, Experience)

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
	UPROPERTY(BlueprintReadOnly, Category = "Ability Scores", ReplicatedUsing=OnRep_AbStrength)
	FGameplayAttributeData AbStrength;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, AbStrength)

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
	UPROPERTY(BlueprintReadOnly, Category = "Ability Scores", ReplicatedUsing=OnRep_AbDexterity)
	FGameplayAttributeData AbDexterity;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, AbDexterity)

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
	UPROPERTY(BlueprintReadOnly, Category = "Ability Scores", ReplicatedUsing=OnRep_AbConstitution)
	FGameplayAttributeData AbConstitution;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, AbConstitution)

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
	UPROPERTY(BlueprintReadOnly, Category = "Ability Scores", ReplicatedUsing=OnRep_AbIntelligence)
	FGameplayAttributeData AbIntelligence;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, AbIntelligence)

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
	UPROPERTY(BlueprintReadOnly, Category = "Ability Scores", ReplicatedUsing=OnRep_AbWisdom)
	FGameplayAttributeData AbWisdom;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, AbWisdom)

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
	UPROPERTY(BlueprintReadOnly, Category = "Ability Scores", ReplicatedUsing=OnRep_AbCharisma)
	FGameplayAttributeData AbCharisma;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, AbCharisma)

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

	/**
	 * Acrobatics measures a character's ability to perform tasks requiring coordination and grace.
	 */
	UPROPERTY(BlueprintReadOnly, Category = "Skills", ReplicatedUsing = OnRep_SkAcrobaticsProficiency)
	FGameplayAttributeData SkAcrobaticsProficiency;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, SkAcrobaticsProficiency)

	/**
	 * Arcana measures how much a character knows about arcane magic and creatures.
	 */
	UPROPERTY(BlueprintReadOnly, Category = "Skills", ReplicatedUsing = OnRep_SkArcanaProficiency)
	FGameplayAttributeData SkArcanaProficiency;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, SkArcanaProficiency)

	/**
	 * Athletics allows a character to perform deeds of physical prowess.
	 */
	UPROPERTY(BlueprintReadOnly, Category = "Skills", ReplicatedUsing = OnRep_SkAthleticsProficiency)
	FGameplayAttributeData SkAthleticsProficiency;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, SkAthleticsProficiency)

	/**
	 * Crafting allows a character to create and repair items.
	 */
	UPROPERTY(BlueprintReadOnly, Category = "Skills", ReplicatedUsing = OnRep_SkCraftingProficiency)
	FGameplayAttributeData SkCraftingProficiency;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, SkCraftingProficiency)

	/**
	 * Deception allows a character to trick and mislead others using disguises, lies, and other forms of subterfuge.
	 */
	UPROPERTY(BlueprintReadOnly, Category = "Skills", ReplicatedUsing = OnRep_SkDeceptionProficiency)
	FGameplayAttributeData SkDeceptionProficiency;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, SkDeceptionProficiency)

	/**
	 * Diplomacy allows a character to influence others through negotiation and flattery.
	 */
	UPROPERTY(BlueprintReadOnly, Category = "Skills", ReplicatedUsing = OnRep_SkDiplomacyProficiency)
	FGameplayAttributeData SkDiplomacyProficiency;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, SkDiplomacyProficiency)

	/**
	 * Intimidation allows a character to bend others to their will using threats.
	 */
	UPROPERTY(BlueprintReadOnly, Category = "Skills", ReplicatedUsing = OnRep_SkIntimidationProficiency)
	FGameplayAttributeData SkIntimidationProficiency;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, SkIntimidationProficiency)

	/**
	 * Lore gives a character specialized information on a narrow topic.
	 */
	UPROPERTY(BlueprintReadOnly, Category = "Skills", ReplicatedUsing = OnRep_SkLore1Modifier)
	FGameplayAttributeData SkLore1Modifier;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, SkLore1Modifier)

	/**
	 * Lore gives a character specialized information on a narrow topic.
	 */
	UPROPERTY(BlueprintReadOnly, Category = "Skills", ReplicatedUsing = OnRep_SkLore2Modifier)
	FGameplayAttributeData SkLore2Modifier;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, SkLore2Modifier)

	/**
	 * Medicine allows a character to patch up wounds and help people recover from diseases and poisons.
	 */
	UPROPERTY(BlueprintReadOnly, Category = "Skills", ReplicatedUsing = OnRep_SkMedicineProficiency)
	FGameplayAttributeData SkMedicineProficiency;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, SkMedicineProficiency)

	/**
	 * Nature gives a character knowledge about the natural world, including commanding and training animals and beasts.
	 */
	UPROPERTY(BlueprintReadOnly, Category = "Skills", ReplicatedUsing = OnRep_SkNatureProficiency)
	FGameplayAttributeData SkNatureProficiency;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, SkNatureProficiency)

	/**
	 * Occultism gives a character knowledge about ancient philosophies, esoteric lore, obscure mysticism, and
	 * supernatural creatures.
	 */
	UPROPERTY(BlueprintReadOnly, Category = "Skills", ReplicatedUsing = OnRep_SkOccultismProficiency)
	FGameplayAttributeData SkOccultismProficiency;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, SkOccultismProficiency)

	/**
	 * Performance gives a character skill impressing crowds by performing live.
	 */
	UPROPERTY(BlueprintReadOnly, Category = "Skills", ReplicatedUsing = OnRep_SkPerformanceProficiency)
	FGameplayAttributeData SkPerformanceProficiency;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, SkPerformanceProficiency)

	/**
	 * Religion gives a character knowledge of the secrets of deities, dogma, faith, and the realms of divine
	 * creatures -- both sublime and sinister.
	 */
	UPROPERTY(BlueprintReadOnly, Category = "Skills", ReplicatedUsing = OnRep_SkReligionProficiency)
	FGameplayAttributeData SkReligionProficiency;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, SkReligionProficiency)

	/**
	 * Society gives a character an understanding of the people and systems that make civilization run, including the
	 * historical events that make societies what they are today.
	 */
	UPROPERTY(BlueprintReadOnly, Category = "Skills", ReplicatedUsing = OnRep_SkSocietyProficiency)
	FGameplayAttributeData SkSocietyProficiency;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, SkSocietyProficiency)

	/**
	 * Stealth gives a character the ability to avoid detection, slip past foes, hide, and conceal items.
	 */
	UPROPERTY(BlueprintReadOnly, Category = "Skills", ReplicatedUsing = OnRep_SkStealthProficiency)
	FGameplayAttributeData SkStealthProficiency;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, SkStealthProficiency)

	/**
	 * Survival gives a character aptitude to live in the wilderness, foraging for food, and building shelter.
	 */
	UPROPERTY(BlueprintReadOnly, Category = "Skills", ReplicatedUsing = OnRep_SkSurvivalProficiency)
	FGameplayAttributeData SkSurvivalProficiency;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, SkSurvivalProficiency)

	/**
	 * Thievery gives a character training in the particular set of skills favored by thieves and miscreants.
	 */
	UPROPERTY(BlueprintReadOnly, Category = "Skills", ReplicatedUsing = OnRep_SkThieveryProficiency)
	FGameplayAttributeData SkThieveryProficiency;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, SkThieveryProficiency)

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

	/**
	 * Damage is a 'temporary' attribute used by the DamageExecution to calculate final damage.
	 *
	 * This turns into -HitPoints.
	 */
	UPROPERTY(BlueprintReadOnly, Category = "Damage")
	FGameplayAttributeData Damage;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, Damage)

protected:
	/**
	 * Helper function to proportionally adjust the value of an attribute when it's associated max attribute changes.
	 *
	 * (i.e. When MaxHitPoints increases, HitPoints increases by an amount that maintains the same percentage as
	 * before).
	 */
	void AdjustAttributeForMaxChange(FGameplayAttributeData& AffectedAttribute,
									 const FGameplayAttributeData& MaxAttribute,
									 float NewMaxValue,
									 const FGameplayAttribute& AffectedAttributeProperty);

	// These OnRep functions exist to make sure that the ability system internal representations are synchronized
	// properly during replication.
	UFUNCTION()
    virtual void OnRep_Experience(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_HitPoints(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_MaxHitPoints(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_AbStrength(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_AbStrengthModifier(const FGameplayAttributeData& OldValue);

	UFUNCTION()
    virtual void OnRep_AbDexterity(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_AbDexterityModifier(const FGameplayAttributeData& OldValue);

	UFUNCTION()
    virtual void OnRep_AbConstitution(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_AbConstitutionModifier(const FGameplayAttributeData& OldValue);

	UFUNCTION()
    virtual void OnRep_AbIntelligence(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_AbIntelligenceModifier(const FGameplayAttributeData& OldValue);

	UFUNCTION()
    virtual void OnRep_AbWisdom(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_AbWisdomModifier(const FGameplayAttributeData& OldValue);

	UFUNCTION()
    virtual void OnRep_AbCharisma(const FGameplayAttributeData& OldValue);

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
    virtual void OnRep_SkAcrobaticsProficiency(const FGameplayAttributeData& OldValue);

	UFUNCTION()
    virtual void OnRep_SkArcanaProficiency(const FGameplayAttributeData& OldValue);

	UFUNCTION()
    virtual void OnRep_SkAthleticsProficiency(const FGameplayAttributeData& OldValue);

	UFUNCTION()
    virtual void OnRep_SkCraftingProficiency(const FGameplayAttributeData& OldValue);

	UFUNCTION()
    virtual void OnRep_SkDeceptionProficiency(const FGameplayAttributeData& OldValue);

	UFUNCTION()
    virtual void OnRep_SkDiplomacyProficiency(const FGameplayAttributeData& OldValue);

	UFUNCTION()
    virtual void OnRep_SkIntimidationProficiency(const FGameplayAttributeData& OldValue);

	UFUNCTION()
    virtual void OnRep_SkLore1Modifier(const FGameplayAttributeData& OldValue);

	UFUNCTION()
    virtual void OnRep_SkLore2Modifier(const FGameplayAttributeData& OldValue);

	UFUNCTION()
    virtual void OnRep_SkMedicineProficiency(const FGameplayAttributeData& OldValue);

	UFUNCTION()
    virtual void OnRep_SkNatureProficiency(const FGameplayAttributeData& OldValue);

	UFUNCTION()
    virtual void OnRep_SkOccultismProficiency(const FGameplayAttributeData& OldValue);

	UFUNCTION()
    virtual void OnRep_SkPerformanceProficiency(const FGameplayAttributeData& OldValue);

	UFUNCTION()
    virtual void OnRep_SkReligionProficiency(const FGameplayAttributeData& OldValue);

	UFUNCTION()
    virtual void OnRep_SkSocietyProficiency(const FGameplayAttributeData& OldValue);

	UFUNCTION()
    virtual void OnRep_SkStealthProficiency(const FGameplayAttributeData& OldValue);

	UFUNCTION()
    virtual void OnRep_SkSurvivalProficiency(const FGameplayAttributeData& OldValue);

	UFUNCTION()
    virtual void OnRep_SkThieveryProficiency(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_AttackPower(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_DefensePower(const FGameplayAttributeData& OldValue);
};

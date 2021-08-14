// OpenPF2 for UE Game Logic, Copyright 2021, Guy Elsmore-Paddock. All Rights Reserved.
//
// Content from Pathfinder 2nd Edition is licensed under the Open Game License (OGL) v1.0a, subject to the following:
//	 - Open Game License v 1.0a, Copyright 2000, Wizards of the Coast, Inc.
//	 - System Reference Document, Copyright 2000, Wizards of the Coast, Inc.
//	 - Pathfinder Core Rulebook (Second Edition), Copyright 2019, Paizo Inc.
// Except for material designated as Product Identity, the game mechanics and logic in this file are Open Game Content,
// as defined in the Open Game License version 1.0a, Section 1(d) (see accompanying LICENSE.TXT). No portion of this
// file other than the material designated as Open Game Content may be reproduced in any form without written
// permission.

#pragma once

#include <AttributeSet.h>
#include <AbilitySystemComponent.h>
#include "PF2AttributeSet.generated.h"

// Uses macros from AttributeSet.h
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/** This holds all of the attributes used by abilities, it instantiates a copy of this on every character */
UCLASS()
class OPENPF2CORE_API UPF2AttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:

	// =================================================================================================================
	// Constructors
	// =================================================================================================================
	UPF2AttributeSet();

	// =================================================================================================================
	// Callbacks
	// =================================================================================================================
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	// =================================================================================================================
	// Attributes - Stats Shared by Both PCs and NPCs
	// =================================================================================================================
	/**
	 * Experience Points (XP) track the knowledge a character has earned from facing beasts and traps.
	 *
	 * From the Pathfinder 2E Core Rulebook, page 8, "Defining Characteristics":
	 * "Every time a character amasses 1,000 XP, they go up a level, gaining new abilities so they can take on even
	 * greater challenges. A 1st-level PC might face off against a giant rat or a group of bandits, but at 20th level,
	 * that same character might be able to bring ruin to an entire city with a single spell."
	 *
	 * From the Pathfinder 2E Core Rulebook, page 507, "Experience Points":
	 * "As characters adventure, they earn Experience Points (XP). These awards come from achieving goals, completing
	 * social encounters, exploring new places, fighting monsters, overcoming hazards, and other sorts of deeds.
	 * ...
	 * Normally, when a player character reaches 1,000 XP or more, they level up, reduce their XP by 1,000, and start
	 * progressing toward the next level."
	 */
	UPROPERTY(BlueprintReadOnly, Category = "Experience", ReplicatedUsing=OnRep_Experience)
	FGameplayAttributeData Experience;
	ATTRIBUTE_ACCESSORS(UPF2AttributeSet, Experience)

	/**
	 * All creatures and objects have Hit Points (HP).
	 *
	 * From the Pathfinder 2E Core Rulebook, page 459, "Knocked Out and Dying":
	 * "Creatures cannot be reduced to fewer than 0 Hit Points. When most creatures reach 0 Hit Points, they die and are
	 * removed from play unless the attack was nonlethal, in which case they are instead knocked out for a significant
	 * amount of time (usually 1 minute or more).
	 *
	 * Player characters, their companions, and other significant characters and creatures don’t automatically die when
	 * they reach 0 Hit Points. Instead, they are knocked out and are at risk of death."
	 *
	 * Capped by MaxHitPoints.
	 */
	UPROPERTY(BlueprintReadOnly, Category = "HitPoints", ReplicatedUsing=OnRep_HitPoints)
	FGameplayAttributeData HitPoints;
	ATTRIBUTE_ACCESSORS(UPF2AttributeSet, HitPoints)

	/** The maximum number of hit points for this character. */
	UPROPERTY(BlueprintReadOnly, Category = "HitPoints", ReplicatedUsing=OnRep_MaxHitPoints)
	FGameplayAttributeData MaxHitPoints;
	ATTRIBUTE_ACCESSORS(UPF2AttributeSet, MaxHitPoints)

	/**
	 * Strength measures a character’s physical power.
	 *
	 * Strength is important for characters who engage in hand-to-hand combat. The Strength modifier gets added to melee
	 * damage rolls and determines how much a character can carry. (Pathfinder 2E Core Rulebook, page 19)
	 */
	UPROPERTY(BlueprintReadOnly, Category = "Ability Scores", ReplicatedUsing=OnRep_AbStrength)
	FGameplayAttributeData AbStrength;
	ATTRIBUTE_ACCESSORS(UPF2AttributeSet, AbStrength)

	/**
	 * Strength measures a character’s physical power.
	 *
	 * Strength is important for characters who engage in hand-to-hand combat. The Strength modifier gets added to melee
	 * damage rolls and determines how much a character can carry.
	 * (Pathfinder 2E Core Rulebook, page 19)
	 */
	UPROPERTY(BlueprintReadOnly, Category = "Ability Scores", ReplicatedUsing=OnRep_AbStrengthModifier)
	FGameplayAttributeData AbStrengthModifier;
	ATTRIBUTE_ACCESSORS(UPF2AttributeSet, AbStrengthModifier)

	/**
	 * Dexterity measures a character’s agility, balance, and reflexes.
	 *
	 * Dexterity is important if a character makes attacks with ranged weapons or uses stealth to surprise others. The
	 * Dexterity modifier is also added to a character’s AC and Reflex saving throws.
	 * (Pathfinder 2E Core Rulebook, page 19)
	 */
	UPROPERTY(BlueprintReadOnly, Category = "Ability Scores", ReplicatedUsing=OnRep_AbDexterity)
	FGameplayAttributeData AbDexterity;
	ATTRIBUTE_ACCESSORS(UPF2AttributeSet, AbDexterity)

	/**
	 * Dexterity measures a character’s agility, balance, and reflexes.
	 *
	 * Dexterity is important if a character makes attacks with ranged weapons or uses stealth to surprise others. The
	 * Dexterity modifier is also added to a character’s AC and Reflex saving throws.
	 * (Pathfinder 2E Core Rulebook, page 19)
	 */
	UPROPERTY(BlueprintReadOnly, Category = "Ability Scores", ReplicatedUsing=OnRep_AbDexterityModifier)
	FGameplayAttributeData AbDexterityModifier;
	ATTRIBUTE_ACCESSORS(UPF2AttributeSet, AbDexterityModifier)

	/**
	 * Constitution measures a character’s overall health and stamina.
	 *
	 * Constitution is an important statistic for all characters, especially those who fight in close combat. The
	 * Constitution modifier is added to its Hit Points and Fortitude saving throws.
	 * (Pathfinder 2E Core Rulebook, page 19)
	 */
	UPROPERTY(BlueprintReadOnly, Category = "Ability Scores", ReplicatedUsing=OnRep_AbConstitution)
	FGameplayAttributeData AbConstitution;
	ATTRIBUTE_ACCESSORS(UPF2AttributeSet, AbConstitution)

	/**
	 * Constitution measures a character’s overall health and stamina.
	 *
	 * Constitution is an important statistic for all characters, especially those who fight in close combat. The
	 * Constitution modifier is added to its Hit Points and Fortitude saving throws.
	 * (Pathfinder 2E Core Rulebook, page 19)
	 */
	UPROPERTY(BlueprintReadOnly, Category = "Ability Scores", ReplicatedUsing=OnRep_AbConstitutionModifier)
	FGameplayAttributeData AbConstitutionModifier;
	ATTRIBUTE_ACCESSORS(UPF2AttributeSet, AbConstitutionModifier)

	/**
	 * Intelligence measures how well a character can learn and reason.
	 *
	 * A high Intelligence allows a character to analyze situations and understand patterns, and unlocks the ability to
	 * become trained in additional skills and the ability to master additional languages.
	 * (Pathfinder 2E Core Rulebook, page 19)
	 */
	UPROPERTY(BlueprintReadOnly, Category = "Ability Scores", ReplicatedUsing=OnRep_AbIntelligence)
	FGameplayAttributeData AbIntelligence;
	ATTRIBUTE_ACCESSORS(UPF2AttributeSet, AbIntelligence)

	/**
	 * Intelligence measures how well a character can learn and reason.
	 *
	 * A high Intelligence allows a character to analyze situations and understand patterns, and unlocks the ability to
	 * become trained in additional skills and the ability to master additional languages.
	 * (Pathfinder 2E Core Rulebook, page 19)
	 */
	UPROPERTY(BlueprintReadOnly, Category = "Ability Scores", ReplicatedUsing=OnRep_AbIntelligenceModifier)
	FGameplayAttributeData AbIntelligenceModifier;
	ATTRIBUTE_ACCESSORS(UPF2AttributeSet, AbIntelligenceModifier)

	/**
	 * Wisdom measures a character’s common sense, awareness, and intuition.
	 *
	 * The Wisdom modifier is added to its Perception and Will saving throws.
	 * (Pathfinder 2E Core Rulebook, page 19)
	 */
	UPROPERTY(BlueprintReadOnly, Category = "Ability Scores", ReplicatedUsing=OnRep_AbWisdom)
	FGameplayAttributeData AbWisdom;
	ATTRIBUTE_ACCESSORS(UPF2AttributeSet, AbWisdom)

	/**
	 * Wisdom measures a character’s common sense, awareness, and intuition.
	 *
	 * The Wisdom modifier is added to its Perception and Will saving throws.
	 * (Pathfinder 2E Core Rulebook, page 19)
	 */
	UPROPERTY(BlueprintReadOnly, Category = "Ability Scores", ReplicatedUsing=OnRep_AbWisdomModifier)
	FGameplayAttributeData AbWisdomModifier;
	ATTRIBUTE_ACCESSORS(UPF2AttributeSet, AbWisdomModifier)

	/**
	 * Charisma measures a character’s personal magnetism and strength of personality.
	 *
	 * A high Charisma score helps a character influence the thoughts and moods of others.
	 * (Pathfinder 2E Core Rulebook, page 19)
	 */
	UPROPERTY(BlueprintReadOnly, Category = "Ability Scores", ReplicatedUsing=OnRep_AbCharisma)
	FGameplayAttributeData AbCharisma;
	ATTRIBUTE_ACCESSORS(UPF2AttributeSet, AbCharisma)

	/**
	 * Charisma measures a character’s personal magnetism and strength of personality.
	 *
	 * A high Charisma score helps a character influence the thoughts and moods of others.
	 * (Pathfinder 2E Core Rulebook, page 19)
	 */
	UPROPERTY(BlueprintReadOnly, Category = "Ability Scores", ReplicatedUsing=OnRep_AbCharismaModifier)
	FGameplayAttributeData AbCharismaModifier;
	ATTRIBUTE_ACCESSORS(UPF2AttributeSet, AbCharismaModifier)

	/**
	 * The Difficulty Class (DC) modifier for this character.
	 *
	 * This controls how hard or easy certain types of tasks are for this character.
	 */
	UPROPERTY(BlueprintReadOnly, Category = "Class DC", ReplicatedUsing=OnRep_ClassDifficultyClass)
	FGameplayAttributeData ClassDifficultyClass;
	ATTRIBUTE_ACCESSORS(UPF2AttributeSet, ClassDifficultyClass)

	/** How fast this character can move (in centimeters per second). */
	UPROPERTY(BlueprintReadOnly, Category = "Speed", ReplicatedUsing = OnRep_Speed)
	FGameplayAttributeData Speed;
	ATTRIBUTE_ACCESSORS(UPF2AttributeSet, Speed)

	/** The maximum speed of this character (in centimeters per second). */
	UPROPERTY(BlueprintReadOnly, Category = "Speed", ReplicatedUsing = OnRep_MaxSpeed)
	FGameplayAttributeData MaxSpeed;
	ATTRIBUTE_ACCESSORS(UPF2AttributeSet, MaxSpeed)

	/**
	 * The Armor Class, which represents how hard it is to hit and damage a creature.
	 *
	 * This serves as the Difficulty Class for hitting a creature with an attack.
	 * (Pathfinder 2E Core Rulebook, page 12)
	 */
	UPROPERTY(BlueprintReadOnly, Category = "Armor Class", ReplicatedUsing = OnRep_ArmorClass)
	FGameplayAttributeData ArmorClass;
	ATTRIBUTE_ACCESSORS(UPF2AttributeSet, ArmorClass)

	/**
	 * Fortitude saving throws reduce the effects of abilities and afflictions that can debilitate the body.
	 * (Pathfinder 2E Core Rulebook, page 449)
	 */
	UPROPERTY(BlueprintReadOnly, Category = "Saving Throws", ReplicatedUsing = OnRep_StFortitudeModifier)
	FGameplayAttributeData StFortitudeModifier;
	ATTRIBUTE_ACCESSORS(UPF2AttributeSet, StFortitudeModifier)

	/**
	 * Reflex saving throws measure how quickly and gracefully a character responds to a situation.
	 * (Pathfinder 2E Core Rulebook, page 449)
	 */
	UPROPERTY(BlueprintReadOnly, Category = "Saving Throws", ReplicatedUsing = OnRep_StReflexModifier)
	FGameplayAttributeData StReflexModifier;
	ATTRIBUTE_ACCESSORS(UPF2AttributeSet, StReflexModifier)

	/**
	 * Will saving throws measure how well a character resists attacks to mind and spirit.
	 * (Pathfinder 2E Core Rulebook, page 449)
	 */
	UPROPERTY(BlueprintReadOnly, Category = "Saving Throws", ReplicatedUsing = OnRep_StWillModifier)
	FGameplayAttributeData StWillModifier;
	ATTRIBUTE_ACCESSORS(UPF2AttributeSet, StWillModifier)

	/**
	 * Perception measures a character's ability to notice hidden objects or unusual situations and affects initiative.
	 * (Pathfinder 2E Core Rulebook, page 448)
	 */
	UPROPERTY(BlueprintReadOnly, Category = "Perception", ReplicatedUsing = OnRep_PerceptionModifier)
	FGameplayAttributeData PerceptionModifier;
	ATTRIBUTE_ACCESSORS(UPF2AttributeSet, PerceptionModifier)

	/**
	 * Acrobatics measures a character's ability to perform tasks requiring coordination and grace.
	 * (Pathfinder 2E Core Rulebook, page 240)
	 */
	UPROPERTY(BlueprintReadOnly, Category = "Skills", ReplicatedUsing = OnRep_SkAcrobaticsModifier)
	FGameplayAttributeData SkAcrobaticsModifier;
	ATTRIBUTE_ACCESSORS(UPF2AttributeSet, SkAcrobaticsModifier)

	/**
	 * Arcana measures how much a character knows about arcane magic and creatures.
	 * (Pathfinder 2E Core Rulebook, page 241)
	 */
	UPROPERTY(BlueprintReadOnly, Category = "Skills", ReplicatedUsing = OnRep_SkArcanaModifier)
	FGameplayAttributeData SkArcanaModifier;
	ATTRIBUTE_ACCESSORS(UPF2AttributeSet, SkArcanaModifier)

	/**
	 * Athletics allows a character to perform deeds of physical prowess.
	 * (Pathfinder 2E Core Rulebook, page 241)
	 */
	UPROPERTY(BlueprintReadOnly, Category = "Skills", ReplicatedUsing = OnRep_SkAthleticsModifier)
	FGameplayAttributeData SkAthleticsModifier;
	ATTRIBUTE_ACCESSORS(UPF2AttributeSet, SkAthleticsModifier)

	/**
	 * Crafting allows a character to create and repair items.
	 * (Pathfinder 2E Core Rulebook, page 243)
	 */
	UPROPERTY(BlueprintReadOnly, Category = "Skills", ReplicatedUsing = OnRep_SkCraftingModifier)
	FGameplayAttributeData SkCraftingModifier;
	ATTRIBUTE_ACCESSORS(UPF2AttributeSet, SkCraftingModifier)

	/**
	 * Deception allows a character to trick and mislead others using disguises, lies, and other forms of subterfuge.
	 * (Pathfinder 2E Core Rulebook, page 245)
	 */
	UPROPERTY(BlueprintReadOnly, Category = "Skills", ReplicatedUsing = OnRep_SkDeceptionModifier)
	FGameplayAttributeData SkDeceptionModifier;
	ATTRIBUTE_ACCESSORS(UPF2AttributeSet, SkDeceptionModifier)

	/**
	 * Diplomacy allows a character to influence others through negotiation and flattery.
	 * (Pathfinder 2E Core Rulebook, page 245)
	 */
	UPROPERTY(BlueprintReadOnly, Category = "Skills", ReplicatedUsing = OnRep_SkDiplomacyModifier)
	FGameplayAttributeData SkDiplomacyModifier;
	ATTRIBUTE_ACCESSORS(UPF2AttributeSet, SkDiplomacyModifier)

	/**
	 * Intimidation allows a character to bend others to their will using threats.
	 * (Pathfinder 2E Core Rulebook, page 247)
	 */
	UPROPERTY(BlueprintReadOnly, Category = "Skills", ReplicatedUsing = OnRep_SkIntimidationModifier)
	FGameplayAttributeData SkIntimidationModifier;
	ATTRIBUTE_ACCESSORS(UPF2AttributeSet, SkIntimidationModifier)

	/**
	 * Lore gives a character specialized information on a narrow topic.
	 * (Pathfinder 2E Core Rulebook, page 247)
	 */
	UPROPERTY(BlueprintReadOnly, Category = "Skills", ReplicatedUsing = OnRep_SkLore1Modifier)
	FGameplayAttributeData SkLore1Modifier;
	ATTRIBUTE_ACCESSORS(UPF2AttributeSet, SkLore1Modifier)

	/**
	 * Lore gives a character specialized information on a narrow topic.
	 * (Pathfinder 2E Core Rulebook, page 247)
	 */
	UPROPERTY(BlueprintReadOnly, Category = "Skills", ReplicatedUsing = OnRep_SkLore2Modifier)
	FGameplayAttributeData SkLore2Modifier;
	ATTRIBUTE_ACCESSORS(UPF2AttributeSet, SkLore2Modifier)

	/**
	 * Medicine allows a character to patch up wounds and help people recover from diseases and poisons.
	 * (Pathfinder 2E Core Rulebook, page 248)
	 */
	UPROPERTY(BlueprintReadOnly, Category = "Skills", ReplicatedUsing = OnRep_SkMedicineModifier)
	FGameplayAttributeData SkMedicineModifier;
	ATTRIBUTE_ACCESSORS(UPF2AttributeSet, SkMedicineModifier)

	/**
	 * Nature gives a character knowledge about the natural world, including commanding and training animals and beasts.
	 * (Pathfinder 2E Core Rulebook, page 249)
	 */
	UPROPERTY(BlueprintReadOnly, Category = "Skills", ReplicatedUsing = OnRep_SkNatureModifier)
	FGameplayAttributeData SkNatureModifier;
	ATTRIBUTE_ACCESSORS(UPF2AttributeSet, SkNatureModifier)

	/**
	 * Occultism gives a character knowledge about ancient philosophies, esoteric lore, obscure mysticism, and
	 * supernatural creatures.
	 *
	 * (Pathfinder 2E Core Rulebook, page 249)
	 */
	UPROPERTY(BlueprintReadOnly, Category = "Skills", ReplicatedUsing = OnRep_SkOccultismModifier)
	FGameplayAttributeData SkOccultismModifier;
	ATTRIBUTE_ACCESSORS(UPF2AttributeSet, SkOccultismModifier)

	/**
	 * Performance gives a character skill impressing crowds by performing live.
	 * (Pathfinder 2E Core Rulebook, page 250)
	 */
	UPROPERTY(BlueprintReadOnly, Category = "Skills", ReplicatedUsing = OnRep_SkPerformanceModifier)
	FGameplayAttributeData SkPerformanceModifier;
	ATTRIBUTE_ACCESSORS(UPF2AttributeSet, SkPerformanceModifier)

	/**
	 * Religion gives a character knowledge of the secrets of deities, dogma, faith, and the realms of divine
	 * creatures -- both sublime and sinister. (Pathfinder 2E Core Rulebook, page 250)
	 */
	UPROPERTY(BlueprintReadOnly, Category = "Skills", ReplicatedUsing = OnRep_SkReligionModifier)
	FGameplayAttributeData SkReligionModifier;
	ATTRIBUTE_ACCESSORS(UPF2AttributeSet, SkReligionModifier)

	/**
	 * Society gives a character an understanding of the people and systems that make civilization run, including the
	 * historical events that make societies what they are today. (Pathfinder 2E Core Rulebook, page 250)
	 */
	UPROPERTY(BlueprintReadOnly, Category = "Skills", ReplicatedUsing = OnRep_SkSocietyModifier)
	FGameplayAttributeData SkSocietyModifier;
	ATTRIBUTE_ACCESSORS(UPF2AttributeSet, SkSocietyModifier)

	/**
	 * Stealth gives a character the ability to avoid detection, slip past foes, hide, and conceal items.
	 * (Pathfinder 2E Core Rulebook, page 251)
	 */
	UPROPERTY(BlueprintReadOnly, Category = "Skills", ReplicatedUsing = OnRep_SkStealthModifier)
	FGameplayAttributeData SkStealthModifier;
	ATTRIBUTE_ACCESSORS(UPF2AttributeSet, SkStealthModifier)

	/**
	 * Survival gives a character aptitude to live in the wilderness, foraging for food, and building shelter.
	 * (Pathfinder 2E Core Rulebook, page 252)
	 */
	UPROPERTY(BlueprintReadOnly, Category = "Skills", ReplicatedUsing = OnRep_SkSurvivalModifier)
	FGameplayAttributeData SkSurvivalModifier;
	ATTRIBUTE_ACCESSORS(UPF2AttributeSet, SkSurvivalModifier)

	/**
	 * Thievery gives a character training in the particular set of skills favored by thieves and miscreants.
	 * (Pathfinder 2E Core Rulebook, page 253)
	 */
	UPROPERTY(BlueprintReadOnly, Category = "Skills", ReplicatedUsing = OnRep_SkThieveryModifier)
	FGameplayAttributeData SkThieveryModifier;
	ATTRIBUTE_ACCESSORS(UPF2AttributeSet, SkThieveryModifier)

	/**
	 * Damage is a 'temporary' attribute used by the DamageExecution to calculate final damage.
	 *
	 * This turns into -HitPoints.
	 */
	UPROPERTY(BlueprintReadOnly, Category = "Damage")
	FGameplayAttributeData Damage;
	ATTRIBUTE_ACCESSORS(UPF2AttributeSet, Damage)

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
	virtual void OnRep_ClassDifficultyClass(const FGameplayAttributeData& OldValue);

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
	virtual void OnRep_PerceptionModifier(const FGameplayAttributeData& OldValue);

	UFUNCTION()
    virtual void OnRep_SkAcrobaticsModifier(const FGameplayAttributeData& OldValue);

	UFUNCTION()
    virtual void OnRep_SkArcanaModifier(const FGameplayAttributeData& OldValue);

	UFUNCTION()
    virtual void OnRep_SkAthleticsModifier(const FGameplayAttributeData& OldValue);

	UFUNCTION()
    virtual void OnRep_SkCraftingModifier(const FGameplayAttributeData& OldValue);

	UFUNCTION()
    virtual void OnRep_SkDeceptionModifier(const FGameplayAttributeData& OldValue);

	UFUNCTION()
    virtual void OnRep_SkDiplomacyModifier(const FGameplayAttributeData& OldValue);

	UFUNCTION()
    virtual void OnRep_SkIntimidationModifier(const FGameplayAttributeData& OldValue);

	UFUNCTION()
    virtual void OnRep_SkLore1Modifier(const FGameplayAttributeData& OldValue);

	UFUNCTION()
    virtual void OnRep_SkLore2Modifier(const FGameplayAttributeData& OldValue);

	UFUNCTION()
    virtual void OnRep_SkMedicineModifier(const FGameplayAttributeData& OldValue);

	UFUNCTION()
    virtual void OnRep_SkNatureModifier(const FGameplayAttributeData& OldValue);

	UFUNCTION()
    virtual void OnRep_SkOccultismModifier(const FGameplayAttributeData& OldValue);

	UFUNCTION()
    virtual void OnRep_SkPerformanceModifier(const FGameplayAttributeData& OldValue);

	UFUNCTION()
    virtual void OnRep_SkReligionModifier(const FGameplayAttributeData& OldValue);

	UFUNCTION()
    virtual void OnRep_SkSocietyModifier(const FGameplayAttributeData& OldValue);

	UFUNCTION()
    virtual void OnRep_SkStealthModifier(const FGameplayAttributeData& OldValue);

	UFUNCTION()
    virtual void OnRep_SkSurvivalModifier(const FGameplayAttributeData& OldValue);

	UFUNCTION()
    virtual void OnRep_SkThieveryModifier(const FGameplayAttributeData& OldValue);
};

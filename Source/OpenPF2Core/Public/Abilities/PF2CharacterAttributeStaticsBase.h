// OpenPF2 for UE Game Logic, Copyright 2021-2023, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#pragma once

#include "GameplayEffectExecutionCalculation.h"
#include "PF2CharacterAbilityScoreType.h"

#include "Abilities/PF2AttributeSet.h"
#include "Abilities/PF2AttributeSetMacros.h"

#include "Utilities/PF2EnumUtilities.h"

/**
 * Base class for singleton containers of OpenPF2 character attribute capture definitions.
 *
 * These centralize static capture definitions for OpenPF2 attributes instead of there being multiple, smaller "Statics"
 * definitions like those preferred by Epic's sample projects.
 */
class OPENPF2CORE_API FPF2CharacterAttributeStaticsBase
{
public:
	// =================================================================================================================
	// Attribute Capture Definitions
	// =================================================================================================================
	DECLARE_ATTRIBUTE_CAPTUREDEF(AbBoostCount);

	DECLARE_ATTRIBUTE_CAPTUREDEF(AbCharisma);
	DECLARE_ATTRIBUTE_CAPTUREDEF(AbCharismaModifier);

	DECLARE_ATTRIBUTE_CAPTUREDEF(AbConstitution);
	DECLARE_ATTRIBUTE_CAPTUREDEF(AbConstitutionModifier);

	DECLARE_ATTRIBUTE_CAPTUREDEF(AbDexterity);
	DECLARE_ATTRIBUTE_CAPTUREDEF(AbDexterityModifier);

	DECLARE_ATTRIBUTE_CAPTUREDEF(AbIntelligence);
	DECLARE_ATTRIBUTE_CAPTUREDEF(AbIntelligenceModifier);

	DECLARE_ATTRIBUTE_CAPTUREDEF(AbStrength);
	DECLARE_ATTRIBUTE_CAPTUREDEF(AbStrengthModifier);

	DECLARE_ATTRIBUTE_CAPTUREDEF(AbWisdom);
	DECLARE_ATTRIBUTE_CAPTUREDEF(AbWisdomModifier);

	DECLARE_ATTRIBUTE_CAPTUREDEF(ArmorClass);
	DECLARE_ATTRIBUTE_CAPTUREDEF(HitPoints);

	DECLARE_ATTRIBUTE_CAPTUREDEF(RstPhysicalBludgeoning);
	DECLARE_ATTRIBUTE_CAPTUREDEF(RstPhysicalPiercing);
	DECLARE_ATTRIBUTE_CAPTUREDEF(RstPhysicalSlashing);

	DECLARE_ATTRIBUTE_CAPTUREDEF(RstEnergyAcid);
	DECLARE_ATTRIBUTE_CAPTUREDEF(RstEnergyCold);
	DECLARE_ATTRIBUTE_CAPTUREDEF(RstEnergyFire);
	DECLARE_ATTRIBUTE_CAPTUREDEF(RstEnergySonic);
	DECLARE_ATTRIBUTE_CAPTUREDEF(RstEnergyPositive);
	DECLARE_ATTRIBUTE_CAPTUREDEF(RstEnergyNegative);
	DECLARE_ATTRIBUTE_CAPTUREDEF(RstEnergyForce);

	DECLARE_ATTRIBUTE_CAPTUREDEF(RstAlignmentChaotic);
	DECLARE_ATTRIBUTE_CAPTUREDEF(RstAlignmentEvil);
	DECLARE_ATTRIBUTE_CAPTUREDEF(RstAlignmentGood);
	DECLARE_ATTRIBUTE_CAPTUREDEF(RstAlignmentLawful);

	DECLARE_ATTRIBUTE_CAPTUREDEF(RstMental);
	DECLARE_ATTRIBUTE_CAPTUREDEF(RstPoison);
	DECLARE_ATTRIBUTE_CAPTUREDEF(RstBleed);
	DECLARE_ATTRIBUTE_CAPTUREDEF(RstPrecision);

	DECLARE_ATTRIBUTE_CAPTUREDEF(EncMultipleAttackPenalty);

protected:
	// =================================================================================================================
	// Protected Constants
	// =================================================================================================================
	/**
	 * Name of the tag that is used to pass a dynamic resistance amount into the calculation.
	 */
	const TMap<FName, FName> DamageTypeToResistanceAttributeMap = {
		{ "DamageType.Physical.Bludgeoning", "RstPhysicalBludgeoning" },
		{ "DamageType.Physical.Piercing",    "RstPhysicalPiercing"    },
		{ "DamageType.Physical.Slashing",    "RstPhysicalSlashing"    },

		{ "DamageType.Energy.Acid",          "RstEnergyAcid"          },
		{ "DamageType.Energy.Cold",          "RstEnergyCold"          },
		{ "DamageType.Energy.Fire",          "RstEnergyFire"          },
		{ "DamageType.Energy.Sonic",         "RstEnergySonic"         },
		{ "DamageType.Energy.Positive",      "RstEnergyPositive"      },
		{ "DamageType.Energy.Negative",      "RstEnergyNegative"      },
		{ "DamageType.Energy.Force",         "RstEnergyForce"         },

		{ "DamageType.Alignment.Chaotic",    "RstAlignmentChaotic"    },
		{ "DamageType.Alignment.Evil",       "RstAlignmentEvil"       },
		{ "DamageType.Alignment.Good",       "RstAlignmentGood"       },
		{ "DamageType.Alignment.Lawful",     "RstAlignmentLawful"     },

		{ "DamageType.Mental",               "RstMental"              },
		{ "DamageType.Poison",               "RstPoison"              },
		{ "DamageType.Bleed",                "RstBleed"               },
		{ "DamageType.Precision",            "RstPrecision"           },
	};

	// =================================================================================================================
	// Protected Fields
	// =================================================================================================================
	/**
	 * A map of all capture definitions, keyed by property name.
	 */
	TMap<FString, const FGameplayEffectAttributeCaptureDefinition*> CaptureDefinitions;

	/**
	 * The names of all ability-related attributes.
	 */
	TArray<FString> AbilityNames;

	/**
	 * The names of all ability-modifier-related attributes.
	 */
	TArray<FString> AbilityModifierNames;

public:
	// =================================================================================================================
	// Public Methods
	// =================================================================================================================
	/**
	 * Gets all of the character capture definitions.
	 *
	 * @return
	 *	An array of all the capture definitions for character attributes.
	 */
	FORCEINLINE TArray<const FGameplayEffectAttributeCaptureDefinition*> GetCaptureDefinitions() const
	{
		TArray<const FGameplayEffectAttributeCaptureDefinition*> Result;

		this->CaptureDefinitions.GenerateValueArray(Result);

		return Result;
	}

	/**
	 * Gets the names of all character ability attributes.
	 *
	 * @return
	 *	The name of each ability attribute.
	 */
	FORCEINLINE const TArray<FString>& GetAbilityNames() const
	{
		return this->AbilityNames;
	}

	/**
	 * Gets the names of all ability-modifier-related attributes.
	 *
	 * @return
	 *	The name of each ability modifier attribute.
	 */
	FORCEINLINE const TArray<FString>& GetAbilityModifierNames() const
	{
		return this->AbilityModifierNames;
	}

	/**
	 * Gets the capture definition for the given character attribute.
	 *
	 * @param Attribute
	 *	The attribute for which a capture definition is desired.
	 *
	 * @return
	 *	Either the desired capture definition; or nullptr if the given attribute doesn't correspond to a character
	 *	ability.
	 */
	FORCEINLINE const FGameplayEffectAttributeCaptureDefinition* GetCaptureByAttribute(
		const FGameplayAttribute& Attribute) const
	{
		return this->GetCaptureByAttributeName(Attribute.GetName());
	}

	/**
	 * Gets a capture definition for the specified character attribute.
	 *
	 * @param Name
	 *	The name of the attribute for which a capture definition is desired.
	 *
	 * @return
	 *	Either the desired capture definition; or nullptr if the given attribute name doesn't correspond to a character
	 *	ability.
	 */
	FORCEINLINE const FGameplayEffectAttributeCaptureDefinition* GetCaptureByAttributeName(const FString& Name) const
	{
		if (this->CaptureDefinitions.Contains(Name))
		{
			return this->CaptureDefinitions[Name];
		}
		else
		{
			UE_LOG(
				LogPf2CoreStats,
				Error,
				TEXT("No attribute capture corresponds to attribute name '%s'."),
				*Name
			);

			return nullptr;
		}
	}

	/**
	 * Gets the capture definition for the given character ability score type.
	 *
	 * @param AbilityScoreType
	 *	The ability score for which an attribute capture is desired.
	 *
	 * @return
	 *	Either the desired capture definition; or nullptr if the character is using an ASC that does not provide an
	 *	attribute that corresponds to the specified ability score.
	 */
	FORCEINLINE const FGameplayEffectAttributeCaptureDefinition* GetCaptureByAbilityScoreType(
		const EPF2CharacterAbilityScoreType AbilityScoreType) const
	{
		return this->GetCaptureByAttributeName(PF2EnumUtilities::ToString(AbilityScoreType));
	}

	/**
	 * Gets the capture definition for the modifier of the given character ability score type.
	 *
	 * @param AbilityScoreType
	 *	The ability score for which a modifier attribute capture is desired.
	 *
	 * @return
	 *	Either the desired modifier capture definition; or nullptr if the character is using an ASC that does not
	 *	provide a modifier attribute that corresponds to the specified ability score.
	 */
	FORCEINLINE const FGameplayEffectAttributeCaptureDefinition* GetModifierCaptureByAbilityScoreType(
		const EPF2CharacterAbilityScoreType AbilityScoreType) const
	{
		return this->GetCaptureByAttributeName(PF2EnumUtilities::ToString(AbilityScoreType) + "Modifier");
	}

	/**
	 * Gets capture definitions for all character ability score values.
	 *
	 * @return
	 *	Capture definitions for all character ability scores.
	 */
	TArray<const FGameplayEffectAttributeCaptureDefinition*> GetAllAbilityScoreCaptures() const;

	/**
	 * Gets the resistance attribute capture definition for the damage type that has the given tag.
	 *
	 * @param DamageType
	 *	The damage tag for which a resistance capture definition is desired.
	 *
	 * @return
	 *	Either the desired capture definition; or nullptr if the character is using an ASC that does not provide a
	 *	resistance attribute that corresponds to the specified damage type.
	 */
	FORCEINLINE const FGameplayEffectAttributeCaptureDefinition* GetResistanceCaptureForDamageType(
		const FGameplayTag& DamageType) const
	{
		return this->GetResistanceCaptureForDamageType(DamageType.GetTagName());
	}

	/**
	 * Gets the resistance attribute capture definition for the damage type that has the given tag name.
	 *
	 * @param DamageTypeName
	 *	The name of the damage tag for which a resistance capture definition is desired.
	 *
	 * @return
	 *	Either the desired capture definition; or nullptr if the character is using an ASC that does not provide a
	 *	resistance attribute that corresponds to the specified damage type.
	 */
	const FGameplayEffectAttributeCaptureDefinition* GetResistanceCaptureForDamageType(
		const FName& DamageTypeName) const;

	/**
	 * Gets capture definitions for all damage resistances.
	 *
	 * @return
	 *	Capture definitions for all damage resistance scores.
	 */
	TArray<const FGameplayEffectAttributeCaptureDefinition*> GetAllResistanceCaptures() const;

protected:
	// =================================================================================================================
	// Protected Constructors
	// =================================================================================================================
	/**
	 * Protected constructor to prevent instantiation outside of the singleton factory method.
	 */
	FPF2CharacterAttributeStaticsBase() :
		AbBoostCountProperty(nullptr),
		AbCharismaProperty(nullptr),
		AbCharismaModifierProperty(nullptr),
		AbConstitutionProperty(nullptr),
		AbConstitutionModifierProperty(nullptr),
		AbDexterityProperty(nullptr),
		AbDexterityModifierProperty(nullptr),
		AbIntelligenceProperty(nullptr),
		AbIntelligenceModifierProperty(nullptr),
		AbStrengthProperty(nullptr),
		AbStrengthModifierProperty(nullptr),
		AbWisdomProperty(nullptr),
		AbWisdomModifierProperty(nullptr),
		ArmorClassProperty(nullptr),
		HitPointsProperty(nullptr),
		RstPhysicalBludgeoningProperty(nullptr),
		RstPhysicalPiercingProperty(nullptr),
		RstPhysicalSlashingProperty(nullptr),
		RstEnergyAcidProperty(nullptr),
		RstEnergyColdProperty(nullptr),
		RstEnergyFireProperty(nullptr),
		RstEnergySonicProperty(nullptr),
		RstEnergyPositiveProperty(nullptr),
		RstEnergyNegativeProperty(nullptr),
		RstEnergyForceProperty(nullptr),
		RstAlignmentChaoticProperty(nullptr),
		RstAlignmentEvilProperty(nullptr),
		RstAlignmentGoodProperty(nullptr),
		RstAlignmentLawfulProperty(nullptr),
		RstMentalProperty(nullptr),
		RstPoisonProperty(nullptr),
		RstBleedProperty(nullptr),
		RstPrecisionProperty(nullptr),
		EncMultipleAttackPenaltyProperty(nullptr)
	{
#if !(UE_BUILD_SHIPPING || UE_BUILD_TEST)
		TArray<FName> Keys;

		this->DamageTypeToResistanceAttributeMap.GetKeys(Keys);

		// Validate that all tag names are valid.
		for (const FName& CurrentTagName : Keys)
		{
			// Rather than crashing the game/engine, we soften this to a log error so that a game designer can still
			// correct the error by possibly loading/defining tags.
			FGameplayTag Tag = FGameplayTag::RequestGameplayTag(CurrentTagName, false);

			if (!Tag.IsValid())
			{
				UE_LOG(
					LogPf2CoreStats,
					Error,
					TEXT("The damage type tag '%s' is missing."),
					*(CurrentTagName.ToString())
				);
			}
		}
#endif
	}
};

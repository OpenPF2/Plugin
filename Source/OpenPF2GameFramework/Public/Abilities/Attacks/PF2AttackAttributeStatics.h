// OpenPF2 Game Framework for Unreal Engine, Copyright 2023-2024, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#pragma once

#include <GameplayEffectExecutionCalculation.h>

#include "CharacterStats/PF2AttributeStaticsBase.h"

/**
 * Singleton container for transient attack attribute capture definitions.
 */
struct OPENPF2GAMEFRAMEWORK_API FPF2AttackAttributeStatics : FPF2AttributeStaticsBase
{
protected:
	// =================================================================================================================
	// Protected Constants
	// =================================================================================================================
	/**
	 * The prefix for all attribute captures that relate to the amount of damage of each type being done.
	 */
	inline static const FString Damage_Attribute_Prefix = TEXT("TmpDmgType");

	/**
	 * Map from each damage type tag to the transient attack attribute for that damage type.
	 */
	inline static const TMap<FName, FName> DamageTypeToTransientDamageAttributeMap = {
		{ "PF2.DamageType.Physical.Bludgeoning", "TmpDmgTypePhysicalBludgeoning" },
		{ "PF2.DamageType.Physical.Piercing",    "TmpDmgTypePhysicalPiercing"    },
		{ "PF2.DamageType.Physical.Slashing",    "TmpDmgTypePhysicalSlashing"    },

		{ "PF2.DamageType.Energy.Acid",          "TmpDmgTypeEnergyAcid"          },
		{ "PF2.DamageType.Energy.Cold",          "TmpDmgTypeEnergyCold"          },
		{ "PF2.DamageType.Energy.Electricity",   "TmpDmgTypeEnergyElectricity"   },
		{ "PF2.DamageType.Energy.Fire",          "TmpDmgTypeEnergyFire"          },
		{ "PF2.DamageType.Energy.Sonic",         "TmpDmgTypeEnergySonic"         },
		{ "PF2.DamageType.Energy.Positive",      "TmpDmgTypeEnergyPositive"      },
		{ "PF2.DamageType.Energy.Negative",      "TmpDmgTypeEnergyNegative"      },
		{ "PF2.DamageType.Energy.Force",         "TmpDmgTypeEnergyForce"         },

		{ "PF2.DamageType.Alignment.Chaotic",    "TmpDmgTypeAlignmentChaotic"    },
		{ "PF2.DamageType.Alignment.Evil",       "TmpDmgTypeAlignmentEvil"       },
		{ "PF2.DamageType.Alignment.Good",       "TmpDmgTypeAlignmentGood"       },
		{ "PF2.DamageType.Alignment.Lawful",     "TmpDmgTypeAlignmentLawful"     },

		{ "PF2.DamageType.Mental",               "TmpDmgTypeMental"              },
		{ "PF2.DamageType.Poison",               "TmpDmgTypePoison"              },
		{ "PF2.DamageType.Bleed",                "TmpDmgTypeBleed"               },
		{ "PF2.DamageType.Precision",            "TmpDmgTypePrecision"           },
	};

public:
	// =================================================================================================================
	// Public Static Methods
	// =================================================================================================================
	/**
	 * Gets an instance of this container.
	 *
	 * @return
	 *	A reference to the capture definition container.
	 */
	FORCEINLINE static const FPF2AttackAttributeStatics& GetInstance()
	{
		static FPF2AttackAttributeStatics AttributeStatics;

		return AttributeStatics;
	}

	// =================================================================================================================
	// Attribute Capture Definitions
	// =================================================================================================================
	DECLARE_ATTRIBUTE_CAPTUREDEF(TmpAttackRollCount);
	DECLARE_ATTRIBUTE_CAPTUREDEF(TmpAttackRollSize);
	DECLARE_ATTRIBUTE_CAPTUREDEF(TmpAttackDegreeOfSuccess);

	DECLARE_ATTRIBUTE_CAPTUREDEF(TmpDmgRollCount);
	DECLARE_ATTRIBUTE_CAPTUREDEF(TmpDmgRollSize);

	DECLARE_ATTRIBUTE_CAPTUREDEF(TmpDmgTypePhysicalBludgeoning);
	DECLARE_ATTRIBUTE_CAPTUREDEF(TmpDmgTypePhysicalPiercing);
	DECLARE_ATTRIBUTE_CAPTUREDEF(TmpDmgTypePhysicalSlashing);
	DECLARE_ATTRIBUTE_CAPTUREDEF(TmpDmgTypeEnergyAcid);
	DECLARE_ATTRIBUTE_CAPTUREDEF(TmpDmgTypeEnergyCold);
	DECLARE_ATTRIBUTE_CAPTUREDEF(TmpDmgTypeEnergyElectricity);
	DECLARE_ATTRIBUTE_CAPTUREDEF(TmpDmgTypeEnergyFire);
	DECLARE_ATTRIBUTE_CAPTUREDEF(TmpDmgTypeEnergySonic);
	DECLARE_ATTRIBUTE_CAPTUREDEF(TmpDmgTypeEnergyPositive);
	DECLARE_ATTRIBUTE_CAPTUREDEF(TmpDmgTypeEnergyNegative);
	DECLARE_ATTRIBUTE_CAPTUREDEF(TmpDmgTypeEnergyForce);
	DECLARE_ATTRIBUTE_CAPTUREDEF(TmpDmgTypeAlignmentChaotic);
	DECLARE_ATTRIBUTE_CAPTUREDEF(TmpDmgTypeAlignmentEvil);
	DECLARE_ATTRIBUTE_CAPTUREDEF(TmpDmgTypeAlignmentGood);
	DECLARE_ATTRIBUTE_CAPTUREDEF(TmpDmgTypeAlignmentLawful);
	DECLARE_ATTRIBUTE_CAPTUREDEF(TmpDmgTypeMental);
	DECLARE_ATTRIBUTE_CAPTUREDEF(TmpDmgTypePoison);
	DECLARE_ATTRIBUTE_CAPTUREDEF(TmpDmgTypeBleed);
	DECLARE_ATTRIBUTE_CAPTUREDEF(TmpDmgTypePrecision);

	// =================================================================================================================
	// Public Methods
	// =================================================================================================================
	/**
	 * Gets all the properties that represent transient damage attributes.
	 *
	 * @return
	 *	The damage-related attributes in this static capture definition.
	 */
	TArray<const FGameplayEffectAttributeCaptureDefinition*> GetAllDamageCaptures() const;

	/**
	 * Gets the transient damage attribute capture definition for the damage type that has the given tag.
	 *
	 * @param DamageType
	 *	The damage tag for which a damage capture definition is desired.
	 *
	 * @return
	 *	Either the desired capture definition; or nullptr if the character is using an ASC that does not provide a
	 *	transient damage attribute that corresponds to the specified damage type.
	 */
	FORCEINLINE const FGameplayEffectAttributeCaptureDefinition* GetDamageCaptureForDamageType(
		const FGameplayTag& DamageType) const
	{
		return this->GetDamageCaptureForDamageType(DamageType.GetTagName());
	}

	/**
	 * Gets the transient damage attribute capture definition for the damage type that has the given tag name.
	 *
	 * @param DamageTypeName
	 *	The name of the damage tag for which a damage capture definition is desired.
	 *
	 * @return
	 *	Either the desired capture definition; or nullptr if the character is using an ASC that does not provide a
	 *	transient damage attribute that corresponds to the specified damage type.
	 */
	const FGameplayEffectAttributeCaptureDefinition* GetDamageCaptureForDamageType(
		const FName& DamageTypeName) const;

	/**
	 * Gets the damage type tag that corresponds to the specified transient damage attribute.
	 *
	 * @param Attribute
	 *	The attribute for which a damage type is desired.
	 *
	 * @return
	 *	Either the tag for the type of damage that was provided; or, a gameplay tag that is not valid if there is no
	 *	damage type that corresponds to the given attribute.
	 */
	FGameplayTag GetDamageTypeForDamageAttribute(const FGameplayAttribute& Attribute) const;

protected:
	// =================================================================================================================
	// Protected Constructors
	// =================================================================================================================
	/**
	 * Protected constructor to prevent instantiation outside of the singleton factory method.
	 */
	explicit FPF2AttackAttributeStatics();
};

// OpenPF2 for UE Game Logic, Copyright 2023, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#pragma once

#include "Abilities/PF2AttackAttributeSet.h"
#include "Abilities/PF2CharacterAttributeStaticsBase.h"

/**
 * Singleton container for transient attack attribute capture definitions.
 */
struct OPENPF2CORE_API FPF2AttackAttributeStatics
{
protected:
	/**
	 * The prefix for all attribute captures that relate to the amount of damage of each type being done.
	 */
	inline static const FString Damage_Attribute_Prefix = TEXT("TmpDmgType");

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

protected:
	// =================================================================================================================
	// Protected Fields
	// =================================================================================================================
	/**
	 * A map of all capture definitions, keyed by property name.
	 */
	TMap<FString, const FGameplayEffectAttributeCaptureDefinition*> CaptureDefinitions;

public:
	// =================================================================================================================
	// Public Methods
	// =================================================================================================================
	/**
	 * Gets all attribute capture definitions.
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

protected:
	// =================================================================================================================
	// Protected Constructors
	// =================================================================================================================
	/**
	 * Protected constructor to prevent instantiation outside of the singleton factory method.
	 */
	explicit FPF2AttackAttributeStatics() :
		TmpAttackRollCountProperty(nullptr),
		TmpAttackRollSizeProperty(nullptr),
		TmpAttackDegreeOfSuccessProperty(nullptr),
		TmpDmgRollCountProperty(nullptr),
		TmpDmgRollSizeProperty(nullptr),
		TmpDmgTypePhysicalBludgeoningProperty(nullptr),
		TmpDmgTypePhysicalPiercingProperty(nullptr),
		TmpDmgTypePhysicalSlashingProperty(nullptr),
		TmpDmgTypeEnergyAcidProperty(nullptr),
		TmpDmgTypeEnergyColdProperty(nullptr),
		TmpDmgTypeEnergyFireProperty(nullptr),
		TmpDmgTypeEnergySonicProperty(nullptr),
		TmpDmgTypeEnergyPositiveProperty(nullptr),
		TmpDmgTypeEnergyNegativeProperty(nullptr),
		TmpDmgTypeEnergyForceProperty(nullptr),
		TmpDmgTypeAlignmentChaoticProperty(nullptr),
		TmpDmgTypeAlignmentEvilProperty(nullptr),
		TmpDmgTypeAlignmentGoodProperty(nullptr),
		TmpDmgTypeAlignmentLawfulProperty(nullptr),
		TmpDmgTypeMentalProperty(nullptr),
		TmpDmgTypePoisonProperty(nullptr),
		TmpDmgTypeBleedProperty(nullptr),
		TmpDmgTypePrecisionProperty(nullptr)
	{
		DEFINE_PF2_ATTRIBUTE_CAPTUREDEF(UPF2AttackAttributeSet, TmpAttackDegreeOfSuccess, Source, false);
		DEFINE_PF2_ATTRIBUTE_CAPTUREDEF(UPF2AttackAttributeSet, TmpAttackRollCount, Source, false);
		DEFINE_PF2_ATTRIBUTE_CAPTUREDEF(UPF2AttackAttributeSet, TmpAttackRollSize, Source, false);

		DEFINE_PF2_ATTRIBUTE_CAPTUREDEF(UPF2AttackAttributeSet, TmpDmgRollCount, Source, false);
		DEFINE_PF2_ATTRIBUTE_CAPTUREDEF(UPF2AttackAttributeSet, TmpDmgRollSize, Source, false);

		DEFINE_PF2_ATTRIBUTE_CAPTUREDEF(UPF2AttackAttributeSet, TmpDmgTypePhysicalBludgeoning, Source, false);
		DEFINE_PF2_ATTRIBUTE_CAPTUREDEF(UPF2AttackAttributeSet, TmpDmgTypePhysicalPiercing, Source, false);
		DEFINE_PF2_ATTRIBUTE_CAPTUREDEF(UPF2AttackAttributeSet, TmpDmgTypePhysicalSlashing, Source, false);
		DEFINE_PF2_ATTRIBUTE_CAPTUREDEF(UPF2AttackAttributeSet, TmpDmgTypeEnergyAcid, Source, false);
		DEFINE_PF2_ATTRIBUTE_CAPTUREDEF(UPF2AttackAttributeSet, TmpDmgTypeEnergyCold, Source, false);
		DEFINE_PF2_ATTRIBUTE_CAPTUREDEF(UPF2AttackAttributeSet, TmpDmgTypeEnergyFire, Source, false);
		DEFINE_PF2_ATTRIBUTE_CAPTUREDEF(UPF2AttackAttributeSet, TmpDmgTypeEnergySonic, Source, false);
		DEFINE_PF2_ATTRIBUTE_CAPTUREDEF(UPF2AttackAttributeSet, TmpDmgTypeEnergyPositive, Source, false);
		DEFINE_PF2_ATTRIBUTE_CAPTUREDEF(UPF2AttackAttributeSet, TmpDmgTypeEnergyNegative, Source, false);
		DEFINE_PF2_ATTRIBUTE_CAPTUREDEF(UPF2AttackAttributeSet, TmpDmgTypeEnergyForce, Source, false);
		DEFINE_PF2_ATTRIBUTE_CAPTUREDEF(UPF2AttackAttributeSet, TmpDmgTypeAlignmentChaotic, Source, false);
		DEFINE_PF2_ATTRIBUTE_CAPTUREDEF(UPF2AttackAttributeSet, TmpDmgTypeAlignmentEvil, Source, false);
		DEFINE_PF2_ATTRIBUTE_CAPTUREDEF(UPF2AttackAttributeSet, TmpDmgTypeAlignmentGood, Source, false);
		DEFINE_PF2_ATTRIBUTE_CAPTUREDEF(UPF2AttackAttributeSet, TmpDmgTypeAlignmentLawful, Source, false);
		DEFINE_PF2_ATTRIBUTE_CAPTUREDEF(UPF2AttackAttributeSet, TmpDmgTypeMental, Source, false);
		DEFINE_PF2_ATTRIBUTE_CAPTUREDEF(UPF2AttackAttributeSet, TmpDmgTypePoison, Source, false);
		DEFINE_PF2_ATTRIBUTE_CAPTUREDEF(UPF2AttackAttributeSet, TmpDmgTypeBleed, Source, false);
		DEFINE_PF2_ATTRIBUTE_CAPTUREDEF(UPF2AttackAttributeSet, TmpDmgTypePrecision, Source, false);
	}
};

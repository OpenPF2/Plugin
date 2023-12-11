// OpenPF2 for UE Game Logic, Copyright 2023, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "Abilities/PF2AttackAttributeStatics.h"

#include "Abilities/PF2AttackAttributeSet.h"
#include "Abilities/PF2AttributeSetMacros.h"

#include "Utilities/PF2ArrayUtilities.h"

TArray<const FGameplayEffectAttributeCaptureDefinition*> FPF2AttackAttributeStatics::GetAllDamageCaptures() const
{
	return PF2ArrayUtilities::Filter(
		this->GetCaptureDefinitions(),
		[](const FGameplayEffectAttributeCaptureDefinition* CaptureDefinition)
		{
			return CaptureDefinition->AttributeToCapture.GetName().StartsWith("TmpDmgType");
		});
}

const FGameplayEffectAttributeCaptureDefinition* FPF2AttackAttributeStatics::GetDamageCaptureForDamageType(
	const FName& DamageTypeName) const
{
	const FGameplayEffectAttributeCaptureDefinition* Result = nullptr;

	if (this->DamageTypeToTransientDamageAttributeMap.Contains(DamageTypeName))
	{
		const FName ResistanceAttributeName = this->DamageTypeToTransientDamageAttributeMap[DamageTypeName];

		Result = this->GetCaptureByAttributeName(ResistanceAttributeName.ToString());
	}
	else
	{
		UE_LOG(
			LogPf2CoreStats,
			Error,
			TEXT("No damage attribute corresponds to damage type '%s'."),
			*(DamageTypeName.ToString())
		);
	}

	return Result;
}

FPF2AttackAttributeStatics::FPF2AttackAttributeStatics():
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
	TmpDmgTypeEnergyElectricityProperty(nullptr),
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
#if !(UE_BUILD_SHIPPING || UE_BUILD_TEST)
	TArray<FName> Keys;

	this->DamageTypeToTransientDamageAttributeMap.GetKeys(Keys);

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

	DEFINE_PF2_ATTRIBUTE_CAPTUREDEF(UPF2AttackAttributeSet, TmpAttackDegreeOfSuccess, Source, false);
	DEFINE_PF2_ATTRIBUTE_CAPTUREDEF(UPF2AttackAttributeSet, TmpAttackRollCount, Source, false);
	DEFINE_PF2_ATTRIBUTE_CAPTUREDEF(UPF2AttackAttributeSet, TmpAttackRollSize, Source, false);

	DEFINE_PF2_ATTRIBUTE_CAPTUREDEF(UPF2AttackAttributeSet, TmpDmgRollCount, Source, false);
	DEFINE_PF2_ATTRIBUTE_CAPTUREDEF(UPF2AttackAttributeSet, TmpDmgRollSize, Source, false);

	DEFINE_PF2_ATTRIBUTE_CAPTUREDEF(UPF2AttackAttributeSet, TmpDmgTypePhysicalBludgeoning, Source, false);
	DEFINE_PF2_ATTRIBUTE_CAPTUREDEF(UPF2AttackAttributeSet, TmpDmgTypePhysicalPiercing, Source, false);
	DEFINE_PF2_ATTRIBUTE_CAPTUREDEF(UPF2AttackAttributeSet, TmpDmgTypePhysicalSlashing, Source, false);
	DEFINE_PF2_ATTRIBUTE_CAPTUREDEF(UPF2AttackAttributeSet, TmpDmgTypeEnergyAcid, Source, false);
	DEFINE_PF2_ATTRIBUTE_CAPTUREDEF(UPF2AttackAttributeSet, TmpDmgTypeEnergyElectricity, Source, false);
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

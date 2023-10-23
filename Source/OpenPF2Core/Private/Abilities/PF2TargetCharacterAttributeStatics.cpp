// OpenPF2 for UE Game Logic, Copyright 2023, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "Abilities/PF2TargetCharacterAttributeStatics.h"

const FGameplayEffectAttributeCaptureDefinition* FPF2TargetCharacterAttributeStatics::GetResistanceCaptureForDamageAttribute(
	const FName& DamageAttributeName) const
{
	const FGameplayEffectAttributeCaptureDefinition* Result = nullptr;

	if (this->DamageAttributeToResistanceAttributeMap.Contains(DamageAttributeName))
	{
		const FName ResistanceAttributeName = this->DamageAttributeToResistanceAttributeMap[DamageAttributeName];

		Result = this->GetCaptureByAttributeName(ResistanceAttributeName.ToString());
	}
	else
	{
		UE_LOG(
			LogPf2CoreStats,
			Error,
			TEXT("No resistance attribute corresponds to damage attribute '%s'."),
			*(DamageAttributeName.ToString())
		);
	}

	return Result;
}

FPF2TargetCharacterAttributeStatics::FPF2TargetCharacterAttributeStatics():
	TmpDamageIncomingProperty(nullptr),
	TmpIncomingAttackDegreeOfSuccessProperty(nullptr)
{
	DEFINE_PF2_ATTRIBUTE_CAPTUREDEF(UPF2AttributeSet, AbBoostCount, Target, false);

	DEFINE_PF2_ABILITY_SCORE_CAPTUREDEF(UPF2AttributeSet, AbCharisma, Target, false);
	DEFINE_PF2_ABILITY_SCORE_CAPTUREDEF(UPF2AttributeSet, AbConstitution, Target, false);
	DEFINE_PF2_ABILITY_SCORE_CAPTUREDEF(UPF2AttributeSet, AbDexterity, Target, false);
	DEFINE_PF2_ABILITY_SCORE_CAPTUREDEF(UPF2AttributeSet, AbIntelligence, Target, false);
	DEFINE_PF2_ABILITY_SCORE_CAPTUREDEF(UPF2AttributeSet, AbStrength, Target, false);
	DEFINE_PF2_ABILITY_SCORE_CAPTUREDEF(UPF2AttributeSet, AbWisdom, Target, false);

	DEFINE_PF2_ABILITY_MODIFIER_CAPTUREDEF(UPF2AttributeSet, AbCharismaModifier, Target, false);
	DEFINE_PF2_ABILITY_MODIFIER_CAPTUREDEF(UPF2AttributeSet, AbConstitutionModifier, Target, false);
	DEFINE_PF2_ABILITY_MODIFIER_CAPTUREDEF(UPF2AttributeSet, AbDexterityModifier, Target, false);
	DEFINE_PF2_ABILITY_MODIFIER_CAPTUREDEF(UPF2AttributeSet, AbIntelligenceModifier, Target, false);
	DEFINE_PF2_ABILITY_MODIFIER_CAPTUREDEF(UPF2AttributeSet, AbStrengthModifier, Target, false);
	DEFINE_PF2_ABILITY_MODIFIER_CAPTUREDEF(UPF2AttributeSet, AbWisdomModifier, Target, false);

	DEFINE_PF2_ATTRIBUTE_CAPTUREDEF(UPF2AttributeSet, ArmorClass, Target, false);
	DEFINE_PF2_ATTRIBUTE_CAPTUREDEF(UPF2AttributeSet, HitPoints, Target, false);

	DEFINE_PF2_ATTRIBUTE_CAPTUREDEF(UPF2AttributeSet, RstPhysicalBludgeoning, Target, false);
	DEFINE_PF2_ATTRIBUTE_CAPTUREDEF(UPF2AttributeSet, RstPhysicalPiercing, Target, false);
	DEFINE_PF2_ATTRIBUTE_CAPTUREDEF(UPF2AttributeSet, RstPhysicalSlashing, Target, false);

	DEFINE_PF2_ATTRIBUTE_CAPTUREDEF(UPF2AttributeSet, RstEnergyAcid, Target, false);
	DEFINE_PF2_ATTRIBUTE_CAPTUREDEF(UPF2AttributeSet, RstEnergyCold, Target, false);
	DEFINE_PF2_ATTRIBUTE_CAPTUREDEF(UPF2AttributeSet, RstEnergyFire, Target, false);
	DEFINE_PF2_ATTRIBUTE_CAPTUREDEF(UPF2AttributeSet, RstEnergySonic, Target, false);
	DEFINE_PF2_ATTRIBUTE_CAPTUREDEF(UPF2AttributeSet, RstEnergyPositive, Target, false);
	DEFINE_PF2_ATTRIBUTE_CAPTUREDEF(UPF2AttributeSet, RstEnergyNegative, Target, false);
	DEFINE_PF2_ATTRIBUTE_CAPTUREDEF(UPF2AttributeSet, RstEnergyForce, Target, false);

	DEFINE_PF2_ATTRIBUTE_CAPTUREDEF(UPF2AttributeSet, RstAlignmentChaotic, Target, false);
	DEFINE_PF2_ATTRIBUTE_CAPTUREDEF(UPF2AttributeSet, RstAlignmentEvil, Target, false);
	DEFINE_PF2_ATTRIBUTE_CAPTUREDEF(UPF2AttributeSet, RstAlignmentGood, Target, false);
	DEFINE_PF2_ATTRIBUTE_CAPTUREDEF(UPF2AttributeSet, RstAlignmentLawful, Target, false);

	DEFINE_PF2_ATTRIBUTE_CAPTUREDEF(UPF2AttributeSet, RstMental, Target, false);
	DEFINE_PF2_ATTRIBUTE_CAPTUREDEF(UPF2AttributeSet, RstPoison, Target, false);
	DEFINE_PF2_ATTRIBUTE_CAPTUREDEF(UPF2AttributeSet, RstBleed, Target, false);
	DEFINE_PF2_ATTRIBUTE_CAPTUREDEF(UPF2AttributeSet, RstPrecision, Target, false);

	DEFINE_PF2_ATTRIBUTE_CAPTUREDEF(UPF2AttributeSet, TmpDamageIncoming, Target, false);
	DEFINE_PF2_ATTRIBUTE_CAPTUREDEF(UPF2AttributeSet, TmpIncomingAttackDegreeOfSuccess, Target, false);
}

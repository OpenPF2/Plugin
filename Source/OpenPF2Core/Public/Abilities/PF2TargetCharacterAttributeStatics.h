// OpenPF2 for UE Game Logic, Copyright 2023, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#pragma once

#include "Abilities/PF2AttributeSet.h"
#include "Abilities/PF2CharacterAttributeStaticsBase.h"

/**
 * Singleton container for OpenPF2 character attribute capture definitions for target actors.
 */
class OPENPF2CORE_API FPF2TargetCharacterAttributeStatics final : public FPF2CharacterAttributeStaticsBase
{
public:
	// =================================================================================================================
	// Attribute Capture Definitions
	// =================================================================================================================
	DECLARE_ATTRIBUTE_CAPTUREDEF(TmpDamageIncoming);

	// =================================================================================================================
	// Public Static Methods
	// =================================================================================================================
	/**
	 * Gets an instance of this container.
	 *
	 * @return
	 *	A reference to the capture definition container.
	 */
	FORCEINLINE static const FPF2TargetCharacterAttributeStatics& GetInstance()
	{
		static FPF2TargetCharacterAttributeStatics AttributeStatics;

		return AttributeStatics;
	}

private:
	// =================================================================================================================
	// Private Constructors
	// =================================================================================================================
	/**
	 * Constructor for FPF2TargetCharacterAttributeStatics.
	 */
	FPF2TargetCharacterAttributeStatics() : TmpDamageIncomingProperty(nullptr)
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
	}
};

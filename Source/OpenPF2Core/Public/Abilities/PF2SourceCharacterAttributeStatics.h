// OpenPF2 for UE Game Logic, Copyright 2023, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#pragma once

#include "Abilities/PF2AttributeSet.h"
#include "Abilities/PF2CharacterAttributeStaticsBase.h"

/**
 * Singleton container for OpenPF2 character attribute capture definitions for source actors.
 */
class OPENPF2CORE_API FPF2SourceCharacterAttributeStatics final : public FPF2CharacterAttributeStaticsBase
{
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
	FORCEINLINE static const FPF2SourceCharacterAttributeStatics& GetInstance()
	{
		static FPF2SourceCharacterAttributeStatics AttributeStatics;

		return AttributeStatics;
	}

private:
	// =================================================================================================================
	// Private Constructors
	// =================================================================================================================
	/**
	 * Constructor for FPF2SourceCharacterAttributeStatics.
	 */
	FPF2SourceCharacterAttributeStatics()
	{
		DEFINE_PF2_ATTRIBUTE_CAPTUREDEF(UPF2AttributeSet, AbBoostCount, Source, false);

		DEFINE_PF2_ABILITY_SCORE_CAPTUREDEF(UPF2AttributeSet, AbCharisma, Source, false);
		DEFINE_PF2_ABILITY_SCORE_CAPTUREDEF(UPF2AttributeSet, AbConstitution, Source, false);
		DEFINE_PF2_ABILITY_SCORE_CAPTUREDEF(UPF2AttributeSet, AbDexterity, Source, false);
		DEFINE_PF2_ABILITY_SCORE_CAPTUREDEF(UPF2AttributeSet, AbIntelligence, Source, false);
		DEFINE_PF2_ABILITY_SCORE_CAPTUREDEF(UPF2AttributeSet, AbStrength, Source, false);
		DEFINE_PF2_ABILITY_SCORE_CAPTUREDEF(UPF2AttributeSet, AbWisdom, Source, false);

		DEFINE_PF2_ABILITY_MODIFIER_CAPTUREDEF(UPF2AttributeSet, AbCharismaModifier, Source, false);
		DEFINE_PF2_ABILITY_MODIFIER_CAPTUREDEF(UPF2AttributeSet, AbConstitutionModifier, Source, false);
		DEFINE_PF2_ABILITY_MODIFIER_CAPTUREDEF(UPF2AttributeSet, AbDexterityModifier, Source, false);
		DEFINE_PF2_ABILITY_MODIFIER_CAPTUREDEF(UPF2AttributeSet, AbIntelligenceModifier, Source, false);
		DEFINE_PF2_ABILITY_MODIFIER_CAPTUREDEF(UPF2AttributeSet, AbStrengthModifier, Source, false);
		DEFINE_PF2_ABILITY_MODIFIER_CAPTUREDEF(UPF2AttributeSet, AbWisdomModifier, Source, false);

		DEFINE_PF2_ATTRIBUTE_CAPTUREDEF(UPF2AttributeSet, ArmorClass, Source, false);
		DEFINE_PF2_ATTRIBUTE_CAPTUREDEF(UPF2AttributeSet, HitPoints, Source, false);

		DEFINE_PF2_ATTRIBUTE_CAPTUREDEF(UPF2AttributeSet, RstPhysicalBludgeoning, Source, false);
		DEFINE_PF2_ATTRIBUTE_CAPTUREDEF(UPF2AttributeSet, RstPhysicalPiercing, Source, false);
		DEFINE_PF2_ATTRIBUTE_CAPTUREDEF(UPF2AttributeSet, RstPhysicalSlashing, Source, false);

		DEFINE_PF2_ATTRIBUTE_CAPTUREDEF(UPF2AttributeSet, RstEnergyAcid, Source, false);
		DEFINE_PF2_ATTRIBUTE_CAPTUREDEF(UPF2AttributeSet, RstEnergyCold, Source, false);
		DEFINE_PF2_ATTRIBUTE_CAPTUREDEF(UPF2AttributeSet, RstEnergyFire, Source, false);
		DEFINE_PF2_ATTRIBUTE_CAPTUREDEF(UPF2AttributeSet, RstEnergySonic, Source, false);
		DEFINE_PF2_ATTRIBUTE_CAPTUREDEF(UPF2AttributeSet, RstEnergyPositive, Source, false);
		DEFINE_PF2_ATTRIBUTE_CAPTUREDEF(UPF2AttributeSet, RstEnergyNegative, Source, false);
		DEFINE_PF2_ATTRIBUTE_CAPTUREDEF(UPF2AttributeSet, RstEnergyForce, Source, false);

		DEFINE_PF2_ATTRIBUTE_CAPTUREDEF(UPF2AttributeSet, RstAlignmentChaotic, Source, false);
		DEFINE_PF2_ATTRIBUTE_CAPTUREDEF(UPF2AttributeSet, RstAlignmentEvil, Source, false);
		DEFINE_PF2_ATTRIBUTE_CAPTUREDEF(UPF2AttributeSet, RstAlignmentGood, Source, false);
		DEFINE_PF2_ATTRIBUTE_CAPTUREDEF(UPF2AttributeSet, RstAlignmentLawful, Source, false);

		DEFINE_PF2_ATTRIBUTE_CAPTUREDEF(UPF2AttributeSet, RstMental, Source, false);
		DEFINE_PF2_ATTRIBUTE_CAPTUREDEF(UPF2AttributeSet, RstPoison, Source, false);
		DEFINE_PF2_ATTRIBUTE_CAPTUREDEF(UPF2AttributeSet, RstBleed, Source, false);
		DEFINE_PF2_ATTRIBUTE_CAPTUREDEF(UPF2AttributeSet, RstPrecision, Source, false);

		DEFINE_PF2_ATTRIBUTE_CAPTUREDEF(UPF2AttributeSet, EncMultipleAttackPenalty, Source, false);

		DEFINE_PF2_ATTRIBUTE_CAPTUREDEF(UPF2AttributeSet, TmpDamageIncoming, Source, false);
	}
};

// OpenPF2 for UE Game Logic, Copyright 2023, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "Abilities/PF2SourceCharacterAttributeStatics.h"

FPF2SourceCharacterAttributeStatics::FPF2SourceCharacterAttributeStatics()
{
	DEFINE_PF2_ATTRIBUTE_CAPTUREDEF(UPF2AttributeSet, AbBoostCount, Source, true);

	DEFINE_PF2_ABILITY_SCORE_CAPTUREDEF(UPF2AttributeSet, AbCharisma, Source, true);
	DEFINE_PF2_ABILITY_SCORE_CAPTUREDEF(UPF2AttributeSet, AbConstitution, Source, true);
	DEFINE_PF2_ABILITY_SCORE_CAPTUREDEF(UPF2AttributeSet, AbDexterity, Source, true);
	DEFINE_PF2_ABILITY_SCORE_CAPTUREDEF(UPF2AttributeSet, AbIntelligence, Source, true);
	DEFINE_PF2_ABILITY_SCORE_CAPTUREDEF(UPF2AttributeSet, AbStrength, Source, true);
	DEFINE_PF2_ABILITY_SCORE_CAPTUREDEF(UPF2AttributeSet, AbWisdom, Source, true);

	DEFINE_PF2_ABILITY_MODIFIER_CAPTUREDEF(UPF2AttributeSet, AbCharismaModifier, Source, true);
	DEFINE_PF2_ABILITY_MODIFIER_CAPTUREDEF(UPF2AttributeSet, AbConstitutionModifier, Source, true);
	DEFINE_PF2_ABILITY_MODIFIER_CAPTUREDEF(UPF2AttributeSet, AbDexterityModifier, Source, true);
	DEFINE_PF2_ABILITY_MODIFIER_CAPTUREDEF(UPF2AttributeSet, AbIntelligenceModifier, Source, true);
	DEFINE_PF2_ABILITY_MODIFIER_CAPTUREDEF(UPF2AttributeSet, AbStrengthModifier, Source, true);
	DEFINE_PF2_ABILITY_MODIFIER_CAPTUREDEF(UPF2AttributeSet, AbWisdomModifier, Source, true);

	DEFINE_PF2_ATTRIBUTE_CAPTUREDEF(UPF2AttributeSet, ArmorClass, Source, true);
	DEFINE_PF2_ATTRIBUTE_CAPTUREDEF(UPF2AttributeSet, HitPoints, Source, true);

	DEFINE_PF2_ATTRIBUTE_CAPTUREDEF(UPF2AttributeSet, RstPhysicalBludgeoning, Source, true);
	DEFINE_PF2_ATTRIBUTE_CAPTUREDEF(UPF2AttributeSet, RstPhysicalPiercing, Source, true);
	DEFINE_PF2_ATTRIBUTE_CAPTUREDEF(UPF2AttributeSet, RstPhysicalSlashing, Source, true);

	DEFINE_PF2_ATTRIBUTE_CAPTUREDEF(UPF2AttributeSet, RstEnergyAcid, Source, true);
	DEFINE_PF2_ATTRIBUTE_CAPTUREDEF(UPF2AttributeSet, RstEnergyCold, Source, true);
	DEFINE_PF2_ATTRIBUTE_CAPTUREDEF(UPF2AttributeSet, RstEnergyFire, Source, true);
	DEFINE_PF2_ATTRIBUTE_CAPTUREDEF(UPF2AttributeSet, RstEnergySonic, Source, true);
	DEFINE_PF2_ATTRIBUTE_CAPTUREDEF(UPF2AttributeSet, RstEnergyPositive, Source, true);
	DEFINE_PF2_ATTRIBUTE_CAPTUREDEF(UPF2AttributeSet, RstEnergyNegative, Source, true);
	DEFINE_PF2_ATTRIBUTE_CAPTUREDEF(UPF2AttributeSet, RstEnergyForce, Source, true);

	DEFINE_PF2_ATTRIBUTE_CAPTUREDEF(UPF2AttributeSet, RstAlignmentChaotic, Source, true);
	DEFINE_PF2_ATTRIBUTE_CAPTUREDEF(UPF2AttributeSet, RstAlignmentEvil, Source, true);
	DEFINE_PF2_ATTRIBUTE_CAPTUREDEF(UPF2AttributeSet, RstAlignmentGood, Source, true);
	DEFINE_PF2_ATTRIBUTE_CAPTUREDEF(UPF2AttributeSet, RstAlignmentLawful, Source, true);

	DEFINE_PF2_ATTRIBUTE_CAPTUREDEF(UPF2AttributeSet, RstMental, Source, true);
	DEFINE_PF2_ATTRIBUTE_CAPTUREDEF(UPF2AttributeSet, RstPoison, Source, true);
	DEFINE_PF2_ATTRIBUTE_CAPTUREDEF(UPF2AttributeSet, RstBleed, Source, true);
	DEFINE_PF2_ATTRIBUTE_CAPTUREDEF(UPF2AttributeSet, RstPrecision, Source, true);

	DEFINE_PF2_ATTRIBUTE_CAPTUREDEF(UPF2AttributeSet, EncMultipleAttackPenalty, Source, true);
}

// OpenPF2 Game Framework for Unreal Engine, Copyright 2026, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "GameplayTags/Common.h"
#include "GameplayTags/CurrencyUnits.h"
#include "GameplayTags/GameplayEffects/CalculationSources.h"
#include "GameplayTags/Stats/Languages.h"
#include "GameplayTags/Stats/Proficiencies/Armor.h"
#include "GameplayTags/Traits/Conditions.h"
#include "GameplayTags/Traits/Weapons.h"
#include "GameplayTags/WeaponGroups.h"

#include "Tests/PF2SpecBase.h"

BEGIN_DEFINE_PF_SPEC(FPF2NativeGameplayTagsSpec,
	"OpenPF2.Libraries.NativeGameplayTags",
	EAutomationTestFlags::ProductFilter | EnhancedAutomationApplicationContextMask)
END_DEFINE_PF_SPEC(FPF2NativeGameplayTagsSpec)

void FPF2NativeGameplayTagsSpec::Define()
{
	/** Exported category constants must link across modules and resolve to their intended canonical names. */
	It(TEXT("exports the canonical category tags to consumers"), [this]()
	{
		TestEqual(TEXT("Traits"), Pf2TagTraits.GetTag().ToString(), FString(TEXT("PF2.Trait")));
		TestEqual(TEXT("Weapon groups"), Pf2TagWeaponGroups.GetTag().ToString(), FString(TEXT("PF2.WeaponGroup")));
		TestEqual(TEXT("Weapon traits"), Pf2TagTraitWeapons.GetTag().ToString(), FString(TEXT("PF2.Trait.Weapon")));
		TestEqual(TEXT("Calculation sources"), Pf2TagGameplayEffectCalculationSources.GetTag().ToString(),
			FString(TEXT("PF2.GameplayEffect.CalculationSource")));
		TestTrue(TEXT("Armor category is beneath armor"),
			Pf2TagProficiencyArmorCategories.GetTag().MatchesTag(Pf2TagProficiencyArmor));
		TestTrue(TEXT("Heavy proficiency is beneath armor categories"),
			Pf2TagProficiencyArmorCategoryHeavy.GetTag().MatchesTag(Pf2TagProficiencyArmorCategories));
		TestEqual(TEXT("Trigger root"), Pf2TagTriggerTagCategoryRoot.GetTag().ToString(),
			FString(TEXT("TriggerTagCategory.PF2")));
	});

	/** A category query must include other common languages without treating them as the Common language. */
	It(TEXT("keeps the common language category distinct from the Common language"), [this]()
	{
		TestTrue(TEXT("Draconic is a common language"),
			Pf2TagLanguageCommonDraconic.GetTag().MatchesTag(Pf2TagLanguagesCommon));
		TestFalse(TEXT("Draconic is not the Common language"),
			Pf2TagLanguageCommonDraconic.GetTag().MatchesTag(Pf2TagLanguageCommonCommon));
	});

	/** Migrated currency units and numbered Sickened conditions must remain registered and usable. */
	It(TEXT("registers currency units and all Sickened levels"), [this]()
	{
		TestEqual(TEXT("Copper unit"), Pf2TagCurrencyUnitCoinCopperPiece.GetTag().ToString(),
			FString(TEXT("PF2.CurrencyUnit.Coin.CopperPiece")));
		for (const FGameplayTag& Tag : { Pf2TagTraitConditionSickened1.GetTag(),
			Pf2TagTraitConditionSickened2.GetTag(), Pf2TagTraitConditionSickened3.GetTag(),
			Pf2TagTraitConditionSickened4.GetTag() })
		{
			TestTrue(TEXT("Sickened level is registered"), Tag.IsValid());
			TestTrue(TEXT("Sickened level matches its condition"), Tag.MatchesTag(Pf2TagTraitConditionSickened));
		}
	});
}

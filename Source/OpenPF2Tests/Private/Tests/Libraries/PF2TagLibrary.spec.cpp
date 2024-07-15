// OpenPF2 Game Framework for Unreal Engine, Copyright 2023-2026, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "GameplayTags/Stats/CreatureAlignments.h"
#include "GameplayTags/Stats/CreatureSizes.h"
#include "GameplayTags/Traits/Conditions.h"

#include "Libraries/PF2TagLibrary.h"

#include "Tests/PF2SpecBase.h"

#include "Utilities/PF2GameplayAbilityUtilities.h"

// Exercise the compact spec macro alongside suites that use BEGIN_DEFINE_PF_SPEC.
DEFINE_PF_SPEC(FPF2TagLibrarySpec,
               "OpenPF2.Libraries.Tag",
               EAutomationTestFlags::ProductFilter | EnhancedAutomationApplicationContextMask)

void FPF2TagLibrarySpec::Define()
{
	static const TArray<FGameplayTag> Tags = {
		Pf2TagCreatureSizeMedium,
		Pf2TagTraitConditionDying4,
		Pf2TagTraitConditionWounded3,
		Pf2TagTraitConditionWounded2,
		Pf2TagCreatureAlignmentChaoticGood,
	};

	static const FGameplayTag DoomedTag        = Pf2TagTraitConditionDoomed,
	                          DyingParentTag   = Pf2TagTraitConditionDying,
	                          WoundedParentTag = Pf2TagTraitConditionWounded,
	                          ConditionTag     = Pf2TagTraitConditions,
	                          Dying4Tag        = Pf2TagTraitConditionDying4,
	                          Wounded3Tag      = Pf2TagTraitConditionWounded3;

	static FGameplayTagContainer TagList;

	for (const FGameplayTag& Tag : Tags)
	{
		TagList.AddTag(Tag);
	}

	Describe(TEXT("AddDefaultAbilityTag"), [=, this]
	{
		/** Preserve the original defaults while returning both the existing tag and the requested new tag. */
		It(TEXT("returns combined tags without changing the input container"), [=, this]
		{
			const FGameplayTagContainer DefaultTags(DoomedTag);
			const FGameplayTagContainer UpdatedTags = UPF2TagLibrary::AddDefaultAbilityTag(DefaultTags, Dying4Tag);

			TestTrue("Existing tag is preserved", UpdatedTags.HasTagExact(DoomedTag));
			TestTrue("Requested tag is included", UpdatedTags.HasTagExact(Dying4Tag));
			TestEqual("Combined tag count", UpdatedTags.Num(), 2);
			TestEqual("Original tag count", DefaultTags.Num(), 1);
			TestFalse("Original defaults remain unchanged", DefaultTags.HasTagExact(Dying4Tag));
		});

		/** Repeatedly adding an existing default tag must leave exactly one entry. */
		It(TEXT("does not duplicate an existing default tag"), [=, this]
		{
			const FGameplayTagContainer DefaultTags(DoomedTag);
			const FGameplayTagContainer UpdatedTags = UPF2TagLibrary::AddDefaultAbilityTag(DefaultTags, DoomedTag);

			TestTrue("Existing tag is preserved", UpdatedTags.HasTagExact(DoomedTag));
			TestEqual("Unique tag count", UpdatedTags.Num(), 1);
		});
	});

	Describe(TEXT("FindChildTag"), [=, this]
	{
		Describe(TEXT("when given a tag that is not a parent of any tags in the list"), [=, this]
		{
			It(TEXT("sets `bMatchFound` to `false` and returns a gameplay tag that is not valid"), [=, this]
			{
				bool               bMatchFound = true;
				const FGameplayTag Result      = UPF2TagLibrary::FindChildTag(TagList, DoomedTag, bMatchFound);

				TestFalse("Result.IsValid()", Result.IsValid());
				TestFalse("bMatchFound", bMatchFound);
			});
		});

		Describe(TEXT("when given a tag that is a parent of one tag in the list"), [=, this]
		{
			It(TEXT("sets `bMatchFound` to `true` and returns the gameplay tag that is a child of the given parent tag"), [=, this]
			{
				bool               bMatchFound = false;
				const FGameplayTag Result      = UPF2TagLibrary::FindChildTag(TagList, DyingParentTag, bMatchFound);

				TestTrue("Result.IsValid()", Result.IsValid());
				TestTrue("bMatchFound", bMatchFound);
				TestEqual("Result", Result, Dying4Tag);
			});
		});

		Describe(TEXT("when given a tag that is a parent of multiple tags in the list"), [=, this]
		{
			It(TEXT("returns the first gameplay tag encountered that is a child of the given parent tag"), [=, this]
			{
				bool         bMatchFound = false;
				FGameplayTag Result;

				AddExpectedError(
					TEXT("More than one child tag \\('PF2\\.Trait\\.Condition\\.Wounded\\.3, "
					"PF2\\.Trait\\.Condition\\.Wounded\\.2'\\) matched parent tag "
					"\\('PF2\\.Trait\\.Condition\\.Wounded'\\)\\."),
					EAutomationExpectedErrorFlags::Exact,
					1
				);

				Result = UPF2TagLibrary::FindChildTag(TagList, WoundedParentTag, bMatchFound);

				TestTrue("Result.IsValid()", Result.IsValid());
				TestTrue("bMatchFound", bMatchFound);
				TestEqual("Result", Result, Wounded3Tag);
			});
		});
	});

	Describe(TEXT("FindAndParseConditionLevel"), [=, this]
	{
		Describe(TEXT("when given a condition tag that is not a parent of any tags in the list"), [=, this]
		{
			It(TEXT("returns `0`"), [=, this]
			{
				const int8 Result = UPF2TagLibrary::FindAndParseConditionLevel(TagList, DoomedTag);

				TestEqual("Result", Result, 0);
			});
		});

		Describe(TEXT("when given a condition tag that is a grandparent of a tag in the list"), [=, this]
		{
			It(TEXT("returns `0`"), [=, this]
			{
				int8 Result;

				AddExpectedError(
					TEXT("More than one child tag \\('PF2\\.Trait\\.Condition\\.Dying\\.4, "
					"PF2\\.Trait\\.Condition\\.Wounded\\.3, PF2\\.Trait\\.Condition\\.Wounded.2'\\) matched parent tag "
					"\\('PF2\\.Trait\\.Condition'\\)\\."),
					EAutomationExpectedErrorFlags::Exact,
					1
				);

				Result = UPF2TagLibrary::FindAndParseConditionLevel(TagList, ConditionTag);

				TestEqual("Result", Result, 0);
			});
		});

		Describe(TEXT("when given a condition tag that is a parent of one tag in the list"), [=, this]
		{
			It(TEXT("returns the integer value of the child condition tag"), [=, this]
			{
				const int8 Result = UPF2TagLibrary::FindAndParseConditionLevel(TagList, DyingParentTag);

				TestEqual("Result", Result, 4);
			});
		});

		Describe(TEXT("when given a condition tag that is a parent of multiple tags in the list"), [=, this]
		{
			It(TEXT("returns the integer value of the first child condition tag encountered"), [=, this]
			{
				int8 Result;

				AddExpectedError(
					TEXT("More than one child tag \\('PF2\\.Trait\\.Condition\\.Wounded\\.3, "
					"PF2\\.Trait\\.Condition\\.Wounded\\.2'\\) matched parent tag "
					"\\('PF2\\.Trait\\.Condition\\.Wounded'\\)\\."),
					EAutomationExpectedErrorFlags::Exact,
					1
				);

				Result = UPF2TagLibrary::FindAndParseConditionLevel(TagList, WoundedParentTag);

				TestEqual("Result", Result, 3);
			});
		});
	});

	Describe(TEXT("ParseConditionLevel"), [=, this]
	{
		Describe(TEXT("when given a parent tag that is not actually a parent of the given condition tag"), [=, this]
		{
			It(TEXT("returns `0`"), [=, this]
			{
				const int8 Result = UPF2TagLibrary::ParseConditionLevel(DoomedTag, WoundedParentTag);

				TestEqual("Result", Result, 0);
			});
		});

		Describe(TEXT("when given a parent tag that is a grandparent of the given condition tag"), [=, this]
		{
			It(TEXT("returns `0`"), [=, this]
			{
				const int8 Result = UPF2TagLibrary::ParseConditionLevel(Wounded3Tag, ConditionTag);

				TestEqual("Result", Result, 0);
			});
		});

		Describe(TEXT("when given a parent tag that is a parent of the given condition tag"), [=, this]
		{
			It(TEXT("returns the integer value of the child condition tag"), [=, this]
			{
				const int8 Result = UPF2TagLibrary::ParseConditionLevel(Wounded3Tag, WoundedParentTag);

				TestEqual("Result", Result, 3);
			});
		});
	});
}

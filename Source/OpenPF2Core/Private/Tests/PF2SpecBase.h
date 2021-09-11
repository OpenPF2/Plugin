// Adapted from content that is Copyright Epic Games, Inc. All Rights Reserved.
// Licensed only for use with Unreal Engine.

#pragma once

#include <Misc/AutomationTest.h>
#include "Abilities/PF2AttributeSet.h"
#include "Tests/PF2TestPawn.h"

#define DEFINE_PF_SPEC_PRIVATE(TClass, PrettyName, TFlags, FileName, LineNumber) \
	class TClass : public FPF2SpecBase \
	{ \
	public: \
		TClass(const FString& InName) : FPF2SpecBase(InName) \
		{ \
			static_assert((TFlags)&EAutomationTestFlags::ApplicationContextMask, "AutomationTest has no application flag.  It shouldn't run.  See AutomationTest.h."); \
			static_assert((((TFlags)&EAutomationTestFlags::FilterMask) == EAutomationTestFlags::SmokeFilter) || \
						  (((TFlags)&EAutomationTestFlags::FilterMask) == EAutomationTestFlags::EngineFilter) || \
						  (((TFlags)&EAutomationTestFlags::FilterMask) == EAutomationTestFlags::ProductFilter) || \
						  (((TFlags)&EAutomationTestFlags::FilterMask) == EAutomationTestFlags::PerfFilter) || \
						  (((TFlags)&EAutomationTestFlags::FilterMask) == EAutomationTestFlags::StressFilter) || \
						  (((TFlags)&EAutomationTestFlags::FilterMask) == EAutomationTestFlags::NegativeFilter), \
						  "All AutomationTests must have exactly 1 filter type specified.  See AutomationTest.h."); \
		} \
		virtual uint32 GetTestFlags() const override { return TFlags; } \
        using FAutomationSpecBase::GetTestSourceFileName; \
		virtual FString GetTestSourceFileName() const override { return FileName; } \
        using FAutomationSpecBase::GetTestSourceFileLine; \
		virtual int32 GetTestSourceFileLine() const override { return LineNumber; } \
		virtual FString GetTestSourceFileName(const FString&) const override { return GetTestSourceFileName(); } \
		virtual int32 GetTestSourceFileLine(const FString&) const override { return GetTestSourceFileLine(); } \
	\
	protected: \
		virtual FString GetBeautifiedTestName() const override { return PrettyName; } \
		virtual void Define() override; \
	};

#define BEGIN_DEFINE_PF_SPEC_PRIVATE(TClass, PrettyName, TFlags, FileName, LineNumber) \
	class TClass : public FPF2SpecBase \
	{ \
	public: \
		TClass(const FString& InName) : FPF2SpecBase(InName) \
		{ \
			static_assert((TFlags)&EAutomationTestFlags::ApplicationContextMask, "AutomationTest has no application flag.  It shouldn't run.  See AutomationTest.h."); \
			static_assert((((TFlags)&EAutomationTestFlags::FilterMask) == EAutomationTestFlags::SmokeFilter) || \
						  (((TFlags)&EAutomationTestFlags::FilterMask) == EAutomationTestFlags::EngineFilter) || \
						  (((TFlags)&EAutomationTestFlags::FilterMask) == EAutomationTestFlags::ProductFilter) || \
						  (((TFlags)&EAutomationTestFlags::FilterMask) == EAutomationTestFlags::PerfFilter) || \
						  (((TFlags)&EAutomationTestFlags::FilterMask) == EAutomationTestFlags::StressFilter) || \
						  (((TFlags)&EAutomationTestFlags::FilterMask) == EAutomationTestFlags::NegativeFilter), \
						  "All AutomationTests must have exactly 1 filter type specified.  See AutomationTest.h."); \
		} \
		virtual uint32 GetTestFlags() const override { return TFlags; } \
		using FAutomationSpecBase::GetTestSourceFileName; \
		virtual FString GetTestSourceFileName() const override { return FileName; } \
		using FAutomationSpecBase::GetTestSourceFileLine; \
		virtual int32 GetTestSourceFileLine() const override { return LineNumber; } \
	\
	protected: \
		virtual FString GetBeautifiedTestName() const override { return PrettyName; } \
		virtual void Define() override;

#if WITH_AUTOMATION_WORKER
	#define DEFINE_PF_SPEC(TClass, PrettyName, TFlags) \
		DEFINE_PF_SPEC_PRIVATE(TClass, PrettyName, TFlags, __FILE__, __LINE__) \
		namespace\
		{\
			TClass TClass##AutomationSpecInstance(TEXT(#TClass));\
		}

	#define BEGIN_DEFINE_PF_SPEC(TClass, PrettyName, TFlags) \
		BEGIN_DEFINE_PF_SPEC_PRIVATE(TClass, PrettyName, TFlags, __FILE__, __LINE__)

	#define END_DEFINE_PF_SPEC(TClass) \
		};\
		namespace\
		{\
			TClass TClass##AutomationSpecInstance(TEXT(#TClass));\
		}
#else
	#define DEFINE_PF_SPEC(TClass, PrettyName, TFlags) \
		DEFINE_PF_SPEC_PRIVATE(TClass, PrettyName, TFlags, __FILE__, __LINE__)

	#define BEGIN_DEFINE_PF_SPEC(TClass, PrettyName, TFlags) \
		BEGIN_DEFINE_PF_SPEC_PRIVATE(TClass, PrettyName, TFlags, __FILE__, __LINE__)

	#define END_DEFINE_PF_SPEC(TClass) \
		};

#endif

typedef TMap<FString, FGameplayAttributeData*> FAttributeCapture;

class OPENPF2CORE_API FPF2SpecBase : public FAutomationSpecBase {
protected:
	UWorld* World;
	APF2TestPawn* TestPawn;
	UAbilitySystemComponent* PawnAbilityComponent;

public:
	explicit FPF2SpecBase(const FString& InName) :
		FAutomationSpecBase(InName, false),
		World(nullptr),
		TestPawn(nullptr),
		PawnAbilityComponent(nullptr)
	{
	}

protected:
	virtual void Define() override = 0;

	template <typename BlueprintType>
	static TSubclassOf<BlueprintType> LoadBlueprint(const FString FolderPath, const FString BlueprintName);

	static FAttributeCapture CaptureAttributes(const UPF2AttributeSet* AttributeSet);
	static FAttributeCapture CaptureAbilityAttributes(const UPF2AttributeSet* AttributeSet);
	static FAttributeCapture CaptureAbilityModifierAttributes(const UPF2AttributeSet* AttributeSet);
	static FAttributeCapture CaptureSavingThrowAttributes(const UPF2AttributeSet* AttributeSet);
	static FAttributeCapture CaptureSkillModifierAttributes(const UPF2AttributeSet* AttributeSet);

	void SetupWorld();
	void BeginPlay() const;
	void DestroyWorld() const;

	void SetupPawn();
	void DestroyPawn();

	FActiveGameplayEffectHandle ApplyGameEffect(FGameplayAttributeData&             Attribute,
	                                            float                               StartingValue,
	                                            const TSubclassOf<UGameplayEffect>& EffectBP,
	                                            const float                         CharacterLevel = 1.0f) const;

	void ApplyTag(FString TagName) const;
	void RemoveTag(FString TagName) const;
};

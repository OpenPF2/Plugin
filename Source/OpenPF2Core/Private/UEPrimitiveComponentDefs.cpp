// Adapted from "Runtime/Engine/Private/Components/PrimitiveComponent.cpp" (Unreal Engine 5.1), which is Copyright
// Epic Games, Inc. Licensed only for use with Unreal Engine.

#pragma once

#include "UEPrimitiveComponentDefs.h"

#include <DrawDebugHelpers.h>

#include <HAL/IConsoleManager.h>

#define LOCTEXT_NAMESPACE "PrimitiveComponent"

// =====================================================================================================================
// Globals Variables
// =====================================================================================================================
namespace PrimitiveComponentStatics
{
	extern const FText MobilityWarnText = LOCTEXT("InvalidMove", "move");
}

// =====================================================================================================================
// Console Variables (CVars)
// =====================================================================================================================
// ReSharper disable CppUE4CodingStandardNamingViolationWarning
namespace PrimitiveComponentCVars
{
	const IConsoleManager& ConsoleManager = IConsoleManager::Get();

	extern const IConsoleVariable* bEnableFastOverlapCheck                 = ConsoleManager.FindConsoleVariable(TEXT("p.EnableFastOverlapCheck"));
	extern const IConsoleVariable* bAllowCachedOverlaps                    = ConsoleManager.FindConsoleVariable(TEXT("p.AllowCachedOverlaps"));
	extern const IConsoleVariable* InitialOverlapTolerance                 = ConsoleManager.FindConsoleVariable(TEXT("p.InitialOverlapTolerance"));
	extern const IConsoleVariable* HitDistanceTolerance                    = ConsoleManager.FindConsoleVariable(TEXT("p.HitDistanceTolerance"));
	extern const IConsoleVariable* bAlwaysCreatePhysicsStateConversionHack = ConsoleManager.FindConsoleVariable(TEXT("p.AlwaysCreatePhysicsStateConversionHack"));
#if !(UE_BUILD_SHIPPING || UE_BUILD_TEST)
	extern const IConsoleVariable* bShowInitialOverlaps                    = ConsoleManager.FindConsoleVariable(TEXT("p.ShowInitialOverlaps"));
#endif // !(UE_BUILD_SHIPPING || UE_BUILD_TEST)
}
// ReSharper restore CppUE4CodingStandardNamingViolationWarning

// =====================================================================================================================
// Global Utility Methods
// =====================================================================================================================
extern void PullBackHit(FHitResult& Hit, const float Dist)
{
	const float DesiredTimeBack = FMath::Clamp(0.1f, 0.1f / Dist, 1.0f / Dist) + 0.001f;

	Hit.Time = FMath::Clamp(Hit.Time - DesiredTimeBack, 0.0f, 1.0f);
}

extern bool ShouldIgnoreHitResult(const UWorld*             InWorld,
                                  FHitResult const&         TestHit,
                                  FVector const&            MovementDirDenormalized,
                                  const AActor*             MovingActor,
                                  const EMoveComponentFlags MoveFlags)
{
	if (TestHit.bBlockingHit)
	{
		// Check "ignore bases" functionality.
		// We let overlap components go through because their overlap is still needed and will cause
		// beginOverlap/endOverlap events.
		if ((MoveFlags & MOVECOMP_IgnoreBases) && (MovingActor != nullptr))
		{
			// Ignore if there's a base relationship between moving actor and hit actor
			AActor const* const HitActor = TestHit.HitObjectHandle.FetchActor();

			if (HitActor != nullptr)
			{
				if (MovingActor->IsBasedOnActor(HitActor) || HitActor->IsBasedOnActor(MovingActor))
				{
					return true;
				}
			}
		}

		// If we started penetrating, we may want to ignore it if we are moving out of penetration.
		// This helps prevent getting stuck in walls.
		if (((TestHit.Distance < PrimitiveComponentCVars::HitDistanceTolerance->GetFloat()) || TestHit.bStartPenetrating) &&
			!(MoveFlags & MOVECOMP_NeverIgnoreBlockingOverlaps))
		{
			const float DotTolerance = PrimitiveComponentCVars::InitialOverlapTolerance->GetFloat();

			// Dot product of movement direction against 'exit' direction
			const FVector MovementDir = MovementDirDenormalized.GetSafeNormal();
			const float   MoveDot     = (TestHit.ImpactNormal | MovementDir);

			const bool bMovingOut = MoveDot > DotTolerance;

	#if !(UE_BUILD_SHIPPING || UE_BUILD_TEST)
			{
				if (PrimitiveComponentCVars::bShowInitialOverlaps->GetBool())
				{
					UE_LOG(
						LogTemp,
						Log,
						TEXT("Overlapping %s Dir %s Dot %f Normal %s Depth %f"),
						*GetNameSafe(TestHit.Component.Get()),
						*MovementDir.ToString(),
						MoveDot,
						*TestHit.ImpactNormal.ToString(),
						TestHit.PenetrationDepth
					);

					DrawDebugDirectionalArrow(
						InWorld,
						TestHit.TraceStart,
						TestHit.TraceStart + 30.f * TestHit.ImpactNormal,
						5.0f,
						bMovingOut ? FColor(64, 128, 255) : FColor(255, 64, 64),
						false,
						4.0f
					);

					if (TestHit.PenetrationDepth > UE_KINDA_SMALL_NUMBER)
					{
						DrawDebugDirectionalArrow(
							InWorld,
							TestHit.TraceStart,
							TestHit.TraceStart + TestHit.PenetrationDepth * TestHit.Normal,
							5.0f,
							FColor(64, 255, 64),
							false,
							4.0f
						);
					}
				}
			}
	#endif

			// If we are moving out, ignore this result!
			if (bMovingOut)
			{
				return true;
			}
		}
	}

	return false;
}

#undef LOCTEXT_NAMESPACE

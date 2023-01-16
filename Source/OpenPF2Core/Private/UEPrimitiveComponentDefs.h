// Adapted from "Runtime/Engine/Private/Components/PrimitiveComponent.cpp" (Unreal Engine 4.27), which is Copyright
// Epic Games, Inc. Licensed only for use with Unreal Engine.

#pragma once

#include <DrawDebugHelpers.h>

#include <Components/PrimitiveComponent.h>

#include <HAL/IConsoleManager.h>

#include <Internationalization/Text.h>

#define LOCTEXT_NAMESPACE "PrimitiveComponent"

// =====================================================================================================================
// Console Variables
// =====================================================================================================================
static const auto bEnableFastOverlapCheckCVar = IConsoleManager::Get().FindConsoleVariable(TEXT("p.EnableFastOverlapCheck"));
static const auto bAllowCachedOverlapsCVar = IConsoleManager::Get().FindConsoleVariable(TEXT("p.AllowCachedOverlaps"));
static const auto InitialOverlapToleranceCVar = IConsoleManager::Get().FindConsoleVariable(TEXT("p.InitialOverlapTolerance"));
static const auto HitDistanceToleranceCVar = IConsoleManager::Get().FindConsoleVariable(TEXT("p.HitDistanceTolerance"));
static const auto bAlwaysCreatePhysicsStateConversionHackCVar = IConsoleManager::Get().FindConsoleVariable(TEXT("p.AlwaysCreatePhysicsStateConversionHack"));

#if !(UE_BUILD_SHIPPING || UE_BUILD_TEST)
static const auto bShowInitialOverlapsCVar = IConsoleManager::Get().FindConsoleVariable(TEXT("p.ShowInitialOverlaps"));
#endif // !(UE_BUILD_SHIPPING || UE_BUILD_TEST)

// =====================================================================================================================
// Globals
// =====================================================================================================================
namespace PrimitiveComponentStatics
{
	static const FText MobilityWarnText = LOCTEXT("InvalidMove", "move");
}

// =====================================================================================================================
// Struct Definitions
// =====================================================================================================================
struct FPredicateOverlapHasDifferentActor
{
	explicit FPredicateOverlapHasDifferentActor(const AActor& Owner): MyOwnerPtr(&Owner)
	{
	}

	bool operator() (const FOverlapInfo& Info) const
	{
		// MyOwnerPtr is always valid, so we don't need the IsValid() checks in the WeakObjectPtr comparison operator.
		return !MyOwnerPtr.HasSameIndexAndSerialNumber(Info.OverlapInfo.Actor);
	}

private:
	const TWeakObjectPtr<const AActor> MyOwnerPtr;
};

struct FFastOverlapInfoCompare
{
	explicit FFastOverlapInfoCompare(const FOverlapInfo& BaseInfo): MyBaseInfo(BaseInfo)
	{
	}

	bool operator() (const FOverlapInfo& Info) const
	{
		return MyBaseInfo.OverlapInfo.Component.HasSameIndexAndSerialNumber(Info.OverlapInfo.Component)
			&& MyBaseInfo.GetBodyIndex() == Info.GetBodyIndex();
	}

	bool operator() (const FOverlapInfo* Info) const
	{
		return MyBaseInfo.OverlapInfo.Component.HasSameIndexAndSerialNumber(Info->OverlapInfo.Component)
			&& MyBaseInfo.GetBodyIndex() == Info->GetBodyIndex();
	}

private:
	const FOverlapInfo& MyBaseInfo;

};

// =====================================================================================================================
// Inlined Utility Methods
// =====================================================================================================================
static FORCEINLINE_DEBUGGABLE bool ShouldCheckOverlapFlagToQueueOverlaps(const UPrimitiveComponent& ThisComponent)
{
	const FScopedMovementUpdate* CurrentUpdate = ThisComponent.GetCurrentScopedMovement();

	if (CurrentUpdate)
	{
		return CurrentUpdate->RequiresOverlapsEventFlag();
	}
	else
	{
		// By default we require the GetGenerateOverlapEvents() to queue up overlaps, since we require it to trigger
		// events.
		return true;
	}
}

static FORCEINLINE_DEBUGGABLE bool ShouldIgnoreOverlapResult(const UWorld*              World,
                                                             const AActor*              ThisActor,
                                                             const UPrimitiveComponent& ThisComponent,
                                                             const AActor*              OtherActor,
                                                             const UPrimitiveComponent& OtherComponent,
                                                             bool                       bCheckOverlapFlags)
{
	// Don't overlap with self
	if (&ThisComponent == &OtherComponent)
	{
		return true;
	}

	if (bCheckOverlapFlags)
	{
		// Both components must set GetGenerateOverlapEvents()
		if (!ThisComponent.GetGenerateOverlapEvents() || !OtherComponent.GetGenerateOverlapEvents())
		{
			return true;
		}
	}

	if (!ThisActor || !OtherActor)
	{
		return true;
	}

	if (!World || (OtherActor == World->GetWorldSettings()) || !OtherActor->IsActorInitialized())
	{
		return true;
	}

	return false;
}

static void PullBackHit(FHitResult& Hit, const FVector& Start, const FVector& End, const float Dist)
{
	const float DesiredTimeBack = FMath::Clamp(0.1f, 0.1f/Dist, 1.f/Dist) + 0.001f;

	Hit.Time = FMath::Clamp(Hit.Time - DesiredTimeBack, 0.f, 1.f);
}

static bool ShouldIgnoreHitResult(const UWorld*       InWorld,
                                  FHitResult const&   TestHit,
                                  FVector const&      MovementDirDenormalized,
                                  const AActor*       MovingActor,
                                  EMoveComponentFlags MoveFlags)
{
	if (TestHit.bBlockingHit)
	{
		// Check "ignore bases" functionality.
		// We let overlap components go through because their overlap is still needed and will cause
		// beginOverlap/endOverlap events.
		if ((MoveFlags & MOVECOMP_IgnoreBases) && MovingActor)
		{
			// Ignore if there's a base relationship between moving actor and hit actor
			AActor const* const HitActor = TestHit.GetActor();

			if (HitActor)
			{
				if (MovingActor->IsBasedOnActor(HitActor) || HitActor->IsBasedOnActor(MovingActor))
				{
					return true;
				}
			}
		}

		// If we started penetrating, we may want to ignore it if we are moving out of penetration.
		// This helps prevent getting stuck in walls.
		if ((TestHit.Distance < HitDistanceToleranceCVar->GetFloat() || TestHit.bStartPenetrating) &&
			!(MoveFlags & MOVECOMP_NeverIgnoreBlockingOverlaps))
		{
 			const float DotTolerance = InitialOverlapToleranceCVar->GetFloat();

			// Dot product of movement direction against 'exit' direction
			const FVector MovementDir = MovementDirDenormalized.GetSafeNormal();
			const float MoveDot = (TestHit.ImpactNormal | MovementDir);

			const bool bMovingOut = MoveDot > DotTolerance;

	#if !(UE_BUILD_SHIPPING || UE_BUILD_TEST)
			{
				if (bShowInitialOverlapsCVar->GetBool())
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
						5.f,
						bMovingOut ? FColor(64,128,255) : FColor(255,64,64),
						false,
						4.f
					);

					if (TestHit.PenetrationDepth > KINDA_SMALL_NUMBER)
					{
						DrawDebugDirectionalArrow(
							InWorld,
							TestHit.TraceStart,
							TestHit.TraceStart + TestHit.PenetrationDepth * TestHit.Normal,
							5.f,
							FColor(64,255,64),
							false,
							4.f
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

template<class AllocatorType>
FORCEINLINE_DEBUGGABLE int32 IndexOfOverlapFast(const TArray<FOverlapInfo, AllocatorType>& OverlapArray,
                                                const FOverlapInfo&                        SearchItem)
{
	return OverlapArray.IndexOfByPredicate(FFastOverlapInfoCompare(SearchItem));
}

template<class AllocatorType>
FORCEINLINE_DEBUGGABLE void AddUniqueOverlapFast(TArray<FOverlapInfo, AllocatorType>& OverlapArray,
                                                 FOverlapInfo&&                       NewOverlap)
{
	if (IndexOfOverlapFast(OverlapArray, NewOverlap) == INDEX_NONE)
	{
		OverlapArray.Add(NewOverlap);
	}
}

#undef LOCTEXT_NAMESPACE

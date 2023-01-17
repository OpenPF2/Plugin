// Adapted from "Runtime/Engine/Private/Components/PrimitiveComponent.cpp" (Unreal Engine 4.27), which is Copyright
// Epic Games, Inc. Licensed only for use with Unreal Engine.

#include "PF2RootCollisionDelegateComponent.h"

#include <Algo/Copy.h>

#include <Components/SkeletalMeshComponent.h>

#include <GameFramework/CheatManager.h>
#include <GameFramework/PlayerController.h>

#include "UEPrimitiveComponentDefs.h"

#define LOCTEXT_NAMESPACE "PF2CollisionDelegateComponent"

bool UPF2RootCollisionDelegateComponent::MoveComponentImpl(const FVector&      Delta,
                                                           const FQuat&        NewRotationQuat,
                                                           bool                bSweep,
                                                           FHitResult*         OutHit,
                                                           EMoveComponentFlags MoveFlags,
                                                           ETeleportType       Teleport)

{
	// --- Start Difference from UPrimitiveComponent
	if (this->CollisionComponent == nullptr)
	{
		// We have no other component on which to perform a collision check, so perform collision checks on this
		// component instead.
		return Super::MoveComponentImpl(Delta, NewRotationQuat, bSweep, OutHit, MoveFlags, Teleport);
	}
	// --- End Difference from UPrimitiveComponent

	// static things can move before they are registered (e.g. immediately after streaming), but not after.
	if (this->IsPendingKill() || this->CheckStaticMobilityAndWarn(PrimitiveComponentStatics::MobilityWarnText))
	{
		if (OutHit != nullptr)
		{
			OutHit->Init();
		}

		return false;
	}

	this->ConditionalUpdateComponentToWorld();

	// --- Start Difference from UPrimitiveComponent
	this->CollisionComponent->ConditionalUpdateComponentToWorld();
	// --- End Difference from UPrimitiveComponent

	// Set up
	const FVector TraceStart = this->GetComponentLocation();
	const FVector TraceEnd   = TraceStart + Delta;

	// --- Start Difference from UPrimitiveComponent
	const FVector CollisionTraceStart = this->CollisionComponent->GetComponentLocation();
	const FVector CollisionTraceEnd   = TraceStart + Delta;
	// --- End Difference from UPrimitiveComponent

	// Recalc here to account for precision loss of float addition
	float       DeltaSizeSq         = (TraceEnd - TraceStart).SizeSquared();
	const FQuat InitialRotationQuat = this->CollisionComponent->GetComponentTransform().GetRotation();

	// ComponentSweepMulti does nothing if moving < KINDA_SMALL_NUMBER in distance, so it's important to not try to
	// sweep distances smaller than that.
	const float MinMovementDistSq = (bSweep ? FMath::Square(4.f*KINDA_SMALL_NUMBER) : 0.0f);

	if (DeltaSizeSq <= MinMovementDistSq)
	{
		// Skip if no vector or rotation.
		if (NewRotationQuat.Equals(InitialRotationQuat, SCENECOMPONENT_QUAT_TOLERANCE))
		{
			// copy to optional output param
			if (OutHit != nullptr)
			{
				// --- Start Difference from UPrimitiveComponent
				OutHit->Init(CollisionTraceStart, CollisionTraceEnd);
				// --- End Difference from UPrimitiveComponent
			}

			return true;
		}

		DeltaSizeSq = 0.0f;
	}

	const bool bSkipPhysicsMove = ((MoveFlags & MOVECOMP_SkipPhysicsMove) != MOVECOMP_NoFlags);

	// WARNING: HitResult is only partially initialized in some paths. All data is valid only if bFilledHitResult is
	// true.
	FHitResult              BlockingHit(NoInit);
	bool                    bFilledHitResult       = false;
	bool                    bMoved                 = false;
	bool                    bIncludesOverlapsAtEnd = false;
	bool                    bRotationOnly          = false;
	AActor* const           Actor                  = this->GetOwner();
	TInlineOverlapInfoArray PendingOverlaps;

	BlockingHit.bBlockingHit = false;
	BlockingHit.Time         = 1.f;

	if (bSweep)
	{
		FVector NewLocation = TraceStart;

		// Perform movement collision checking if needed for this actor.
		const bool bCollisionEnabled = this->IsQueryCollisionEnabled();

		if (bCollisionEnabled && (DeltaSizeSq > 0.0f))
		{
			TArray<FHitResult> Hits;

#if !(UE_BUILD_SHIPPING || UE_BUILD_TEST)
			if (!this->IsRegistered())
			{
				if (Actor == nullptr)
				{
					ensureMsgf(
						this->IsRegistered(),
						TEXT("MovedComponent %s not initialized"),
						*this->GetFullName()
					);
				}
				else
				{ //-V523
					ensureMsgf(
						this->IsRegistered(),
						TEXT("%s MovedComponent %s not initialized deleteme %d"),
						*Actor->GetName(),
						*this->GetName(),
						Actor->IsPendingKill()
					);
				}
			}
#endif

			UWorld* const            MyWorld              = this->GetWorld();
			static const FName       TraceTagName         = TEXT("MoveComponent");
			const bool               bForceGatherOverlaps = !ShouldCheckOverlapFlagToQueueOverlaps(*this);
			FComponentQueryParams    Params(SCENE_QUERY_STAT(MoveComponent), Actor);
			FCollisionResponseParams ResponseParam;

			this->InitSweepCollisionParams(Params, ResponseParam);

			Params.bIgnoreTouches |= !(this->GetGenerateOverlapEvents() || bForceGatherOverlaps);
			Params.TraceTag        = TraceTagName;

			// --- Start Difference from UPrimitiveComponent
			bool const bHadBlockingHit =
				MyWorld->ComponentSweepMulti(
					Hits,
					this->CollisionComponent,
					CollisionTraceStart,
					CollisionTraceEnd,
					InitialRotationQuat,
					Params
				);
			// --- End Difference from UPrimitiveComponent

			if (Hits.Num() > 0)
			{
				const float DeltaSize = FMath::Sqrt(DeltaSizeSq);

				for (int32 HitIdx = 0; HitIdx < Hits.Num(); HitIdx++)
				{
					// --- Start Difference from UPrimitiveComponent
					PullBackHit(Hits[HitIdx], DeltaSize);
					// --- End Difference from UPrimitiveComponent
				}
			}

			// If we had a valid blocking hit, store it.
			// If we are looking for overlaps, store those as well.
			int32 FirstNonInitialOverlapIdx = INDEX_NONE;

			if (bHadBlockingHit || (this->GetGenerateOverlapEvents() || bForceGatherOverlaps))
			{
				int32 BlockingHitIndex          = INDEX_NONE;
				float BlockingHitNormalDotDelta = BIG_NUMBER;

				for (int32 HitIdx = 0; HitIdx < Hits.Num(); HitIdx++)
				{
					const FHitResult& TestHit = Hits[HitIdx];

					if (TestHit.bBlockingHit)
					{
						if (!ShouldIgnoreHitResult(MyWorld, TestHit, Delta, Actor, MoveFlags))
						{
							if (TestHit.bStartPenetrating)
							{
								// We may have multiple initial hits, and want to choose the one with the normal most
								// opposed to our movement.
								const float NormalDotDelta = (TestHit.ImpactNormal | Delta);

								if (NormalDotDelta < BlockingHitNormalDotDelta)
								{
									BlockingHitNormalDotDelta = NormalDotDelta;
									BlockingHitIndex          = HitIdx;
								}
							}
							else if (BlockingHitIndex == INDEX_NONE)
							{
								// First non-overlapping blocking hit should be used, if an overlapping hit was not.
								// This should be the only non-overlapping blocking hit, and last in the results.
								BlockingHitIndex = HitIdx;
								break;
							}
						}
					}
					else if (this->GetGenerateOverlapEvents() || bForceGatherOverlaps)
					{
						UPrimitiveComponent* OverlapComponent = TestHit.Component.Get();

						if ((OverlapComponent != nullptr) &&
							(OverlapComponent->GetGenerateOverlapEvents() || bForceGatherOverlaps))
						{
							// --- Start Difference from UPrimitiveComponent
							bool bShouldIgnoreOverlapResult =
								ShouldIgnoreOverlapResult(
									MyWorld,
									Actor,
									*this->CollisionComponent,
									TestHit.GetActor(),
									*OverlapComponent,
									/*bCheckOverlapFlags=*/ !bForceGatherOverlaps
								);
							// --- End Difference from UPrimitiveComponent

							if (!bShouldIgnoreOverlapResult)
							{
								// don't process touch events after initial blocking hits
								if ((BlockingHitIndex >= 0) && (TestHit.Time > Hits[BlockingHitIndex].Time))
								{
									break;
								}

								if ((FirstNonInitialOverlapIdx == INDEX_NONE) && (TestHit.Time > 0.0f))
								{
									// We are about to add the first non-initial overlap.
									FirstNonInitialOverlapIdx = PendingOverlaps.Num();
								}

								// cache touches
								AddUniqueOverlapFast(PendingOverlaps, FOverlapInfo(TestHit));
							}
						}
					}
				}

				// Update blocking hit, if there was a valid one.
				if (BlockingHitIndex >= 0)
				{
					BlockingHit      = Hits[BlockingHitIndex];
					bFilledHitResult = true;
				}
			}

			// Update NewLocation based on the hit result
			if (!BlockingHit.bBlockingHit)
			{
				NewLocation = TraceEnd;
			}
			else
			{
				check(bFilledHitResult);

				NewLocation = TraceStart + (BlockingHit.Time * (TraceEnd - TraceStart));

				// Sanity check
				const FVector ToNewLocation = (NewLocation - TraceStart);

				if (ToNewLocation.SizeSquared() <= MinMovementDistSq)
				{
					// We don't want really small movements to put us on or inside a surface.
					NewLocation      = TraceStart;
					BlockingHit.Time = 0.0f;

					// Remove any pending overlaps after this point, we are not going as far as we swept.
					if (FirstNonInitialOverlapIdx != INDEX_NONE)
					{
						constexpr bool bAllowShrinking = false;

						PendingOverlaps.SetNum(FirstNonInitialOverlapIdx, bAllowShrinking);
					}
				}
			}

			bIncludesOverlapsAtEnd =
				this->AreSymmetricRotations(InitialRotationQuat, NewRotationQuat, GetComponentScale());

#if !(UE_BUILD_SHIPPING || UE_BUILD_TEST)
			if (UCheatManager::IsDebugCapsuleSweepPawnEnabled() && BlockingHit.bBlockingHit && !this->IsZeroExtent())
			{
				// When debugging, the sole purpose for this is to find how capsule trace information was when hit to
				// resolve stuck or improve our movement system - To turn this on, use DebugCapsuleSweepPawn.
				APawn const* const ActorPawn = (Actor ? Cast<APawn>(Actor) : nullptr);

				if ((ActorPawn  != nullptr) && (ActorPawn->Controller != nullptr) &&
					ActorPawn->Controller->IsLocalPlayerController())
				{
					APlayerController const* const PC = CastChecked<APlayerController>(ActorPawn->Controller);

					if (PC->CheatManager)
					{
						FVector CylExtent =
							ActorPawn->GetSimpleCollisionCylinderExtent() * FVector(1.001f, 1.001f, 1.0f);

						FCollisionShape CapsuleShape = FCollisionShape::MakeCapsule(CylExtent);

						PC->CheatManager->AddCapsuleSweepDebugInfo(
							CollisionTraceStart,
							CollisionTraceEnd,
							BlockingHit.ImpactPoint,
							BlockingHit.Normal,
							BlockingHit.ImpactNormal,
							BlockingHit.Location,
							CapsuleShape.GetCapsuleHalfHeight(),
							CapsuleShape.GetCapsuleRadius(),
							true,
							(BlockingHit.bStartPenetrating && BlockingHit.bBlockingHit) ? true : false
						);
					}
				}
			}
#endif
		}
		else if (DeltaSizeSq > 0.0f)
		{
			// apply move delta even if components has collisions disabled
			NewLocation           += Delta;
			bIncludesOverlapsAtEnd = false;
		}
		else if ((DeltaSizeSq == 0.0f) && bCollisionEnabled)
		{
			bIncludesOverlapsAtEnd =
				this->AreSymmetricRotations(InitialRotationQuat, NewRotationQuat, this->GetComponentScale());

			bRotationOnly = true;
		}

		// Update the location.  This will teleport any child components as well (not sweep).
		bMoved = this->InternalSetWorldLocationAndRotation(NewLocation, NewRotationQuat, bSkipPhysicsMove, Teleport);
	}
	else
	{
		// not sweeping, just go directly to the new transform
		bMoved = this->InternalSetWorldLocationAndRotation(TraceEnd, NewRotationQuat, bSkipPhysicsMove, Teleport);
		bRotationOnly = (DeltaSizeSq == 0);
		bIncludesOverlapsAtEnd =
			bRotationOnly &&
			(this->AreSymmetricRotations(InitialRotationQuat, NewRotationQuat, this->GetComponentScale())) &&
			this->IsQueryCollisionEnabled();
	}

	// Handle overlap notifications.
	if (bMoved)
	{
		if (this->IsDeferringMovementUpdates())
		{
			// Defer UpdateOverlaps until the scoped move ends.
			FScopedMovementUpdate* ScopedUpdate = this->GetCurrentScopedMovement();

			if (bRotationOnly && bIncludesOverlapsAtEnd)
			{
				ScopedUpdate->KeepCurrentOverlapsAfterRotation(bSweep);
			}
			else
			{
				ScopedUpdate->AppendOverlapsAfterMove(PendingOverlaps, bSweep, bIncludesOverlapsAtEnd);
			}
		}
		else
		{
			if (bIncludesOverlapsAtEnd)
			{
				TInlineOverlapInfoArray OverlapsAtEndLocation;
				bool                    bHasEndOverlaps       = false;

				if (bRotationOnly)
				{
					bHasEndOverlaps =
						this->ConvertRotationOverlapsToCurrentOverlaps(
							OverlapsAtEndLocation,
							this->OverlappingComponents
						);
				}
				else
				{
					bHasEndOverlaps =
						this->ConvertSweptOverlapsToCurrentOverlaps(
							OverlapsAtEndLocation,
							PendingOverlaps,
							0,
							this->GetComponentLocation(),
							this->GetComponentQuat()
						);
				}

				TOverlapArrayView PendingOverlapsView(PendingOverlaps);
				TOverlapArrayView OverlapsAtEndView(OverlapsAtEndLocation);

				this->UpdateOverlaps(&PendingOverlapsView, true, bHasEndOverlaps ? &OverlapsAtEndView : nullptr);
			}
			else
			{
				TOverlapArrayView PendingOverlapsView(PendingOverlaps);

				this->UpdateOverlaps(&PendingOverlapsView, true, nullptr);
			}
		}
	}

	// Handle blocking hit notifications. Avoid if pending kill (which could happen after overlaps).
	const bool bAllowHitDispatch =
		!BlockingHit.bStartPenetrating || !(MoveFlags & MOVECOMP_DisableBlockingOverlapDispatch);

	if (BlockingHit.bBlockingHit && bAllowHitDispatch && !this->IsPendingKill())
	{
		check(bFilledHitResult);

		if (this->IsDeferringMovementUpdates())
		{
			FScopedMovementUpdate* ScopedUpdate = this->GetCurrentScopedMovement();

			ScopedUpdate->AppendBlockingHitAfterMove(BlockingHit);
		}
		else
		{
			this->DispatchBlockingHit(*Actor, BlockingHit);
		}
	}

	// copy to optional output param
	if (OutHit != nullptr)
	{
		if (bFilledHitResult)
		{
			*OutHit = BlockingHit;
		}
		else
		{
			OutHit->Init(CollisionTraceStart, CollisionTraceEnd);
		}
	}

	// Return whether we moved at all.
	return bMoved;
}

void UPF2RootCollisionDelegateComponent::SetCollisionComponent(UPrimitiveComponent* Component)
{
	this->CollisionComponent = Component;
}

template<typename AllocatorType>
bool UPF2RootCollisionDelegateComponent::ConvertSweptOverlapsToCurrentOverlaps(
	TArray<FOverlapInfo, AllocatorType>& OverlapsAtEndLocation,
	const TOverlapArrayView&             SweptOverlaps,
	int32                                SweptOverlapsIndex,
	const FVector&                       EndLocation,
	const FQuat&                         EndRotationQuat)
{
	checkSlow(SweptOverlapsIndex >= 0);

	bool       bResult              = false;
	const bool bForceGatherOverlaps = !ShouldCheckOverlapFlagToQueueOverlaps(*this);

	if ((this->GetGenerateOverlapEvents() || bForceGatherOverlaps) &&
		PrimitiveComponentCVars::bAllowCachedOverlaps->GetBool())
	{
		const AActor* Actor = this->GetOwner();

		if ((Actor != nullptr) && (Actor->GetRootComponent() == this))
		{
			// We know we are not overlapping any new components at the end location. Children are ignored here (see
			// note below).
			if (PrimitiveComponentCVars::bEnableFastOverlapCheck->GetBool())
			{
				// Check components we hit during the sweep, keep only those still overlapping
				const FCollisionQueryParams UnusedQueryParams(NAME_None, FCollisionQueryParams::GetUnknownStatId());
				const int32                 NumSweptOverlaps = SweptOverlaps.Num();

				OverlapsAtEndLocation.Reserve(OverlapsAtEndLocation.Num() + NumSweptOverlaps);

				for (int32 Index = SweptOverlapsIndex; Index < NumSweptOverlaps; ++Index)
				{
					const FOverlapInfo&  OtherOverlap   = SweptOverlaps[Index];
					UPrimitiveComponent* OtherPrimitive = OtherOverlap.OverlapInfo.GetComponent();

					if ((OtherPrimitive != nullptr) &&
						(OtherPrimitive->GetGenerateOverlapEvents() || bForceGatherOverlaps))
					{
						if (OtherPrimitive->bMultiBodyOverlap)
						{
							// Not handled yet. We could do it by checking every body explicitly and track each body
							// index in the overlap test, but this seems like a rare need.
							return false;
						}
						else if ((Cast<USkeletalMeshComponent>(OtherPrimitive) != nullptr) ||
								 (Cast<USkeletalMeshComponent>(this) != nullptr))
						{
							// SkeletalMeshComponent does not support this operation, and would return false in the test
							// when an actual query could return true.
							return false;
						}
						else if (OtherPrimitive->ComponentOverlapComponent(this, EndLocation, EndRotationQuat, UnusedQueryParams))
						{
							OverlapsAtEndLocation.Add(OtherOverlap);
						}
					}
				}

				// Note: we don't worry about adding any child components here, because they are not included in the sweep results.
				// Children test for their own overlaps after we update our own, and we ignore children in our own update.
				checkfSlow(
					OverlapsAtEndLocation.FindByPredicate(FPredicateOverlapHasSameActor(*Actor)) == nullptr,
					TEXT("Child overlaps should not be included in the SweptOverlaps() array in UPF2RootCollisionDelegateComponent::ConvertSweptOverlapsToCurrentOverlaps()."));

				bResult = true;
			}
			else
			{
				if (SweptOverlaps.Num() == 0 && this->AreAllCollideableDescendantsRelative())
				{
					// Add overlaps with components in this actor.
					this->GetOverlapsWithActor_Template(Actor, OverlapsAtEndLocation);

					bResult = true;
				}
			}
		}
	}

	return bResult;
}

template<typename AllocatorType>
bool UPF2RootCollisionDelegateComponent::ConvertRotationOverlapsToCurrentOverlaps(
	TArray<FOverlapInfo, AllocatorType>& OutOverlapsAtEndLocation,
	const TOverlapArrayView&             CurrentOverlaps)
{
	bool       bResult              = false;
	const bool bForceGatherOverlaps = !ShouldCheckOverlapFlagToQueueOverlaps(*this);

	if ((this->GetGenerateOverlapEvents() || bForceGatherOverlaps) &&
		PrimitiveComponentCVars::bAllowCachedOverlaps->GetBool())
	{
		const AActor* Actor = this->GetOwner();

		if ((Actor != nullptr) && (Actor->GetRootComponent() == this))
		{
			if (PrimitiveComponentCVars::bEnableFastOverlapCheck->GetBool())
			{
				// Add all current overlaps that are not children. Children test for their own overlaps after we update
				// our own, and we ignore children in our own update.
				OutOverlapsAtEndLocation.Reserve(OutOverlapsAtEndLocation.Num() + CurrentOverlaps.Num());
				Algo::CopyIf(CurrentOverlaps, OutOverlapsAtEndLocation, FPredicateOverlapHasDifferentActor(*Actor));

				bResult = true;
			}
		}
	}

	return bResult;
}

template<typename AllocatorType>
bool UPF2RootCollisionDelegateComponent::GetOverlapsWithActor_Template(
	const AActor*                        Actor,
	TArray<FOverlapInfo, AllocatorType>& OutOverlaps) const
{
	const int32 InitialCount = OutOverlaps.Num();

	if (Actor != nullptr)
	{
		for (int32 OverlapIdx = 0; OverlapIdx < this->OverlappingComponents.Num(); ++OverlapIdx)
		{
			UPrimitiveComponent const* const PrimComp =
				this->OverlappingComponents[OverlapIdx].OverlapInfo.Component.Get();

			if ((PrimComp != nullptr) && (PrimComp->GetOwner() == Actor))
			{
				OutOverlaps.Add(this->OverlappingComponents[OverlapIdx]);
			}
		}
	}

	return InitialCount != OutOverlaps.Num();
}

#undef LOCTEXT_NAMESPACE

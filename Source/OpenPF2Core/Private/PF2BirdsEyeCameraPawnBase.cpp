// OpenPF2 for UE Game Logic, Copyright 2022-2023, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
//
// Portions of this code were adapted from or inspired by the "Real-Time Strategy Plugin for Unreal Engine 4" by Nick
// Pruehs, provided under the MIT License. Copyright (c) 2017 Nick Pruehs.
//

#include "PF2BirdsEyeCameraPawnBase.h"

#include <Camera/CameraComponent.h>
#include <Components/InputComponent.h>

void APF2BirdsEyeCameraPawnBase::FocusCameraOnActor(AActor* Actor)
{
	this->FocusCameraOnActors({Actor});
}

void APF2BirdsEyeCameraPawnBase::FocusCameraOnActors(TArray<AActor*> Actors)
{
	int32     ActorCount     = 0;
	FVector2D LocationSum    = FVector2D::ZeroVector;
	FVector2D CenterLocation;

	for (const AActor* Actor : Actors)
	{
		FVector ActorLocation;

		if (!IsValid(Actor))
		{
			continue;
		}

		ActorLocation = Actor->GetActorLocation();

		LocationSum.X += ActorLocation.X;
		LocationSum.Y += ActorLocation.Y;

		++ActorCount;
	}

	CenterLocation = LocationSum / ActorCount;

	this->FocusCameraOnLocation(CenterLocation);
}

void APF2BirdsEyeCameraPawnBase::FocusCameraOnLocation(const FVector2D NewCameraLocation)
{
	// Calculate where to put the camera, considering its angle, to center on the specified location.
	FVector FinalCameraLocation = FVector(NewCameraLocation.X - this->GetCameraDistance(), NewCameraLocation.Y, 0.0f);

	// Keep camera height.
	FinalCameraLocation.Z = this->GetActorLocation().Z;

	// Update camera location.
	this->SetActorLocation(FinalCameraLocation);
}

USceneComponent* APF2BirdsEyeCameraPawnBase::GetCameraComponent_Implementation() const
{
	return this->FindComponentByClass<UCameraComponent>();
}

float APF2BirdsEyeCameraPawnBase::GetCameraDistance() const
{
	const USceneComponent* Camera = this->GetCameraComponent();
	float                  CameraAngle;

	if (!IsValid(Camera))
	{
		return 0.0f;
	}

	// Get camera angle.
	CameraAngle = Camera->GetRelativeRotation().Pitch;

	if (CameraAngle < 0.0f)
	{
		CameraAngle += 90.0f;
	}

	// Get camera distance using trigonometry.
	// We are assuming that the terrain is flat, centered at the origin, and the camera has no roll or yaw.
	return Camera->GetRelativeLocation().Z * FMath::Tan(FMath::DegreesToRadians(CameraAngle));
}

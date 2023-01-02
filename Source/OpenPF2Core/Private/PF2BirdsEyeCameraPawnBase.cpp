// OpenPF2 for UE Game Logic, Copyright 2021-2022, Guy Elsmore-Paddock. All Rights Reserved.
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

APF2BirdsEyeCameraPawnBase::APF2BirdsEyeCameraPawnBase()
{
	this->CameraSpeed         = 1000.0f;
	this->CameraZoomSpeed     = 4000.0f;
	this->CameraTiltZoomSpeed = 2.0f;

	this->MinCameraDistance = 500.0f;
	this->MaxCameraDistance = 2500.0f;
}

void APF2BirdsEyeCameraPawnBase::Tick(const float DeltaSeconds)
{
	FVector           Location;
	UCameraComponent* PlayerPawnCamera;
	const float       CameraRightLeftInput  = FMath::Clamp(this->CameraRightLeftAxisValue, -1.0f, +1.0f);
	const float       CameraUpDownAxisInput = FMath::Clamp(this->CameraUpDownAxisValue,    -1.0f, +1.0f);
	const float       TiltZoomInput         = FMath::Clamp(this->CameraTiltZoomAxisValue,  -1.0f, +1.0f),
	                  TiltZoomValue         = this->CameraTiltZoomSpeed * TiltZoomInput * DeltaSeconds;

	Super::Tick(DeltaSeconds);

	// Apply lateral input.
    Location = this->GetActorLocation();
    Location += FVector::RightVector   * this->CameraSpeed * CameraRightLeftInput  * DeltaSeconds;
    Location += FVector::ForwardVector * this->CameraSpeed * CameraUpDownAxisInput * DeltaSeconds;

	this->SetActorLocation(Location);

    // Apply zoom input.
    PlayerPawnCamera = this->FindComponentByClass<UCameraComponent>();

    if (IsValid(PlayerPawnCamera))
    {
        FVector CameraLocation = PlayerPawnCamera->GetRelativeLocation();

    	CameraLocation.Z += this->CameraZoomSpeed * this->CameraZoomAxisValue * DeltaSeconds;
        CameraLocation.Z = FMath::Clamp(CameraLocation.Z, this->MinCameraDistance, this->MaxCameraDistance);

    	PlayerPawnCamera->SetRelativeLocation(CameraLocation);
    }

	// Apply tilt-zoom input.
	if (TiltZoomValue != 0.0f)
	{
		this->BP_OnApplyTiltZoom(TiltZoomValue);
	}

}

void APF2BirdsEyeCameraPawnBase::FocusCameraOnActor(AActor* Actor)
{
	this->FocusCameraOnActors({ Actor });
}

void APF2BirdsEyeCameraPawnBase::FocusCameraOnActors(TArray<AActor*> Actors)
{
	int32     ActorCount      = 0;
	FVector2D LocationSum     = FVector2D::ZeroVector;
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

void APF2BirdsEyeCameraPawnBase::FocusCameraOnLocation(FVector2D NewCameraLocation)
{
    // Calculate where to put the camera, considering its angle, to center on the specified location.
    FVector FinalCameraLocation = FVector(NewCameraLocation.X - GetCameraDistance(), NewCameraLocation.Y, 0.0f);

    // Keep camera height.
    FinalCameraLocation.Z = this->GetActorLocation().Z;

    // Update camera location.
    this->SetActorLocation(FinalCameraLocation);
}

void APF2BirdsEyeCameraPawnBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveCameraRightLeft"), this, &APF2BirdsEyeCameraPawnBase::MoveCameraRightLeft);
	PlayerInputComponent->BindAxis(TEXT("MoveCameraUpDown"),    this, &APF2BirdsEyeCameraPawnBase::MoveCameraUpDown);
    PlayerInputComponent->BindAxis(TEXT("ZoomCamera"),          this, &APF2BirdsEyeCameraPawnBase::ZoomCamera);
    PlayerInputComponent->BindAxis(TEXT("TiltZoomCamera"),      this, &APF2BirdsEyeCameraPawnBase::TiltZoomCamera);
}

void APF2BirdsEyeCameraPawnBase::MoveCameraRightLeft(const float Value)
{
    this->CameraRightLeftAxisValue = Value;
}

void APF2BirdsEyeCameraPawnBase::MoveCameraUpDown(const float Value)
{
    this->CameraUpDownAxisValue = Value;
}

void APF2BirdsEyeCameraPawnBase::ZoomCamera(const float Value)
{
    this->CameraZoomAxisValue = Value;
}

void APF2BirdsEyeCameraPawnBase::TiltZoomCamera(const float Value)
{
	this->CameraTiltZoomAxisValue = Value;
}

float APF2BirdsEyeCameraPawnBase::GetCameraDistance() const
{
	const UCameraComponent* Camera = this->FindComponentByClass<UCameraComponent>();
	float CameraAngle;

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

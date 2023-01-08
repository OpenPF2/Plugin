// OpenPF2 for UE Game Logic, Copyright 2022-2023, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
//
// Portions of this code were adapted from or inspired by the "Real-Time Strategy Plugin for Unreal Engine 4" by Nick
// Pruehs, provided under the MIT License. Copyright (c) 2017 Nick Pruehs.

#pragma once

#include <Components/SceneComponent.h>
#include <Camera/CameraComponent.h>

#include <GameFramework/Pawn.h>

#include "PF2BirdsEyeCameraPawnBase.generated.h"

/**
 * Base class for invisible pawns that are possessed while in a top-down, tactical view for encounters.
 */
UCLASS(Abstract)
// ReSharper disable once CppClassCanBeFinal
class OPENPF2CORE_API APF2BirdsEyeCameraPawnBase : public APawn
{
	GENERATED_BODY()

public:
	// =================================================================================================================
	// Public Methods
	// =================================================================================================================
	/**
     * Focuses the camera on a specific actor.
     *
     * @param Actor
     *	The actor to focus on.
     */
	UFUNCTION(BlueprintCallable)
	void FocusCameraOnActor(AActor* Actor);

	/**
	 * Focuses the camera on showing all of the specified actors.
	 *
	 * @param Actors
	 *	The actors to focus on.
	 */
	UFUNCTION(BlueprintCallable)
	void FocusCameraOnActors(TArray<AActor*> Actors);

	/**
	 * Focuses the camera on a specific world location.
	 *
	 * @param NewCameraLocation
	 *	The location to focus on.
	 */
	UFUNCTION(BlueprintCallable)
	void FocusCameraOnLocation(FVector2D NewCameraLocation);

protected:
	// =================================================================================================================
	// Protected Methods
	// =================================================================================================================
	/**
	 * Gets the camera component inside this pawn that the player will control and use to see the world.
	 *
	 * @return
	 *	The camera component.
	 */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="OpenPF2|Bird's Eye Camera Pawns")
	USceneComponent* GetCameraComponent() const;

	/**
	 * Gets the distance from the camera to an object in the level.
	 *
	 * @return
	 *	The distance from the camera to the object, in centimeters (cm).
	 */
	float GetCameraDistance() const;
};

// OpenPF2 for UE Game Logic, Copyright 2022, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#pragma once

#include <GameplayAbilitySpec.h>

#include "Utilities/PF2LogIdentifiableInterface.h"

#include "PF2CharacterControllerInterface.generated.h"

// =====================================================================================================================
// Forward Declarations (to break recursive dependencies)
// =====================================================================================================================
class IPF2CharacterInterface;

// =====================================================================================================================
// Normal Declarations
// =====================================================================================================================
UINTERFACE(MinimalAPI, BlueprintType, meta=(CannotImplementInterfaceInBlueprint))
class UPF2CharacterControllerInterface : public UPF2LogIdentifiableInterface
{
	GENERATED_BODY()
};

/**
 * An interface for controllers that can possess characters (both player controllers and AI controllers).
 */
class OPENPF2CORE_API IPF2CharacterControllerInterface : public IPF2LogIdentifiableInterface
{
	GENERATED_BODY()

public:
	// =================================================================================================================
	// Public Methods
	// =================================================================================================================
	/**
	 * Performs an ability on one of the characters that this controller is able to control.
	 *
	 * The given character must be controllable by this controller.
	 *
	 * @param AbilitySpecHandle
	 *	The handle for the ability to activate.
	 * @param TargetCharacter
	 *	The character upon which the ability should be activated.
	 */
	UFUNCTION(BlueprintCallable, Category="OpenPF2|TargetCharacter Controllers")
	virtual void PerformAbilityOnControllableCharacter(
		const FGameplayAbilitySpecHandle                AbilitySpecHandle,
		const TScriptInterface<IPF2CharacterInterface>& TargetCharacter) = 0;
};

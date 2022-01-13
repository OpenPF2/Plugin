// OpenPF2 for UE Game Logic, Copyright 2021, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#pragma once

#include <UObject/Interface.h>

#include "PF2GameStateInterface.h"
#include "GameModes/PF2ModeOfPlayType.h"

#include "PF2PlayerControllerInterface.generated.h"

UINTERFACE(MinimalAPI, BlueprintType)
class UPF2PlayerControllerInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * An interface for OpenPF2-compatible Player Controllers.
 */
class OPENPF2CORE_API IPF2PlayerControllerInterface
{
	GENERATED_BODY()

public:
	/**
	 * Notifies this player controller that the mode of play has changed.
	 *
	 * (This should normally be invoked only by the game state).
	 *
	 * @see EPF2ModeOfPlay
	 */
	UFUNCTION(BlueprintImplementableEvent, Category="OpenPF2|Player Controllers")
	void OnModeOfPlayChanged(EPF2ModeOfPlayType NewMode);

	/**
	 * Gets the character that this player controller is controlling.
	 */
	UFUNCTION(BlueprintNativeEvent, Category="OpenPF2|Player Controllers")
	TScriptInterface<IPF2CharacterInterface> GetControlledCharacter();
};

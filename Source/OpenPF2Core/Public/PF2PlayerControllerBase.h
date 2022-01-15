// OpenPF2 for UE Game Logic, Copyright 2021, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#pragma once

#include <GameFramework/PlayerController.h>

#include "PF2PlayerControllerInterface.h"
#include "PF2PlayerControllerBase.generated.h"

/**
 * Default base class for PF2 Player Controllers.
 *
 * @see IPF2PlayerControllerInterface
 */
UCLASS(Abstract)
// ReSharper disable once CppClassCanBeFinal
class OPENPF2CORE_API APF2PlayerControllerBase : public APlayerController, public IPF2PlayerControllerInterface
{
	GENERATED_BODY()

public:
	// =================================================================================================================
	// Public Methods - IPF2PlayerControllerInterface Implementation
	// =================================================================================================================
	virtual void HandleModeOfPlayChanged(EPF2ModeOfPlayType NewMode) override;
	virtual TScriptInterface<IPF2CharacterInterface> GetControlledCharacter() override;
	virtual APlayerController* ToPlayerController() override;

protected:
	// =================================================================================================================
	// Blueprint Event Callbacks
	// =================================================================================================================
	/**
	 * BP event invoked when the mode of play has changed.
	 *
	 * @param NewMode
	 *	The new mode of play.
	 */
	UFUNCTION(BlueprintImplementableEvent, Category="OpenPF2|Player Controllers")
	void OnModeOfPlayChanged(EPF2ModeOfPlayType NewMode);

};

// OpenPF2 for UE Game Logic, Copyright 2021-2022, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#pragma once

#include <GameFramework/PlayerController.h>

#include "PF2PlayerControllerInterface.h"

#include "PF2PlayerControllerBase.generated.h"

// =====================================================================================================================
// Forward Declarations (to break recursive dependencies)
// =====================================================================================================================
class IPF2CharacterInterface;
class IPF2CharacterCommandInterface;

// =====================================================================================================================
// Normal Declarations
// =====================================================================================================================
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
	// Public Methods - AController Overrides
	// =================================================================================================================
	virtual void SetPawn(APawn* NewPawn) override;

	// =================================================================================================================
	// Public Methods - IPF2PlayerControllerInterface Implementation
	// =================================================================================================================
	UFUNCTION(BlueprintCallable)
	virtual TScriptInterface<IPF2PlayerStateInterface> GetPlayerState() const override;

	UFUNCTION(BlueprintCallable)
	virtual APlayerController* ToPlayerController() override;

	UFUNCTION()
	virtual void HandleModeOfPlayChanged(EPF2ModeOfPlayType NewMode) override;

	UFUNCTION(NetMulticast, Reliable)
	virtual void MulticastHandleEncounterTurnStarted() override;

	UFUNCTION(NetMulticast, Reliable)
	virtual void MulticastHandleEncounterTurnEnded() override;

	// =================================================================================================================
	// Public Methods - IPF2LogIdentifiableInterface Overrides
	// =================================================================================================================
	UFUNCTION(BlueprintCallable)
	virtual FString GetIdForLogs() const override;

protected:
	// =================================================================================================================
	// Blueprint Implementable Events
	// =================================================================================================================
	/**
	 * BP event invoked when the mode of play has changed.
	 *
	 * This is invoked on both the owning client and server.
	 *
	 * @param NewMode
	 *	The new mode of play.
	 */
	UFUNCTION(BlueprintImplementableEvent, Category="OpenPF2|Player Controllers")
	void OnModeOfPlayChanged(EPF2ModeOfPlayType NewMode);

	/**
	 * BP event invoked when the pawn's turn during an encounter has started.
	 *
	 * This is invoked on both the owning client and server.
	 */
	UFUNCTION(BlueprintImplementableEvent, Category="OpenPF2|Player Controllers")
	void OnEncounterTurnStarted();

	/**
	 * BP event invoked when the pawn's turn during an encounter has ended.
	 *
	 * This is invoked on both the owning client and server.
	 */
	UFUNCTION(BlueprintImplementableEvent, Category="OpenPF2|Player Controllers")
	void OnEncounterTurnEnded();
};

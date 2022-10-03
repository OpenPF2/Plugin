// OpenPF2 for UE Game Logic, Copyright 2022, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#pragma once

#include <GameFramework/PlayerState.h>

#include <Kismet/BlueprintFunctionLibrary.h>

#include "PF2ConversionsLibrary.generated.h"

// =====================================================================================================================
// Forward Declarations (to minimize header dependencies)
// =====================================================================================================================
class IPF2CharacterInterface;
class IPF2PlayerControllerInterface;
class IPF2PlayerStateInterface;

// =====================================================================================================================
// Normal Declarations
// =====================================================================================================================
/**
 * Function library for automatic conversions that improve Game Designer quality of life when working with OpenPF2.
 */
UCLASS()
class UPF2ConversionsLibrary final : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/**
	 * Converts a character to an actor.
	 *
	 * @param Character
	 *	The character interface instance to convert.
	 *
	 * @return
	 *	The resulting actor.
	 */
	UFUNCTION(
		BlueprintPure,
		meta=(DisplayName = "To Actor", CompactNodeTitle = "->", BlueprintAutocast),
		Category="OpenPF2|Conversions"
	)
	static AActor* Conv_CharacterIntfToActor(const TScriptInterface<IPF2CharacterInterface>& Character);

	/**
	 * Converts a character to a pawn.
	 *
	 * @param Character
	 *	The character interface instance to convert.
	 *
	 * @return
	 *	The resulting pawn.
	 */
	UFUNCTION(
		BlueprintPure,
		meta=(DisplayName = "To Pawn", CompactNodeTitle = "->", BlueprintAutocast),
		Category="OpenPF2|Conversions"
	)
	static APawn* Conv_CharacterIntfToPawn(const TScriptInterface<IPF2CharacterInterface>& Character);

	/**
	 * Converts a player controller interface to a standard controller actor.
	 *
	 * @param PlayerController
	 *	The player controller interface instance to convert.
	 *
	 * @return
	 *	The resulting controller.
	 */
	UFUNCTION(
		BlueprintPure,
		meta=(DisplayName = "To Controller", CompactNodeTitle = "->", BlueprintAutocast),
		Category="OpenPF2|Conversions"
	)
	static AController* Conv_PlayerControllerIntfToController(
		const TScriptInterface<IPF2PlayerControllerInterface>& PlayerController
	);

	/**
	 * Converts a player controller interface to a standard player controller actor.
	 *
	 * @param PlayerController
	 *	The player controller interface instance to convert.
	 *
	 * @return
	 *	The resulting player controller.
	 */
	UFUNCTION(
		BlueprintPure,
		meta=(DisplayName = "To Player Controller", CompactNodeTitle = "->", BlueprintAutocast),
		Category="OpenPF2|Conversions"
	)
	static APlayerController* Conv_PlayerControllerIntfToPlayerController(
		const TScriptInterface<IPF2PlayerControllerInterface>& PlayerController
	);

	/**
	 * Converts a player state interface to a standard player state actor.
	 *
	 * @param PlayerState
	 *	The player state interface instance to convert.
	 *
	 * @return
	 *	The resulting player state.
	 */
	UFUNCTION(
		BlueprintPure,
		meta=(DisplayName = "To Player State", CompactNodeTitle = "->", BlueprintAutocast),
		Category="OpenPF2|Conversions"
	)
	static APlayerState* Conv_PlayerStateIntfToPlayerState(
		const TScriptInterface<IPF2PlayerStateInterface>& PlayerState
	);
};

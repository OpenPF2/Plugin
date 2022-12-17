// OpenPF2 for UE Game Logic, Copyright 2021-2022, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#pragma once

#include <GameplayAbilitySpec.h>

#include <GameFramework/Info.h>

#include "GameModes/PF2ModeOfPlayType.h"

#include "Utilities/PF2LogIdentifiableInterface.h"

#include "PF2PlayerControllerInterface.generated.h"

// =====================================================================================================================
// Forward Declarations (to minimize header dependencies)
// =====================================================================================================================
class IPF2CharacterInterface;
class IPF2ModeOfPlayRuleSetInterface;
class IPF2PlayerStateInterface;

// =====================================================================================================================
// Normal Declarations
// =====================================================================================================================
UINTERFACE(MinimalAPI, BlueprintType, meta=(CannotImplementInterfaceInBlueprint))
class UPF2PlayerControllerInterface : public UPF2LogIdentifiableInterface
{
	GENERATED_BODY()
};

/**
 * An interface for OpenPF2-compatible Player Controllers.
 */
class OPENPF2CORE_API IPF2PlayerControllerInterface : public IPF2LogIdentifiableInterface
{
	GENERATED_BODY()

public:
	// =================================================================================================================
	// Public Methods
	// =================================================================================================================
	/**
	 * Gets the player state of this player controller.
	 *
	 * If called on the client and the player state has not yet been replicated, this will return a null script
	 * interface.
	 *
	 * @return
	 *	The OpenPF2-specific player state.
	 */
	UFUNCTION(BlueprintCallable, Category="OpenPF2|Player Controllers")
	virtual TScriptInterface<IPF2PlayerStateInterface> GetPlayerState() const = 0;

	/**
	 * Gets the character(s) that the player has the ability to control or possess.
	 *
	 * For a single-player game that supports parties or squads, this may include both the character that the player
	 * is actively controlling as well as any controllable character in this player's party or squad. Otherwise, this
	 * will return only a single character per controller.
	 *
	 * All the characters returned will each be in the same party as the player, but not all characters in the party are
	 * necessarily controllable by the current player (e.g., in a multiplayer RPG, two players may be in the same party
	 * but may be restricted from being able to control each other's characters).
	 *
	 * @return
	 *	All of the characters that this player controller can control.
	 */
	UFUNCTION(BlueprintCallable, Category="OpenPF2|Player Controllers")
	virtual TArray<TScriptInterface<IPF2CharacterInterface>> GetControllableCharacters() const = 0;

	/**
	 * Gets the last target location that the player has chosen through the UI.
	 *
	 * @return
	 *	A hit result for the target location that the player has chosen through the UI.
	 */
	UFUNCTION(BlueprintCallable, Category="OpenPF2|Player Controllers")
	virtual FHitResult GetTargetLocation() const = 0;

	/**
	 * Gets the player controller that is implementing this interface.
	 *
	 * @return
	 *	This player controller, as a player controller actor.
	 */
	UFUNCTION(BlueprintCallable, Category="OpenPF2|Player Controllers")
	virtual APlayerController* ToPlayerController() = 0;

	/**
	 * Adds the specified character to the list of characters that the player can control.
	 *
	 * The character must be affiliated with the same party as the player to which this player state corresponds.
	 *
	 * @param GivenCharacter
	 *	The character to give to this player.
	 */
	UFUNCTION(BlueprintCallable, Category="OpenPF2|Player Controllers")
	virtual void GiveCharacter(const TScriptInterface<IPF2CharacterInterface>& GivenCharacter) = 0;

	/**
	 * Removes the specified character from the list of characters that the player can control.
	 *
	 * @param ReleasedCharacter
	 *   The character to release from the player's controller.
	 */
	UFUNCTION(BlueprintCallable, Category="OpenPF2|Player Controllers")
	virtual void ReleaseCharacter(const TScriptInterface<IPF2CharacterInterface>& ReleasedCharacter) = 0;

	/**
	 * Builds and executes a command on the server for one of the characters this player controller can control.
	 *
	 * The given character must be controllable by this player controller, but may be possessed by either this player
	 * controller or an AI controller.
	 *
	 * Since this is an RPC, the character is passed as an actor instead of as an interface reference because UE will
	 * not replicate actors if they are declared/referenced through an interface property.
	 *
	 * @param AbilitySpecHandle
	 *	The handle for the ability to activate.
	 * @param CharacterActor
	 *	The character upon which the ability should be activated. The given actor must implement IPF2CharacterInterface.
	 */
	UFUNCTION(BlueprintCallable, Server, Reliable, Category="OpenPF2|Player Controllers")
	virtual void Server_ExecuteCharacterCommand(const FGameplayAbilitySpecHandle AbilitySpecHandle,
	                                            AActor*                          CharacterActor) = 0;

	/**
	 * Requests to cancel a command on the server for one of the characters this player controller can control.
	 *
	 * The character that the command targets must be controllable by this player controller, but may be possessed by
	 * either this player controller or an AI controller.
	 *
	 * Since this is an RPC, the command is passed as an actor instead of as an interface reference because UE will
	 * not replicate actors if they are declared/referenced through an interface property.
	 *
	 * @param Command
	 *	The command that should be cancelled. The given actor must implement the
	 *	IPF2CharacterCommandInterface interface.
	 */
	UFUNCTION(BlueprintCallable, Server, Reliable, Category="OpenPF2|Player Controllers")
	virtual void Server_CancelCharacterCommand(AInfo* Command) = 0;

	// =================================================================================================================
	// Public Event Notifications from the Game Mode
	// =================================================================================================================
	/**
	 * Notifies this player controller that its playable characters have just entered the world.
	 *
	 * (This should normally be invoked only by the game mode).
	 *
	 * @param RuleSet
	 *	The active Mode of Play Rule Set.
	 */
	virtual void Native_OnPlayableCharactersStarting(TScriptInterface<IPF2ModeOfPlayRuleSetInterface> RuleSet) = 0;

	// =================================================================================================================
	// Public Event Notifications from the Game State
	// =================================================================================================================
	/**
	 * Notifies this player controller that the mode of play has changed.
	 *
	 * (This should normally be invoked only by the game state).
	 *
	 * @see EPF2ModeOfPlay
	 *
	 * @param NewMode
	 *	The new mode of play.
	 */
	virtual void Native_OnModeOfPlayChanged(EPF2ModeOfPlayType NewMode) = 0;

	// =================================================================================================================
	// Public Event Notifications from Mode of Play Rule Sets (MoPRS)
	// =================================================================================================================
	/**
	 * Notifies this player controller that the pawn's turn during an encounter has started.
	 *
	 * (This should normally be invoked only by the MoPRS).
	 */
	UFUNCTION(NetMulticast, Reliable)
	virtual void Multicast_OnEncounterTurnStarted() = 0;

	/**
	 *  Notifies this player controller that the pawn's turn during an encounter has ended.
	 *
	 * (This should normally be invoked only by the MoPRS).
	 */
	UFUNCTION(NetMulticast, Reliable)
	virtual void Multicast_OnEncounterTurnEnded() = 0;
};

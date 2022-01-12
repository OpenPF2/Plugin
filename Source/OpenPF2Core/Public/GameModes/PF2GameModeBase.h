// OpenPF2 for UE Game Logic, Copyright 2021, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#pragma once

#include <GameFramework/GameModeBase.h>
#include <UObject/ScriptInterface.h>

#include "OpenPF2Core.h"

#include "GameModes/PF2ModeOfPlayRuleSetBase.h"
#include "GameModes/PF2GameModeInterface.h"

#include "PF2GameModeBase.generated.h"

/**
 * Default base class for PF2 Game Modes.
 *
 * @see IPF2GameModeInterface
 */
UCLASS(Abstract)
// ReSharper disable once CppClassCanBeFinal
class OPENPF2CORE_API APF2GameModeBase : public AGameModeBase, public IPF2GameModeInterface
{
	GENERATED_BODY()

protected:
	// =================================================================================================================
	// Protected Properties
	// =================================================================================================================
	/**
	 * Map from Modes of Play to the Rule Set to use for each mode.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Mode of Play Rules")
	TMap<EPF2ModeOfPlayType, TSubclassOf<UPF2ModeOfPlayRuleSetBase>> ModeRuleSets;

public:
	// =================================================================================================================
	// Public Constructors
	// =================================================================================================================
	/**
	 * Default constructor for APF2GameModeBase.
	 */
	explicit APF2GameModeBase();

	// =================================================================================================================
	// Public Methods - IPF2GameModeInterface Implementation
	// =================================================================================================================
	virtual FORCEINLINE TScriptInterface<IPF2ModeOfPlayRuleSetInterface> CreateModeOfPlayRuleSet(
		const EPF2ModeOfPlayType ModeOfPlay) override;

	virtual void RequestEncounterMode() override;
	virtual void RequestExplorationMode() override;
	virtual void RequestDowntimeMode() override;

	virtual void AddCharacterToEncounter(const TScriptInterface<IPF2CharacterInterface>& Character) override;

	virtual void RemoveCharacterFromEncounter(const TScriptInterface<IPF2CharacterInterface>& Character) override;

	virtual void QueueActionForInitiativeTurn(TScriptInterface<IPF2CharacterInterface>&    Character,
	                                          TScriptInterface<IPF2QueuedActionInterface>& Action) override;

	virtual void CancelActionQueuedForInitiativeTurn(TScriptInterface<IPF2CharacterInterface>&    Character,
	                                                 TScriptInterface<IPF2QueuedActionInterface>& Action) override;

protected:
	// =================================================================================================================
	// Protected Methods - AActor Overrides
	// =================================================================================================================
	virtual void BeginPlay() override;
	virtual void Tick(const float DeltaSeconds) override;

	// =================================================================================================================
	// Protected Methods
	// =================================================================================================================

	/**
	 * Gets the active Mode of Play Rule Set (MoPRS) from the game state.
	 *
	 * @return
	 *	The active MoPRS, wrapped in a script interface (for Blueprint). If there is not a compatible game state loaded,
	 *	or there is no active MoPRS, the script interface wraps nullptr.
	 */
	virtual FORCEINLINE TScriptInterface<IPF2ModeOfPlayRuleSetInterface> GetModeOfPlayRuleSet()
	{
		TScriptInterface<IPF2ModeOfPlayRuleSetInterface> RuleSet;
		IPF2GameStateInterface*                          Pf2GameState = this->GetGameState<IPF2GameStateInterface>();

		if (Pf2GameState == nullptr)
		{
			UE_LOG(
				LogPf2Core,
				Error,
				TEXT("Mode of Play Rule Set (MoPRS) support is not enabled because the current game state is not compatible with PF2.")
			);

			RuleSet = TScriptInterface<IPF2ModeOfPlayRuleSetInterface>();
		}
		else
		{
			RuleSet = Pf2GameState->GetModeOfPlayRuleSet();
		}

		return RuleSet;
	}

	/**
	 * Attempts to change the current play mode for all characters in the loaded level.
	 *
	 * The mode of play is only changed if the rule set for the current mode of play allows the transition. If the mode
	 * of play is changed, all player controllers are notified of the change in mode via game state replication. If the
	 * mode of play is not changed, nothing happens.
	 *
	 * @see EPF2ModeOfPlay
	 *
	 * @param NewModeOfPlay
	 *	The new play mode.
	 */
	void AttemptModeOfPlaySwitch(const EPF2ModeOfPlayType NewModeOfPlay);

	/**
	 * Immediately switches the current play mode for all characters in the loaded level.
	 *
	 * All player controllers are notified of the change in mode via game state replication.
	 *
	 * @param NewModeOfPlay
	 *	The mode of play to switch to.
	 */
	void ForceSwitchModeOfPlay(const EPF2ModeOfPlayType NewModeOfPlay);
};

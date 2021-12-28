// OpenPF2 for UE Game Logic, Copyright 2021, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#pragma once

#include <GameFramework/GameStateBase.h>
#include <UObject/ScriptInterface.h>

#include "PF2GameStateInterface.h"
#include "GameModes/PF2ModeOfPlayType.h"

#include "PF2GameStateBase.generated.h"

/**
 * Default base class for PF2 Game States.
 *
 * @see IPF2GameStateInterface
 */
UCLASS(Abstract)
// ReSharper disable once CppClassCanBeFinal
class OPENPF2CORE_API APF2GameStateBase : public AGameStateBase, public IPF2GameStateInterface
{
	GENERATED_BODY()

protected:
	// =================================================================================================================
	// Protected Properties - Blueprint Accessible
	// =================================================================================================================
	/**
	 * The current play mode for all characters in the loaded level.
	 *
	 * @see IPF2GameStateInterface::GetModeOfPlay
	 */
	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly, Category = GameState, ReplicatedUsing=OnRep_ModeOfPlay)
	EPF2ModeOfPlayType ModeOfPlay;

	/**
	 * The set of rules that govern how the game behaves in the current play mode.
	 *
	 * @see IPF2ModeOfPlayRuleSet
	 */
	UPROPERTY(Transient, BlueprintReadOnly, Category = GameState)
	TScriptInterface<IPF2ModeOfPlayRuleSet> ModeOfPlayRuleSet;

public:
	// =================================================================================================================
	// Public Constructors
	// =================================================================================================================
	/**
	 * Default constructor for APF2GameStateBase.
	 */
	explicit APF2GameStateBase();

	// =================================================================================================================
	// Public Methods - AGameStateBase Implementation
	// =================================================================================================================
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	// =================================================================================================================
	// Public Methods - IPF2GameStateInterface Implementation
	// =================================================================================================================
	virtual FORCEINLINE EPF2ModeOfPlayType GetModeOfPlay() override
	{
		return this->ModeOfPlay;
	}

	virtual TScriptInterface<IPF2ModeOfPlayRuleSet> GetModeOfPlayRuleSet() override
	{
		return this->ModeOfPlayRuleSet;
	}

	virtual void SwitchModeOfPlay(const EPF2ModeOfPlayType                NewMode,
	                              TScriptInterface<IPF2ModeOfPlayRuleSet> NewRuleSet) override;

protected:
	// =================================================================================================================
	// Protected Methods
	// =================================================================================================================
	/**
	 * Replication callback for the "Mode of Play" property.
	 *
	 * This notifies all player controllers that the play mode has changed (e.g., to change HUD display or background
	 * music to suit the new play mode).
	 */
	UFUNCTION()
	virtual void OnRep_ModeOfPlay();
};

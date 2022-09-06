// OpenPF2 for UE Game Logic, Copyright 2022, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
//
// Portions of this code were adapted from or inspired by the "Real-Time Strategy Plugin for Unreal Engine 4" by Nick
// Pruehs, provided under the MIT License. Copyright (c) 2017 Nick Pruehs.

#pragma once

#include <AIController.h>

#include "PF2AIControllerInterface.h"

#include "PF2AiControllerBase.generated.h"

// =====================================================================================================================
// Normal Declarations
// =====================================================================================================================
/**
 * Default base class for OpenPF2 AI Controllers.
 *
 * @see IPF2AIControllerInterface
 */
UCLASS(Abstract)
// ReSharper disable once CppClassCanBeFinal
class OPENPF2CORE_API APF2AIControllerBase : public AAIController, public IPF2AIControllerInterface
{
	GENERATED_BODY()

protected:
	// FIXME: What if multiple commands come in in quick succession? This is only a short-term fix.
	/**
	 * The key in the blackboard of the behavior tree of this controller that contains the next command to execute.
	 *
	 * The behavior tree is expected to consume the command and clear the value of this key promptly.
	 */
	UPROPERTY(EditDefaultsOnly, Category="Blackboard")
	FName NextCommandKey;

public:
	// =================================================================================================================
	// Public Constructors
	// =================================================================================================================
	APF2AIControllerBase() : NextCommandKey("NextCommand")
	{
	}

	// =================================================================================================================
	// Public Methods - IPF2CharacterControllerInterface Implementation
	// =================================================================================================================
	UFUNCTION(BlueprintCallable)
	virtual void PerformAbilityOnControllableCharacter(
		const FGameplayAbilitySpecHandle                AbilitySpecHandle,
		const TScriptInterface<IPF2CharacterInterface>& TargetCharacter) override;

	// =================================================================================================================
	// Public Methods - IPF2LogIdentifiableInterface Overrides
	// =================================================================================================================
	UFUNCTION(BlueprintCallable)
	virtual FString GetIdForLogs() const override;

protected:
	// =================================================================================================================
	// Protected Methods
	// =================================================================================================================
	// FIXME: What if multiple commands come in in quick succession? This is only a short-term fix.
	/**
	 * Gets the name of the blackboard key containing the next command to execute.
	 *
	 * @return
	 *	The name of the blackboard key for the next command.
	 */
	FORCEINLINE FName GetBlackboardNextCommandKey() const
	{
		return this->NextCommandKey;
	}
};

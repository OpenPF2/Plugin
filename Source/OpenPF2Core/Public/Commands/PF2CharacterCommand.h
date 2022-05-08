// OpenPF2 for UE Game Logic, Copyright 2022, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#pragma once

#include <CoreMinimal.h>
#include <UObject/Object.h>

#include "Abilities/PF2GameplayAbilityInterface.h"
#include "GameplayAbilitySpec.h"
#include "PF2CharacterCommandInterface.h"
#include "PF2CharacterInterface.h"

#include "PF2CharacterCommand.generated.h"

/**
 * A command that wraps a character ability that can be executed at any time in the future (including immediately).
 *
 * (The inspiration for this approach -- of wrapping Gameplay Abilities in a command that can be invoked at any time --
 * came from "ue4-orders-abilities" by Daedalic Entertainment,
 * https://github.com/DaedalicEntertainment/ue4-orders-abilities).
 */
UCLASS(BlueprintType)
// ReSharper disable once CppClassCanBeFinal
class OPENPF2CORE_API UPF2CharacterCommand : public UObject, public IPF2CharacterCommandInterface
{
	GENERATED_BODY()

protected:
	/**
	 * The character who would be issued this command.
	 */
	IPF2CharacterInterface* CharacterIntf;

	/**
	 * The specification for the ability that this command will trigger when it is executed.
	 */
	FGameplayAbilitySpec* AbilitySpec;

public:
	// =================================================================================================================
	// Public Static Methods
	// =================================================================================================================
	/**
	 * Creates a new UPF2CharacterCommand for the given character and ability specification.
	 *
	 * @param CharacterIntf
	 *	The character who would be issued the command.
	 * @param AbilitySpec
	 *	The specification for the ability that the command will trigger when it is executed.
	 *
	 * @return
	 *	The new command.
	 */
	static UPF2CharacterCommand* Create(IPF2CharacterInterface* CharacterIntf, FGameplayAbilitySpec* AbilitySpec)
	{
		UPF2CharacterCommand* Command = NewObject<UPF2CharacterCommand>();

		Command->CharacterIntf = CharacterIntf;
		Command->AbilitySpec   = AbilitySpec;

		return Command;
	};

protected:
	// =================================================================================================================
	// Protected Constructors
	// =================================================================================================================
	explicit UPF2CharacterCommand() : CharacterIntf(nullptr), AbilitySpec(nullptr)
	{
	}

public:
	// =================================================================================================================
	// Public Methods - IPF2CharacterCommandInterface Overrides
	// =================================================================================================================
	UFUNCTION(BlueprintCallable)
	virtual UTexture2D* GetCommandIcon() const override;

	UFUNCTION(BlueprintCallable)
	virtual FText GetCommandLabel() const override;

	UFUNCTION(BlueprintCallable)
	virtual FText GetCommandDescription() const override;

	UFUNCTION(BlueprintCallable)
	virtual EPF2CommandExecuteOrQueueResult AttemptExecuteOrQueue() override;

	UFUNCTION(BlueprintCallable)
	virtual EPF2CommandExecuteOrBlockResult AttemptExecuteOrBlock() override;

	// =================================================================================================================
	// Protected Methods
	// =================================================================================================================
protected:
	/**
	 * Gets the character who would be issued this command.
	 *
	 * @return
	 *	The character.
	 */
	IPF2CharacterInterface* GetCharacter() const
	{
		return this->CharacterIntf;
	}

	/**
	 * Gets the specification for the ability that this command will trigger when it is executed.
	 *
	 * @return
	 *	The ability specification.
	 */
	FORCEINLINE FGameplayAbilitySpec* GetAbilitySpec() const
	{
		return this->AbilitySpec;
	}

	/**
	 * Gets the CDO for the ability that this command will trigger when it is executed.
	 *
	 * @return
	 *	The gameplay ability.
	 */
	FORCEINLINE IPF2GameplayAbilityInterface* GetAbility() const
	{
		IPF2GameplayAbilityInterface* Ability = Cast<IPF2GameplayAbilityInterface>(this->GetAbilitySpec()->Ability);
		check(Ability);
		return Ability;
	}
};

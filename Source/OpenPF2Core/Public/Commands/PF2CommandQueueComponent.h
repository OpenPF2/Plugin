// OpenPF2 for UE Game Logic, Copyright 2022, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#pragma once

#include "CoreMinimal.h"
#include "PF2CommandQueueInterface.h"

#include "Components/ActorComponent.h"

#include "Containers/CircularQueue.h"

#include "PF2CommandQueueComponent.generated.h"

/**
 * A component for managing commands/actions that have been queued for a particular character.
 *
 * (The inspiration for this approach -- of wrapping Gameplay Abilities in a command that can be invoked at any time --
 * came from "ue4-orders-abilities" by Daedalic Entertainment,
 * https://github.com/DaedalicEntertainment/ue4-orders-abilities).
 */
UCLASS(ClassGroup="OpenPF2", meta=(BlueprintSpawnableComponent))
// ReSharper disable once CppClassCanBeFinal
class OPENPF2CORE_API UPF2CommandQueueComponent : public UActorComponent, public IPF2CommandQueueInterface
{
	GENERATED_BODY()

protected:
	TArray<IPF2CharacterCommandInterface*> Queue;

public:
	// =================================================================================================================
	// Public Constructors
	// =================================================================================================================
	/**
	 * Default constructor for UPF2CommandQueueComponent.
	 */
	UPF2CommandQueueComponent();

	// =================================================================================================================
	// Public Methods - IPF2CommandQueueInterface Implementation
	// =================================================================================================================
	UFUNCTION(BlueprintCallable)
	virtual void Enqueue(TScriptInterface<IPF2CharacterCommandInterface> Command) override;

	UFUNCTION(BlueprintCallable)
	virtual void PeekNext(TScriptInterface<IPF2CharacterCommandInterface>& NextCommand) override;

	UFUNCTION(BlueprintCallable)
	virtual void PopNext(TScriptInterface<IPF2CharacterCommandInterface>& NextCommand) override;

	UFUNCTION(BlueprintCallable)
	virtual void DropNext() override;

	UFUNCTION(BlueprintCallable)
	virtual EPF2ImmediateCommandExecutionResult PopAndExecuteNext() override;

	UFUNCTION(BlueprintCallable)
	virtual bool Remove(TScriptInterface<IPF2CharacterCommandInterface> Command) override;

	UFUNCTION(BlueprintCallable)
	virtual int Count() override;

	UFUNCTION(BlueprintCallable)
	virtual void Clear() override;

	// =================================================================================================================
	// Public Methods - IPF2LogIdentifiableInterface Implementation
	// =================================================================================================================
	UFUNCTION(BlueprintCallable)
	virtual FString GetIdForLogs() const override;
};

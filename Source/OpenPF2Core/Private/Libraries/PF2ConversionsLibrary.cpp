// OpenPF2 for UE Game Logic, Copyright 2022, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "Libraries/PF2ConversionsLibrary.h"

#include <Engine/World.h>

#include <GameFramework/PlayerController.h>

#include "PF2ActorComponentInterface.h"
#include "PF2CharacterInterface.h"
#include "PF2PlayerStateInterface.h"

#include "Abilities/PF2AbilitySystemInterface.h"

AActor* UPF2ConversionsLibrary::Conv_CharacterIntfToActor(const TScriptInterface<IPF2CharacterInterface>& Character)
{
	if (Character == nullptr)
	{
		// This is neither an assertion error nor a logged error because Blueprints might use this conversion before a
		// call to "Is valid?" or something that can accept a nullptr.
		return nullptr;
	}
	else
	{
		return Character->ToActor();
	}
}

UAbilitySystemComponent* UPF2ConversionsLibrary::Conv_AscIntfToAsc(
	const TScriptInterface<IPF2AbilitySystemInterface>& AscIntf)
{
	if (AscIntf == nullptr)
	{
		// This is neither an assertion error nor a logged error because Blueprints might use this conversion before a
		// call to "Is valid?" or something that can accept a nullptr.
		return nullptr;
	}
	else
	{
		return AscIntf->ToAbilitySystemComponent();
	}
}

APawn* UPF2ConversionsLibrary::Conv_CharacterIntfToPawn(const TScriptInterface<IPF2CharacterInterface>& Character)
{
	if (Character == nullptr)
	{
		// This is neither an assertion error nor a logged error because Blueprints might use this conversion before a
		// call to "Is valid?" or something that can accept a nullptr.
		return nullptr;
	}
	else
	{
		return Character->ToPawn();
	}
}

AController* UPF2ConversionsLibrary::Conv_PlayerControllerIntfToController(
	const TScriptInterface<IPF2PlayerControllerInterface>& PlayerController)
{
	if (PlayerController == nullptr)
	{
		// This is neither an assertion error nor a logged error because Blueprints might use this conversion before a
		// call to "Is valid?" or something that can accept a nullptr.
		return nullptr;
	}
	else
	{
		return PlayerController->ToPlayerController();
	}
}

APlayerController* UPF2ConversionsLibrary::Conv_PlayerControllerIntfToPlayerController(
	const TScriptInterface<IPF2PlayerControllerInterface>& PlayerController)
{
	if (PlayerController == nullptr)
	{
		// This is neither an assertion error nor a logged error because Blueprints might use this conversion before a
		// call to "Is valid?" or something that can accept a nullptr.
		return nullptr;
	}
	else
	{
		return PlayerController->ToPlayerController();
	}
}

APlayerState* UPF2ConversionsLibrary::Conv_PlayerStateIntfToPlayerState(
	const TScriptInterface<IPF2PlayerStateInterface>& PlayerState)
{
	if (PlayerState == nullptr)
	{
		// This is neither an assertion error nor a logged error because Blueprints might use this conversion before a
		// call to "Is valid?" or something that can accept a nullptr.
		return nullptr;
	}
	else
	{
		return PlayerState->ToPlayerState();
	}
}

UActorComponent* UPF2ConversionsLibrary::Conv_ActorComponentIntfToActorComponent(
	const TScriptInterface<IPF2ActorComponentInterface>& ActorComponent)
{
	if (ActorComponent == nullptr)
	{
		// This is neither an assertion error nor a logged error because Blueprints might use this conversion before a
		// call to "Is valid?" or something that can accept a nullptr.
		return nullptr;
	}
	else
	{
		return ActorComponent->ToActorComponent();
	}
}

// OpenPF2 for UE Game Logic, Copyright 2021, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#pragma once

#include "PF2ModeOfPlayRuleSet.h"

#include "PF2ModeOfPlayRuleSetBase.generated.h"

/**
 * Default base class for PF2 Mode of Play Rule Sets (MoPRS).
 *
 * @see IPF2GameModeInterface
 */
UCLASS(Abstract, Blueprintable)
// ReSharper disable once CppClassCanBeFinal
class OPENPF2CORE_API UPF2ModeOfPlayRuleSetBase : public UObject, public IPF2ModeOfPlayRuleSet
{
	GENERATED_BODY()

	virtual void OnQueueAction_Implementation(TScriptInterface<IPF2CharacterInterface>&    Character,
	                                          TScriptInterface<IPF2QueuedActionInterface>& Action) override;

	virtual void OnCancelQueuedAction_Implementation(TScriptInterface<IPF2CharacterInterface>&    Character,
	                                                 TScriptInterface<IPF2QueuedActionInterface>& Action) override;
};

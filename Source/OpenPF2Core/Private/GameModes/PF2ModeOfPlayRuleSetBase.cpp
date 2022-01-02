// OpenPF2 for UE Game Logic, Copyright 2021, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "GameModes/PF2ModeOfPlayRuleSetBase.h"

#include "PF2QueuedActionInterface.h"

void UPF2ModeOfPlayRuleSetBase::OnQueueAction_Implementation(TScriptInterface<IPF2CharacterInterface>& Character,
                                                             TScriptInterface<IPF2QueuedActionInterface>& Action)
{
	// By default there is no queue, so we perform the action immediately.
	Action->PerformQueuedAction();
}

void UPF2ModeOfPlayRuleSetBase::OnCancelQueuedAction_Implementation(TScriptInterface<IPF2CharacterInterface>& Character,
                                                                    TScriptInterface<IPF2QueuedActionInterface>& Action)
{
	// By default there is no queue, so we do nothing.
}

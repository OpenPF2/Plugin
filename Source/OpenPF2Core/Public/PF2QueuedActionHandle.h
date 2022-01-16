// OpenPF2 for UE Game Logic, Copyright 2021, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#pragma once

#include <Styling/SlateBrush.h>
#include <UObject/WeakInterfacePtr.h>

#include "PF2QueuedActionInterface.h"
#include "PF2QueuedActionHandle.generated.h"

USTRUCT(BlueprintType)
struct FPF2QueuedActionHandle
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	int32 HandleId;

	UPROPERTY(BlueprintReadOnly)
	FText ActionName;

	UPROPERTY(BlueprintReadOnly)
	FSlateBrush ActionIcon;

	TWeakInterfacePtr<IPF2QueuedActionInterface> Action;

	void Populate(const int32 NewHandleId, IPF2QueuedActionInterface* NewAction)
	{
		this->HandleId   = NewHandleId;
		this->ActionName = NewAction->GetActionName();
		this->ActionIcon = NewAction->GetActionIcon();
		this->Action     = NewAction;
	}
};

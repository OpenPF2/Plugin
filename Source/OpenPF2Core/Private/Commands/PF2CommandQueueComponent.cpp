// OpenPF2 for UE Game Logic, Copyright 2022, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "Commands/PF2CommandQueueComponent.h"

#include "Utilities/PF2InterfaceUtilities.h"

UPF2CommandQueueComponent::UPF2CommandQueueComponent()
{
}

void UPF2CommandQueueComponent::Enqueue(TScriptInterface<IPF2CharacterCommandInterface>& Command)
{
	IPF2CharacterCommandInterface* CommandIntf = PF2InterfaceUtilities::FromScriptInterface(Command);

	checkf(!this->Queue.Contains(CommandIntf), TEXT("The same command can only exist in the queue once."));
	this->Queue.Add(CommandIntf);
}

void UPF2CommandQueueComponent::PeekNext(TScriptInterface<IPF2CharacterCommandInterface>& NextCommand)
{
	if (this->Count() != 0)
	{
		IPF2CharacterCommandInterface* NextCommandPtr = this->Queue[0];

		NextCommand = PF2InterfaceUtilities::ToScriptInterface<IPF2CharacterCommandInterface>(NextCommandPtr);
	}
}

void UPF2CommandQueueComponent::PopNext(TScriptInterface<IPF2CharacterCommandInterface>& NextCommand)
{
	if (this->Count() != 0)
	{
		IPF2CharacterCommandInterface* NextCommandPtr = this->Queue.Pop();

		NextCommand = PF2InterfaceUtilities::ToScriptInterface<IPF2CharacterCommandInterface>(NextCommandPtr);
	}
}

bool UPF2CommandQueueComponent::Remove(TScriptInterface<IPF2CharacterCommandInterface>& Command)
{
	IPF2CharacterCommandInterface* CommandIntf    = PF2InterfaceUtilities::FromScriptInterface(Command);
	const int32                    CountOfRemoved = this->Queue.Remove(CommandIntf);

	return (CountOfRemoved > 0);
}

int UPF2CommandQueueComponent::Count()
{
	return this->Queue.Num();
}

void UPF2CommandQueueComponent::Clear()
{
	this->Queue.Empty();
}

void UPF2CommandQueueComponent::BeginPlay()
{
	Super::BeginPlay();
}

// OpenPF2 for UE Game Logic, Copyright 2022, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "Commands/PF2CommandQueueComponent.h"

#include <Net/UnrealNetwork.h>

#include <UObject/WeakInterfacePtr.h>

#include "Commands/PF2CharacterCommandInterface.h"

#include "Utilities/PF2InterfaceUtilities.h"
#include "Utilities/PF2LogUtilities.h"

const uint8 UPF2CommandQueueComponent::CommandLimitNone = 0;

UPF2CommandQueueComponent::UPF2CommandQueueComponent(): SizeLimit(CommandLimitNone)
{
	this->SetIsReplicatedByDefault(true);
}

void UPF2CommandQueueComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UPF2CommandQueueComponent, Queue);
}

void UPF2CommandQueueComponent::Enqueue(const TScriptInterface<IPF2CharacterCommandInterface> Command)
{
	AInfo* CommandActor = Command->ToActor();

	if ((this->SizeLimit != CommandLimitNone) && (this->Queue.Num() == this->SizeLimit))
	{
		UE_LOG(
			LogPf2Core,
			Verbose,
			TEXT("Command queue ('%s') is already at maximum capacity ('%d'), so command ('%s') will not be enqueued."),
			*(this->GetIdForLogs()),
			this->SizeLimit,
			*(Command->GetIdForLogs())
		);
	}
	else
	{
		checkf(!this->Queue.Contains(CommandActor), TEXT("The same command can only exist in the queue once."));
		this->Queue.Add(CommandActor);

		this->Native_OnCommandAdded(Command);
		this->Native_OnCommandsChanged();
	}
}

void UPF2CommandQueueComponent::PeekNext(TScriptInterface<IPF2CharacterCommandInterface>& NextCommand)
{
	if (this->Count() != 0)
	{
		IPF2CharacterCommandInterface* NextCommandPtr = Cast<IPF2CharacterCommandInterface>(this->Queue[0]);

		NextCommand = PF2InterfaceUtilities::ToScriptInterface(NextCommandPtr);
	}
}

void UPF2CommandQueueComponent::PopNext(TScriptInterface<IPF2CharacterCommandInterface>& NextCommand)
{
	if (this->Count() != 0)
	{
		this->PeekNext(NextCommand);

		UE_LOG(
			LogPf2Core,
			VeryVerbose,
			TEXT("Popping command ('%s') from command queue ('%s')."),
			*(NextCommand->GetIdForLogs()),
			*(this->GetIdForLogs())
		);

		this->Queue.RemoveAt(0);

		this->Native_OnCommandRemoved(NextCommand);
		this->Native_OnCommandsChanged();
	}
}

void UPF2CommandQueueComponent::DropNext()
{
	if (this->Count() != 0)
	{
		TScriptInterface<IPF2CharacterCommandInterface> NextCommand;

		this->PeekNext(NextCommand);

		UE_LOG(
			LogPf2Core,
			VeryVerbose,
			TEXT("Removing command ('%s') from command queue ('%s')."),
			*(NextCommand->GetIdForLogs()),
			*(this->GetIdForLogs())
		);

		this->Queue.RemoveAt(0);

		this->Native_OnCommandRemoved(NextCommand);
		this->Native_OnCommandsChanged();
	}
}

EPF2CommandExecuteImmediatelyResult UPF2CommandQueueComponent::PopAndExecuteNext()
{
	EPF2CommandExecuteImmediatelyResult             Result;
	TScriptInterface<IPF2CharacterCommandInterface> NextCommand;

	// We don't pop the command (yet) because it may be blocked and we don't want it to lose its place in the queue if
	// it is.
	this->PeekNext(NextCommand);

	if (NextCommand.GetInterface() == nullptr)
	{
		UE_LOG(
			LogPf2Core,
			VeryVerbose,
			TEXT("No actions are currently queued for command queue ('%s')."),
			*(this->GetIdForLogs())
		);

		Result = EPF2CommandExecuteImmediatelyResult::None;
	}
	else
	{
		IPF2CharacterCommandInterface* NextCommandIntf = PF2InterfaceUtilities::FromScriptInterface(NextCommand);

		UE_LOG(
			LogPf2Core,
			VeryVerbose,
			TEXT("Attempt to execute next command ('%s') in command queue ('%s')."),
			*(NextCommandIntf->GetIdForLogs()),
			*(this->GetIdForLogs())
		);

		Result = NextCommandIntf->AttemptExecuteImmediately();

		if (Result == EPF2CommandExecuteImmediatelyResult::Blocked)
		{
			UE_LOG(
				LogPf2Core,
				VeryVerbose,
				TEXT("Next command ('%s') in command queue ('%s') was blocked and will not be removed from the queue."),
				*(NextCommandIntf->GetIdForLogs()),
				*(this->GetIdForLogs())
			);
		}
		else
		{
			// Now it's safe to drop the command.
			this->DropNext();
		}
	}

	return Result;
}

bool UPF2CommandQueueComponent::Remove(const TScriptInterface<IPF2CharacterCommandInterface> Command)
{
	AInfo*      CommandActor       = Command->ToActor();
	const int32 CountOfRemoved     = this->Queue.Remove(CommandActor);
	const bool  bWasCommandRemoved = (CountOfRemoved > 0);

	if (bWasCommandRemoved)
	{
		this->Native_OnCommandRemoved(Command);
		this->Native_OnCommandsChanged();
	}

	return bWasCommandRemoved;
}

int UPF2CommandQueueComponent::Count()
{
	return this->Queue.Num();
}

void UPF2CommandQueueComponent::Clear()
{
	this->Queue.Empty();
	this->Native_OnCommandsChanged();
}

TArray<TScriptInterface<IPF2CharacterCommandInterface>> UPF2CommandQueueComponent::ToArray() const
{
	return PF2ArrayUtilities::Reduce<TArray<TScriptInterface<IPF2CharacterCommandInterface>>>(
		this->Queue,
		TArray<TScriptInterface<IPF2CharacterCommandInterface>>(),
		[](TArray<TScriptInterface<IPF2CharacterCommandInterface>> Commands,
		   const TWeakInterfacePtr<IPF2CharacterCommandInterface>  CurrentCommand)
		{
			if (CurrentCommand.IsValid())
			{
				Commands.Add(PF2InterfaceUtilities::ToScriptInterface(CurrentCommand.Get()));
			}

			return Commands;
		});
}

UActorComponent* UPF2CommandQueueComponent::ToActorComponent()
{
	return this;
}

FString UPF2CommandQueueComponent::GetIdForLogs() const
{
	// ReSharper disable CppRedundantParentheses
	return FString::Format(
		TEXT("{0}.{1}"),
		{
			*(GetNameSafe(this->GetOwner())),
			*(this->GetName())
		}
	);
}

void UPF2CommandQueueComponent::OnRep_Queue(const TArray<AInfo*>& OldQueue)
{
	// Skip unnecessary overhead if we have no listeners. This is only safe because our Native_ callbacks don't do
	// anything other than notify listeners.
	if (this->OnCommandAdded.IsBound() || this->OnCommandRemoved.IsBound())
	{
		TArray<IPF2CharacterCommandInterface*> RemovedCommands,
		                                       AddedCommands;

		// BUGBUG: By the time we're here, this should definitely be an OpenPF2 command, but UE will sometimes replicate
		// entries in this->Queue as NULL.
		PF2ArrayUtilities::CapturePtrDeltasWithCast(OldQueue, this->Queue, RemovedCommands, AddedCommands);

		for (IPF2CharacterCommandInterface* const& RemovedCommand : RemovedCommands)
		{
			this->Native_OnCommandRemoved(PF2InterfaceUtilities::ToScriptInterface(RemovedCommand));
		}

		for (IPF2CharacterCommandInterface* const& AddedCommand : AddedCommands)
		{
			this->Native_OnCommandAdded(PF2InterfaceUtilities::ToScriptInterface(AddedCommand));
		}
	}

	this->Native_OnCommandsChanged();
}

void UPF2CommandQueueComponent::Native_OnCommandsChanged() const
{
	// Skip unnecessary overhead if we have no listeners.
	if (this->OnCommandsChanged.IsBound())
	{
		TArray<TScriptInterface<IPF2CharacterCommandInterface>> NewCommands;

		for (AInfo* NewCommand : this->Queue)
		{
			// BUGBUG: By the time we're here, this should definitely be an OpenPF2 command, but UE will sometimes
			// replicate entries in this->Queue as NULL.
			if (NewCommand != nullptr)
			{
				NewCommands.Add(
					PF2InterfaceUtilities::ToScriptInterface<IPF2CharacterCommandInterface>(
						Cast<IPF2CharacterCommandInterface>(NewCommand)
					)
				);
			}
		}

		UE_LOG(
			LogPf2CoreAbilities,
			VeryVerbose,
			TEXT("[%s] Command queue changed ('%s') - %d elements."),
			*(PF2LogUtilities::GetHostNetId(this->GetWorld())),
			*(this->GetIdForLogs()),
			NewCommands.Num()
		);

		this->OnCommandsChanged.Broadcast(NewCommands);
	}
	else
	{
		UE_LOG(
			LogPf2CoreAbilities,
			VeryVerbose,
			TEXT("[%s] Command queue changed ('%s')."),
			*(PF2LogUtilities::GetHostNetId(this->GetWorld())),
			*(this->GetIdForLogs())
		);
	}
}

void UPF2CommandQueueComponent::Native_OnCommandAdded(
	const TScriptInterface<IPF2CharacterCommandInterface>& CommandAdded) const
{
	UE_LOG(
		LogPf2CoreAbilities,
		VeryVerbose,
		TEXT("[%s] Command ('%s') added to queue ('%s')."),
		*(PF2LogUtilities::GetHostNetId(this->GetWorld())),
		*(CommandAdded->GetIdForLogs()),
		*(this->GetIdForLogs())
	);

	this->OnCommandAdded.Broadcast(CommandAdded);
}

void UPF2CommandQueueComponent::Native_OnCommandRemoved(
	const TScriptInterface<IPF2CharacterCommandInterface>& CommandRemoved) const
{
	UE_LOG(
		LogPf2CoreAbilities,
		VeryVerbose,
		TEXT("[%s] Command ('%s') removed from queue ('%s')."),
		*(PF2LogUtilities::GetHostNetId(this->GetWorld())),
		*(CommandRemoved->GetIdForLogs()),
		*(this->GetIdForLogs())
	);

	this->OnCommandRemoved.Broadcast(CommandRemoved);
}

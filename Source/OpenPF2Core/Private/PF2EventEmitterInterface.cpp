// OpenPF2 for UE Game Logic, Copyright 2023, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "PF2EventEmitterInterface.h"

UClass* IPF2EventEmitterInterface::GetEventsClassOfCDO(const UClass* Class)
{
	if (Class == nullptr)
	{
		return nullptr;
	}
	else
	{
		return GetEventsClassOfObject(Class->GetDefaultObject());
	}
}

UClass* IPF2EventEmitterInterface::GetEventsClassOfObject(const UObject* Object)
{
	UClass*        EventsClass  = nullptr;
	const UObject* EventsObject = GetEventsOfObject(Object);

	if (IsValid(EventsObject))
	{
		EventsClass = EventsObject->GetClass();
	}

	return EventsClass;
}

UObject* IPF2EventEmitterInterface::GetEventsOfCDO(const UClass* Class)
{
	if (Class == nullptr)
	{
		return nullptr;
	}
	else
	{
		return GetEventsOfObject(Class->GetDefaultObject());
	}
}

UObject* IPF2EventEmitterInterface::GetEventsOfObject(const UObject* Object)
{
	UObject* EventsObject = nullptr;

	if (IsValid(Object))
	{
		const IPF2EventEmitterInterface* EventEmitterIntf = Cast<IPF2EventEmitterInterface>(Object);

		if (EventEmitterIntf != nullptr)
		{
			EventsObject = EventEmitterIntf->GetGenericEventsObject();
		}
	}

	return EventsObject;
}

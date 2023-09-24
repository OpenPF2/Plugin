// OpenPF2 for UE Game Logic, Copyright 2023, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "PF2DamageCauseWrapper.h"

#include <Kismet/GameplayStatics.h>

#include <Net/UnrealNetwork.h>

APF2DamageCauseWrapper* APF2DamageCauseWrapper::Create(UWorld* World, IPF2WeaponInterface* Weapon)
{
	APF2DamageCauseWrapper* NewInstance = World->SpawnActorDeferred<APF2DamageCauseWrapper>(StaticClass(), FTransform());

	NewInstance->FinalizeConstruction(Weapon);

	return NewInstance;
}

void APF2DamageCauseWrapper::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APF2DamageCauseWrapper, Weapon);
}

void APF2DamageCauseWrapper::FinalizeConstruction(IPF2WeaponInterface* const InWeapon)
{
	this->Weapon = InWeapon->ToDataAsset();

	UGameplayStatics::FinishSpawningActor(this, FTransform());
}

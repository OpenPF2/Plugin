// OpenPF2 for UE Game Logic, Copyright 2021, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "Tests/PF2TestPawn.h"
#include <AbilitySystemComponent.h>
#include "Abilities/PF2AttributeSet.h"

FName  APF2TestPawn::AbilitySystemComponentName(TEXT("AbilitySystemComponent0"));

APF2TestPawn::APF2TestPawn(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(APF2TestPawn::AbilitySystemComponentName);
	AbilitySystemComponent->SetIsReplicated(true);
}

void APF2TestPawn::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	AbilitySystemComponent->InitStats(UPF2AttributeSet::StaticClass(), nullptr);
}

UAbilitySystemComponent* APF2TestPawn::GetAbilitySystemComponent() const
{
	return FindComponentByClass<UAbilitySystemComponent>();
}

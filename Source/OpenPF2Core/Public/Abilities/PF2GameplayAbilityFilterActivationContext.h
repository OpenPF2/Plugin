// OpenPF2 for UE Game Logic, Copyright 2022, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#pragma once

#include <GameplayAbilitySpec.h>

#include "PF2GameplayAbilityFilterActivationContext.generated.h"

UCLASS(Abstract)
class OPENPF2CORE_API UPF2GameplayAbilityFilterActivationContext final : public UObject
{
	GENERATED_BODY()

protected:
	UPROPERTY(Replicated)
	FName InputName;

	UPROPERTY(Replicated)
	FGameplayAbilitySpecHandle ActivatedAbilityHandle;

public:
	UPF2GameplayAbilityFilterActivationContext() : InputName(FName("none"))
	{
	}

	UPF2GameplayAbilityFilterActivationContext(const FName                      InputName,
	                                           const FGameplayAbilitySpecHandle ActivatedAbilityHandle) :
		InputName(InputName),
		ActivatedAbilityHandle(ActivatedAbilityHandle)
	{
	}

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	FORCEINLINE FName GetInputName() const
	{
		return this->InputName;
	}

	FORCEINLINE FGameplayAbilitySpecHandle GetActivatedAbilityHandle() const
	{
		return this->ActivatedAbilityHandle;
	}
};

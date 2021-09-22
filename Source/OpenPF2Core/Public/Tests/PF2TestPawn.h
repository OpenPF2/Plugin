// OpenPF2 for UE Game Logic, Copyright 2021, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#pragma once

#include "CoreMinimal.h"
#include "GameplayCueInterface.h"
#include "GameFramework/DefaultPawn.h"
#include "AbilitySystemInterface.h"
#include "PF2TestPawn.generated.h"

class UAbilitySystemComponent;

UCLASS(Blueprintable, BlueprintType, notplaceable)
class OPENPF2CORE_API APF2TestPawn : public ADefaultPawn, public IGameplayCueInterface, public IAbilitySystemInterface
{
	GENERATED_UCLASS_BODY()

	virtual void PostInitializeComponents() override;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

private:
	/** The ability system component of this pawn (manipulated by tests). */
	UPROPERTY(Category = AbilitySystem, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UAbilitySystemComponent* AbilitySystemComponent;

public:
	static FName AbilitySystemComponentName;

	/** Gets the ASC in this pawn. **/
	class UAbilitySystemComponent* GetAbilitySystemComponent()
	{
		return AbilitySystemComponent;
	}
};

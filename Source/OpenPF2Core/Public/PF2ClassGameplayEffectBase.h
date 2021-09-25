#pragma once

#include "GameplayEffect.h"
#include "PF2ClassGameplayEffectBase.generated.h"

/**
 * Parent class for Gameplay Effects that represent how a character's class impacts them.
 */
UCLASS(Abstract)
class UPF2ClassGameplayEffectBase : public UGameplayEffect
{
	GENERATED_BODY()
};

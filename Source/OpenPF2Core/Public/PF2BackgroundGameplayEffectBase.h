#pragma once

#include "GameplayEffect.h"
#include "PF2BackgroundGameplayEffectBase.generated.h"

/**
 * Parent class for Gameplay Effects that represent how a character's background impacts them.
 */
UCLASS(Abstract)
class UPF2BackgroundGameplayEffectBase : public UGameplayEffect
{
	GENERATED_BODY()
};

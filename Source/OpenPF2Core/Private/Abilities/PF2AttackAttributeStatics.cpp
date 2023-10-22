// OpenPF2 for UE Game Logic, Copyright 2023, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "Abilities/PF2AttackAttributeStatics.h"

#include "Utilities/PF2ArrayUtilities.h"

TArray<const FGameplayEffectAttributeCaptureDefinition*> FPF2AttackAttributeStatics::GetAllDamageCaptures() const
{
	return PF2ArrayUtilities::Filter(
		this->GetCaptureDefinitions(),
		[](const FGameplayEffectAttributeCaptureDefinition* CaptureDefinition)
		{
			return CaptureDefinition->AttributeToCapture.GetName().StartsWith("TmpDmgType");
		});
}

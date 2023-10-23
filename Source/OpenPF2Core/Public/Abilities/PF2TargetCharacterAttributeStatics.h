// OpenPF2 for UE Game Logic, Copyright 2023, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#pragma once

#include "Abilities/PF2CharacterAttributeStaticsBase.h"

/**
 * Singleton container for OpenPF2 character attribute capture definitions for target actors.
 */
struct OPENPF2CORE_API FPF2TargetCharacterAttributeStatics final : FPF2CharacterAttributeStaticsBase
{
	// =================================================================================================================
	// Public Static Methods
	// =================================================================================================================
	/**
	 * Gets an instance of this container.
	 *
	 * @return
	 *	A reference to the capture definition container.
	 */
	FORCEINLINE static const FPF2TargetCharacterAttributeStatics& GetInstance()
	{
		static FPF2TargetCharacterAttributeStatics AttributeStatics;

		return AttributeStatics;
	}

	// =================================================================================================================
	// Attribute Capture Definitions
	// =================================================================================================================
	DECLARE_ATTRIBUTE_CAPTUREDEF(TmpDamageIncoming);
	DECLARE_ATTRIBUTE_CAPTUREDEF(TmpIncomingAttackDegreeOfSuccess);

private:
	// =================================================================================================================
	// Private Constructors
	// =================================================================================================================
	/**
	 * Constructor for FPF2TargetCharacterAttributeStatics.
	 */
	explicit FPF2TargetCharacterAttributeStatics();
};

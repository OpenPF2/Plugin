// OpenPF2 Game Framework for Unreal Engine, Copyright 2021-2024, Guy Elsmore-Paddock. All Rights Reserved.
// 
// Content from Pathfinder 2nd Edition is licensed under the Open Game License (OGL) v1.0a, subject to the following:
//	- Open Game License v 1.0a, Copyright 2000, Wizards of the Coast, Inc.
//	- System Reference Document, Copyright 2000, Wizards of the Coast, Inc.
//	- Pathfinder Core Rulebook (Second Edition), Copyright 2019, Paizo Inc.
// 
// Except for material designated as Product Identity, the game mechanics and logic in this file are Open Game Content,
// as defined in the Open Game License version 1.0a, Section 1(d) (see accompanying LICENSE.TXT). No portion of this
// file other than the material designated as Open Game Content may be reproduced in any form without written
// permission.

#include "GameplayTags/Currencies.h"

// =====================================================================================================================
// Default Currency - "Coins"
// =====================================================================================================================
// Source: Pathfinder 2E Core Rulebook, Chapter 6, page 271.
UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagCurrencies,
	"PF2.Currency",
	"Types of money used to pay for goods in lieu of bartering."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagCurrencyCoins,
	"PF2.Currency.Coins",
	"The most common currency in OpenPF2."
)

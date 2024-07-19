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

#include "GameplayTags/CurrencyUnits.h"

// =====================================================================================================================
// Default Currency Units
// =====================================================================================================================
// Source: Pathfinder 2E Core Rulebook, Chapter 6, page 271.
UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagCurrencyUnits,
	"PF2.CurrencyUnit",
	"Standard units of payment for goods."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagCurrencyUnitCoins,
	"PF2.CurrencyUnit.Coin",
	"Standard coin increments when paying for goods."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagCurrencyUnitCoinCopperPiece,
	"PF2.CurrencyUnit.Coin.CopperPiece",
	"A unit of currency worth 1/10 of a silver piece."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagCurrencyUnitCoinSilverPiece,
	"PF2.CurrencyUnit.Coin.SilverPiece",
	"The standard unit of currency for commoners and beginning adventurers. Each is a standard weight of silver and is typically accepted by any merchant or kingdom no matter where it was minted."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagCurrencyUnitCoinGoldPiece,
	"PF2.CurrencyUnit.Coin.GoldPiece",
	"A unit of currency often used for purchasing magic items and other expensive items. 1 gold piece is worth 10 silver pieces and 100 copper pieces."
)

UE_DEFINE_GAMEPLAY_TAG_COMMENT(
	Pf2TagCurrencyUnitCoinPlatinumPiece,
	"PF2.CurrencyUnit.Coin.PlatinumPiece",
	"A unit of current used by nobles to demonstrate their wealth, for the purchase of very expensive items, or simply as a way to easily transport large sums of currency. A platinum piece is worth 10 gold pieces, 100 silver pieces, and 1,000 copper pieces."
)

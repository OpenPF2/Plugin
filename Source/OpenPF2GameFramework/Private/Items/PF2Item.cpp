// OpenPF2 Game Framework for Unreal Engine, Copyright 2023-2024, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "Items/PF2Item.h"

FPrimaryAssetId UPF2Item::GetPrimaryAssetId()
{
	return UPrimaryDataAsset::GetPrimaryAssetId();
}

UDataAsset* UPF2Item::ToDataAsset()
{
	return this;
}

bool UPF2Item::ShouldBeEquippedInAllLinkedSlots()
{
	return this->bShouldBeEquippedInAllLinkedSlots;
}

FString UPF2Item::GetIdForLogs() const
{
	return this->GetFullName();
}

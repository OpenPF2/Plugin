// OpenPF2 Game Framework for Unreal Engine, Copyright 2026, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#pragma once

#include <Commandlets/Commandlet.h>

#include "PF2MigrateGameplayTagsCommandlet.generated.h"

/**
 * Migrates tracked content to native gameplay tags and records values for a redirect-free reload audit.
 *
 * Supply Manifest and Report paths. Resave compiles and saves Blueprints; Baseline compares a previous report.
 */
UCLASS()
class UPF2MigrateGameplayTagsCommandlet final : public UCommandlet
{
	GENERATED_BODY()

public:
	UPF2MigrateGameplayTagsCommandlet();
	virtual int32 Main(const FString& Params) override;
};

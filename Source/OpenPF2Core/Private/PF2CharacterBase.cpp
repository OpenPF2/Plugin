// OpenPF2 for UE Game Logic, Copyright 2021-2022, Guy Elsmore-Paddock. All Rights Reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

#include "PF2CharacterBase.h"

#include <AbilitySystemGlobals.h>
#include <Net/UnrealNetwork.h>
#include <UObject/ConstructorHelpers.h>

#include "PF2OwnerTrackingComponent.h"
#include "PF2PlayerStateInterface.h"

#include "Abilities/PF2GameplayAbilityTargetData_BoostAbility.h"
#include "Commands/PF2CommandQueueComponent.h"
#include "Utilities/PF2InterfaceUtilities.h"
#include "Utilities/PF2LogUtilities.h"

APF2CharacterBase::APF2CharacterBase() :
	APF2CharacterBase(TPF2CharacterComponentFactory<UPF2AbilitySystemComponent,
	                                                UPF2CommandQueueComponent,
	                                                UPF2OwnerTrackingComponent,
	                                                UPF2AttributeSet>())
{
}

void APF2CharacterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (this->AbilitySystemComponent != nullptr)
	{
		this->AbilitySystemComponent->InitAbilityActorInfo(this, this);

		this->ActivatePassiveGameplayEffects();
		this->ApplyAbilityBoostSelections();
		this->GrantAdditionalAbilities();
	}
}

void APF2CharacterBase::OnRep_Controller()
{
	Super::OnRep_Controller();

	if (this->AbilitySystemComponent != nullptr)
	{
		this->AbilitySystemComponent->RefreshAbilityActorInfo();
	}
}

void APF2CharacterBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APF2CharacterBase, CharacterLevel);
}

FString APF2CharacterBase::GetIdForLogs() const
{
	// ReSharper disable twice CppRedundantParentheses
	return FString::Format(TEXT("{0}[{1}]"), { *(this->GetCharacterName().ToString()), *(this->GetName()) });
}

UAbilitySystemComponent* APF2CharacterBase::GetAbilitySystemComponent() const
{
	check(this->AbilitySystemComponent);
	return this->AbilitySystemComponent;
}

FText APF2CharacterBase::GetCharacterName() const
{
	FText Name = this->CharacterName;

	if (Name.IsEmpty())
	{
		Name = FText::FromString(this->GetName());
	}

	return Name;
}

UTexture2D* APF2CharacterBase::GetCharacterPortrait() const
{
	return this->CharacterPortrait;
}

int32 APF2CharacterBase::GetCharacterLevel() const
{
	return this->CharacterLevel;
}

FORCEINLINE void APF2CharacterBase::GetCharacterAbilitySystemComponent(
	TScriptInterface<IPF2CharacterAbilitySystemInterface>& Output) const
{
	// BUGBUG: This is weird, but the way that a TScriptInterface object works is it maintains a reference to a UObject
	// that *implements* an interface along with a pointer to the part of the UObject that provides the interface
	// implementation, so we need to provide the concrete object instead of the interface type.
	Output = this->AbilitySystemComponent;
}

FORCEINLINE IPF2CharacterAbilitySystemInterface* APF2CharacterBase::GetCharacterAbilitySystemComponent() const
{
	// Too bad that ASCs in UE don't implement an interface; otherwise we could extend it so casts like this aren't
	// needed.
	IPF2CharacterAbilitySystemInterface* CharacterAsc =
		Cast<IPF2CharacterAbilitySystemInterface>(this->AbilitySystemComponent);

	check(CharacterAsc);
	return CharacterAsc;
}

TScriptInterface<IPF2CommandQueueInterface> APF2CharacterBase::GetCommandQueueComponent() const
{
	return this->CommandQueue;
}

TScriptInterface<IPF2OwnerTrackingInterface> APF2CharacterBase::GetOwnerTrackingComponent() const
{
	return this->OwnerTracker;
}

TScriptInterface<IPF2PlayerControllerInterface> APF2CharacterBase::GetPlayerController() const
{
	TScriptInterface<IPF2PlayerControllerInterface> PlayerController = this->GetController();

	// Using the PC is usually the fastest/easiest option, but only works if the character is possessed, as is the case
	// for a party character in exploration mode. For any other situation, we have to use the owner tracking component
	// (if there is one) to identify the PC for this character. If this doesn't work, then this character isn't
	// controllable by any PCs right now but might be controllable by AI (e.g. by the story or campaign).
	if (PlayerController == nullptr)
	{
		const TScriptInterface<IPF2OwnerTrackingInterface> OwnerTrackingComponent = this->GetOwnerTrackingComponent();

		UE_LOG(
			LogPf2Core,
			VeryVerbose,
			TEXT("[%s] Attempting to identify owner of character ('%s') using owner tracking component."),
			*(PF2LogUtilities::GetHostNetId(this->GetWorld())),
			*(this->GetIdForLogs())
		);

		if (OwnerTrackingComponent != nullptr)
		{
			const TScriptInterface<IPF2PlayerStateInterface> OwnerPlayerState =
				OwnerTrackingComponent->GetStateOfOwningPlayer();

			if (OwnerPlayerState != nullptr)
			{
				PlayerController = OwnerPlayerState->GetPlayerController();
			}
		}
	}

	if (PlayerController == nullptr)
	{
		UE_LOG(
			LogPf2Core,
			Warning,
			TEXT("[%s] Either this character ('%s') is only controllable by a remote client, or the character does not have an OpenPF2-compatible player controller."),
			*(PF2LogUtilities::GetHostNetId(this->GetWorld())),
			*(this->GetIdForLogs())
		);
	}

	return PlayerController;
}

TArray<TScriptInterface<IPF2AbilityBoostInterface>> APF2CharacterBase::GetPendingAbilityBoosts() const
{
	return this->GetCharacterAbilitySystemComponent()->GetPendingAbilityBoosts();
}

AActor* APF2CharacterBase::ToActor()
{
	return this;
}

APawn* APF2CharacterBase::ToPawn()
{
	return this;
}

bool APF2CharacterBase::IsAlive()
{
	return (this->AttributeSet->GetHitPoints() > 0);
}

void APF2CharacterBase::AddAbilityBoostSelection(
	const TSubclassOf<UPF2AbilityBoostBase>   BoostGameplayAbility,
	const TSet<EPF2CharacterAbilityScoreType> SelectedAbilities)
{
	this->AbilityBoostSelections.Add(FPF2CharacterAbilityBoostSelection(BoostGameplayAbility, SelectedAbilities));
}

void APF2CharacterBase::ApplyAbilityBoostSelections()
{
	if (this->IsAuthorityForEffects())
	{
		TArray<FPF2CharacterAbilityBoostSelection> UnmatchedAbilityBoostSelections;

		for (const auto& AbilityBoostSelection : this->AbilityBoostSelections)
		{
			TSubclassOf<UPF2AbilityBoostBase> BoostGa   = AbilityBoostSelection.BoostGameplayAbility;
			UAbilitySystemComponent*          Asc       = this->GetAbilitySystemComponent();
			FGameplayAbilitySpec*             BoostSpec = Asc->FindAbilitySpecFromClass(BoostGa);

			if (BoostSpec == nullptr)
			{
				UnmatchedAbilityBoostSelections.Add(AbilityBoostSelection);
			}
			else
			{
				this->ActivateAbilityBoost(BoostSpec, AbilityBoostSelection);

				this->AppliedAbilityBoostSelections.Add(AbilityBoostSelection);
			}
		}

		// In case we couldn't match some, put them back into the property. This is safer than trying to modify the
		// property in place while we iterate.
		this->AbilityBoostSelections = UnmatchedAbilityBoostSelections;
	}
}

void APF2CharacterBase::ActivatePassiveGameplayEffects()
{
	IPF2CharacterAbilitySystemInterface* CharacterAsc = this->GetCharacterAbilitySystemComponent();

	if (this->IsAuthorityForEffects() && !CharacterAsc->ArePassiveGameplayEffectsActive())
	{
		this->PopulatePassiveGameplayEffects();
		this->ApplyDynamicTags();

		CharacterAsc->ActivateAllPassiveGameplayEffects();

		// Ensure we do not re-prompt for boosts that have already chosen and applied to this character.
		this->RemoveRedundantPendingAbilityBoosts();
	}
}

void APF2CharacterBase::DeactivatePassiveGameplayEffects()
{
	if (this->IsAuthorityForEffects())
	{
		this->GetCharacterAbilitySystemComponent()->DeactivateAllPassiveGameplayEffects();
	}
}

void APF2CharacterBase::AddAndActivateGameplayAbility(const TSubclassOf<UGameplayAbility> Ability)
{
	UAbilitySystemComponent* Asc          = this->GetAbilitySystemComponent();
	const int32              AbilityLevel = this->GetCharacterLevel();
	FGameplayAbilitySpec     Spec         = FGameplayAbilitySpec(Ability, AbilityLevel, INDEX_NONE, this);

	Asc->GiveAbilityAndActivateOnce(Spec);
}

void APF2CharacterBase::Native_OnDamageReceived(const float                  Damage,
                                                IPF2CharacterInterface*      InstigatorCharacter,
                                                AActor*                      DamageSource,
                                                const FGameplayTagContainer* EventTags,
                                                const FHitResult             HitInfo)
{
	this->BP_OnDamageReceived(
		Damage,
		PF2InterfaceUtilities::ToScriptInterface(InstigatorCharacter),
		DamageSource,
		*EventTags,
		HitInfo
	);
}

void APF2CharacterBase::Native_OnHitPointsChanged(const float Delta, const FGameplayTagContainer* EventTags)
{
	if ((this->AbilitySystemComponent == nullptr) ||
		!this->GetCharacterAbilitySystemComponent()->ArePassiveGameplayEffectsActive())
	{
		// Stats are not presently initialized, so bail out to avoid firing off during initialization.
		return;
	}

	this->BP_OnHitPointsChanged(Delta, *EventTags);
}

void APF2CharacterBase::Multicast_OnEncounterTurnStarted_Implementation()
{
	this->OnEncounterTurnStarted.Broadcast(this);
}

void APF2CharacterBase::Multicast_OnEncounterTurnEnded_Implementation()
{
	this->OnEncounterTurnEnded.Broadcast(this);
}

bool APF2CharacterBase::SetCharacterLevel(const int32 NewLevel)
{
	const int32 OldLevel = this->CharacterLevel;

	if ((OldLevel != NewLevel) && (NewLevel > 0))
	{
		this->Native_OnCharacterLevelChanged(OldLevel, NewLevel);
		return true;
	}
	else
	{
		return false;
	}
}

void APF2CharacterBase::ApplyAbilityBoost(const EPF2CharacterAbilityScoreType TargetAbilityScore)
{
	this->GetCharacterAbilitySystemComponent()->ApplyAbilityBoost(TargetAbilityScore);
}

void APF2CharacterBase::RemoveRedundantPendingAbilityBoosts()
{
	if (this->IsAuthorityForEffects())
	{
		for (const auto& AbilityBoostSelection : this->AppliedAbilityBoostSelections)
		{
			TSubclassOf<UPF2AbilityBoostBase> BoostGa   = AbilityBoostSelection.BoostGameplayAbility;
			UAbilitySystemComponent*          Asc       = this->GetAbilitySystemComponent();
			const FGameplayAbilitySpec*       BoostSpec = Asc->FindAbilitySpecFromClass(BoostGa);

			if (BoostSpec != nullptr)
			{
				// The player or a game designer already made a selection for this boost ability.
				Asc->ClearAbility(BoostSpec->Handle);
			}
		}
	}
}

bool APF2CharacterBase::IsAuthorityForEffects() const
{
	return (this->GetLocalRole() == ROLE_Authority);
}

void APF2CharacterBase::ActivateAbilityBoost(
	FGameplayAbilitySpec*                     BoostSpec,
	const FPF2CharacterAbilityBoostSelection& AbilityBoostSelection) const
{
	UAbilitySystemComponent*                    Asc               = this->GetAbilitySystemComponent();
	const TSet<EPF2CharacterAbilityScoreType>   SelectedAbilities = AbilityBoostSelection.SelectedAbilities;
	FPF2GameplayAbilityTargetData_BoostAbility* BoostTargetData   = new FPF2GameplayAbilityTargetData_BoostAbility();
	FGameplayAbilityTargetDataHandle            TargetDataHandle;
	FGameplayEventData                          BoostEventInfo;

	BoostSpec->RemoveAfterActivation   = true;
	BoostTargetData->SelectedAbilities = SelectedAbilities;

	TargetDataHandle.Add(BoostTargetData);

	BoostEventInfo.TargetData = TargetDataHandle;

	// Fire it up!
	Asc->TriggerAbilityFromGameplayEvent(
		BoostSpec->Handle,
		Asc->AbilityActorInfo.Get(),
		UPF2AbilityBoostBase::GetTriggerTag(),
		&BoostEventInfo,
		*Asc
	);
}

void APF2CharacterBase::PopulatePassiveGameplayEffects()
{
	TMultiMap<FName, TSubclassOf<UGameplayEffect>> GameplayEffects;

	this->GenerateManagedPassiveGameplayEffects();

	GameplayEffects.Append(this->CoreGameplayEffects);
	GameplayEffects.Append(this->ManagedGameplayEffects);

	for (const auto& AdditionalEffect : this->AdditionalPassiveGameplayEffects)
	{
		// Allow GE to override the default weight group.
		const FName WeightGroup =
			PF2GameplayAbilityUtilities::GetWeightGroupOfGameplayEffect(
				AdditionalEffect,
				PF2CharacterConstants::GeWeightGroups::PreAbilityBoosts
			);

		GameplayEffects.Add(WeightGroup, AdditionalEffect);
	}

	this->GetCharacterAbilitySystemComponent()->SetPassiveGameplayEffects(GameplayEffects);
}

void APF2CharacterBase::ApplyDynamicTags() const
{
	FGameplayTagContainer DynamicTags;

	DynamicTags.AddTag(this->Alignment);
	DynamicTags.AppendTags(this->AdditionalLanguages);
	DynamicTags.AppendTags(this->AdditionalSkillProficiencies);

	this->GetCharacterAbilitySystemComponent()->AppendDynamicTags(DynamicTags);
}

void APF2CharacterBase::GenerateManagedPassiveGameplayEffects()
{
	if (this->IsAuthorityForEffects() && !this->bManagedPassiveEffectsGenerated)
	{
		TArray<TSubclassOf<UGameplayEffect>> EffectBlueprints = {
			this->AncestryAndHeritage,
			this->Background,
		};

		for (const auto& EffectBlueprint : EffectBlueprints)
		{
			if (*EffectBlueprint != nullptr)
			{
				// Allow managed GE to override the default weight group.
				const FName WeightGroup =
					PF2GameplayAbilityUtilities::GetWeightGroupOfGameplayEffect(
						EffectBlueprint,
						PF2CharacterConstants::GeWeightGroups::ManagedEffects
					);

				this->ManagedGameplayEffects.Add(WeightGroup, EffectBlueprint);
			}
		}

		this->bManagedPassiveEffectsGenerated = true;
	}
}

void APF2CharacterBase::ClearManagedPassiveGameplayEffects()
{
	this->ManagedGameplayEffects.Empty();

	this->bManagedPassiveEffectsGenerated = false;
}

void APF2CharacterBase::GrantAdditionalAbilities()
{
	if ((this->GrantedAdditionalAbilities.Num() == 0) && this->IsAuthorityForEffects())
	{
		UAbilitySystemComponent* Asc          = this->GetAbilitySystemComponent();
		const int32              AbilityLevel = this->GetCharacterLevel();

		for (const TSubclassOf<UGameplayAbility>& Ability : this->AdditionalGameplayAbilities)
		{
			FGameplayAbilitySpec       Spec       = FGameplayAbilitySpec(Ability, AbilityLevel, INDEX_NONE, this);
			FGameplayAbilitySpecHandle SpecHandle = Asc->GiveAbility(Spec);

			this->GrantedAdditionalAbilities.Add(Ability, SpecHandle);
		}
	}
}

void APF2CharacterBase::Native_OnCharacterLevelChanged(const float OldLevel, const float NewLevel)
{
	this->DeactivatePassiveGameplayEffects();

	this->CharacterLevel = NewLevel;
	this->BP_OnCharacterLevelChanged(OldLevel, NewLevel);

	this->ActivatePassiveGameplayEffects();
}

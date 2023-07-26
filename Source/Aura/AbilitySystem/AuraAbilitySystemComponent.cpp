// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AuraAbilitySystemComponent.h"

void UAuraAbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.RemoveAll(this);
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UAuraAbilitySystemComponent::EffectApplied);
}

void UAuraAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* ASC, const FGameplayEffectSpec& ES, FActiveGameplayEffectHandle AGEH)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString("Effect Applied!"));

	FGameplayTagContainer TagContainer;
	ES.GetAllAssetTags((OUT TagContainer));

	/*for (const FGameplayTag& Tag : TagContainer)
	{
		const FString Msg = FString::Printf(TEXT("GE TAG : %s"), *Tag.ToString());
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, Msg);
	}*/
	EffectAssetTags.Broadcast(TagContainer);
}

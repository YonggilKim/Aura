// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Chracter/AuraChracterBase.h"
#include "AuraPlayer.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AAuraPlayer : public AAuraChracterBase
{
	GENERATED_BODY()
public:
	AAuraPlayer();
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
	virtual int32 GetPlayerLevel() override;

private:
	virtual void InitAbilityActorInfo() override;
protected:
	UPROPERTY(EditAnyWhere, Category = "Camera")
	TObjectPtr<class USpringArmComponent> CameraBoom;


	UPROPERTY(EditAnyWhere, Category = "Camera")
	TObjectPtr<class UCameraComponent> FollowCamera;
};

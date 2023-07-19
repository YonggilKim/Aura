// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AuraPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
class IEnermyInterface;
/**
 * 
 */
UCLASS()
class AURA_API AAuraPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AAuraPlayerController();

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	virtual void PlayerTick(float DeltaTime) override;

	void Move(const struct FInputActionValue& Value);

private:
	void TickCursorTrace();

private:
	UPROPERTY(EditAnyWhere, Category="input")
	TObjectPtr<UInputMappingContext> AuraContext;

	UPROPERTY(EditAnyWhere, Category = "input")
	TObjectPtr<UInputAction> MoveAction;

	IEnermyInterface* TargetActor;
};

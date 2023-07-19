// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/AuraPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "../Interface/EnermyInterface.h"

AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(AuraContext);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (Subsystem)
		Subsystem->AddMappingContext(AuraContext, 0);

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	TickCursorTrace();
}

void AAuraPlayerController::Move(const FInputActionValue& Value)
{
	const FVector2D InputAxisVector = Value.Get<FVector2D>();

	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if (APawn* ControlledPawn = GetPawn())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);

	}
}

void AAuraPlayerController::TickCursorTrace()
{
	FHitResult CursorHit;
	if (GetHitResultUnderCursor(ECC_Visibility, false, OUT CursorHit) == false)
		return;
	IEnermyInterface* LocalTargetActor = Cast<IEnermyInterface>(CursorHit.GetActor());

	if (LocalTargetActor == nullptr)
	{
		//원래 있었는데 없어짐
		if (TargetActor)
			TargetActor->UnHighlightActor();
	}
	else
	{
		if (TargetActor)
		{
			//원래 있었는데 다른애였음
			if (TargetActor != LocalTargetActor)
			{
				TargetActor->UnHighlightActor();
				LocalTargetActor->HighlightActor();
			}
			//동일한애면 무시
		}
		else
		{
			// 원래 없엇고 새로 타겟
			LocalTargetActor->HighlightActor();
		}
	}

	TargetActor = LocalTargetActor;
}

// Copyright Epic Games, Inc. All Rights Reserved.

#include "BullethellPlayerController.h"
#include "GameFramework/Pawn.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "BullethellCharacter.h"
#include "Engine/World.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "Kismet/KismetMathLibrary.h"
#include "BullethellCharacter.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

ABullethellPlayerController::ABullethellPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
}

void ABullethellPlayerController::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
}

void ABullethellPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	// Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{

	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void ABullethellPlayerController::Move(FVector2D inputs)
{
	APawn* ControlledPawn = GetPawn();
	if (ControlledPawn == nullptr)
		return;

	FRotator PawnRotation = ControlledPawn->GetControlRotation();
	ControlRotation.Pitch = 0.f;
	FVector RightVector = UKismetMathLibrary::GetRightVector(ControlRotation);
	ControlledPawn->AddMovementInput(RightVector, inputs.X);

	ControlRotation.Pitch = 0.f;
	FVector ForwardVector = UKismetMathLibrary::GetForwardVector(ControlRotation);
	ControlledPawn->AddMovementInput(ForwardVector, inputs.Y);
}

void ABullethellPlayerController::RotateTowardsCursor()
{
	APawn* ControlledPawn = GetPawn();
	if (ControlledPawn == nullptr)
		return;

	float MouseX, MouseY;
	GetMousePosition(MouseX, MouseY);

	FVector WorldLocation, WorldDirection;
	DeprojectScreenPositionToWorld(MouseX, MouseY, WorldLocation, WorldDirection);

	FVector CharacterLocation = ControlledPawn->GetActorLocation();
	FVector PlanePoint = CharacterLocation;
	FVector PlaneNormal = FVector::UpVector;
	CursorWorldPosition = FMath::LinePlaneIntersection(WorldLocation, WorldLocation + WorldDirection * 10000.0f, PlanePoint, PlaneNormal);
	FVector Direction = (CursorWorldPosition - CharacterLocation).GetSafeNormal();
	FRotator NewRotation = FRotationMatrix::MakeFromX(Direction).Rotator();

	ControlledPawn->SetActorRotation(NewRotation);
}

void ABullethellPlayerController::FireLight()
{
	APawn* ControlledPawn = GetPawn();
	if (ControlledPawn == nullptr)
		return;

	ABullethellCharacter* PlayerCharacter = Cast<ABullethellCharacter>(ControlledPawn);
	if (PlayerCharacter == nullptr)
		return;

	PlayerCharacter->TryFireLight();
}

void ABullethellPlayerController::FireHeavyStarted()
{
	APawn* ControlledPawn = GetPawn();
	if (ControlledPawn == nullptr)
		return;

	ABullethellCharacter* PlayerCharacter = Cast<ABullethellCharacter>(ControlledPawn);
	if (PlayerCharacter == nullptr)
		return;

	PlayerCharacter->StartChargeHeavy();
}

void ABullethellPlayerController::FireHeavyEnded()
{
	APawn* ControlledPawn = GetPawn();
	if (ControlledPawn == nullptr)
		return;

	ABullethellCharacter* PlayerCharacter = Cast<ABullethellCharacter>(ControlledPawn);
	if (PlayerCharacter == nullptr)
		return;

	PlayerCharacter->EndChargeHeavy();
}

FVector ABullethellPlayerController::GetCursorWorldPosition()
{
	return CursorWorldPosition;
}



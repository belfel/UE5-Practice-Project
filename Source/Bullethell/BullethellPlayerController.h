// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"
#include "GameFramework/PlayerController.h"
#include "BullethellPlayerController.generated.h"

/** Forward declaration to improve compiling times */
class UNiagaraSystem;
class UInputMappingContext;
class UInputAction;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS()
class ABullethellPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ABullethellPlayerController();

	/** Time Threshold to know if it was a short press */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	float ShortPressThreshold;

	/** FX Class that we will spawn when clicking */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UNiagaraSystem* FXCursor;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	UFUNCTION(BlueprintCallable, Category = "Movement")
	void Move(FVector2D inputs);

	UFUNCTION(BlueprintCallable, Category = "Movement")
	void RotateTowardsCursor();

	UFUNCTION(BlueprintCallable, Category = "Attack")
	void FireLight();

	UFUNCTION(BlueprintCallable, Category = "Attack")
	void FireHeavyStarted();

	UFUNCTION(BlueprintCallable, Category = "Attack")
	void FireHeavyEnded();

	UFUNCTION(BlueprintCallable)
	FVector GetCursorWorldPosition();

protected:
	virtual void SetupInputComponent() override;
	
	// To add mapping context
	virtual void BeginPlay();

private:

	UPROPERTY(VisibleAnywhere)
	FVector CursorWorldPosition;
};



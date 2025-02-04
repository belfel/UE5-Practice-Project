// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BullethellCharacter.generated.h"

UCLASS(Blueprintable)
class ABullethellCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ABullethellCharacter();

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	UFUNCTION(BlueprintCallable, Category = "Attack")
	void TryFireLight();

	UFUNCTION(BlueprintCallable, Category = "Attack")
	void StartChargeHeavy();

	UFUNCTION(BlueprintCallable, Category = "Attack")
	void EndChargeHeavy();

	UFUNCTION(BlueprintImplementableEvent, Category = "Attack")
	void OnFireLight();

	UFUNCTION(BlueprintImplementableEvent, Category = "Attack")
	void OnStartedChargeHeavy();

	UFUNCTION(BlueprintImplementableEvent, Category = "Attack")
	void OnEndedChargeHeavy();

	UFUNCTION(BlueprintImplementableEvent, Category = "Attack")
	void OnFireHeavy();

private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float HeavyMaxDamage = 60.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float HeavyMaxChargeTime = 2.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float HeavyMinPercentChargeToFire = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float HeavyPercentCharge = 0.f;

	bool IsChargingHeavy = false;
	float HeavyChargeTime = 0.f;
};


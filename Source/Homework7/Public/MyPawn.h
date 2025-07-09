#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyPawn.generated.h"

class UCapsuleComponent;
class USkeletalMeshComponent;
class USpringArmComponent;
class UCameraComponent;
class UMyCharacterMovement;

struct FInputActionValue;

UCLASS()
class HOMEWORK7_API AMyPawn : public APawn
{
	GENERATED_BODY()

public:
	AMyPawn();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	void Move(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable)
	void Stop(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable)
	void Look(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable)
	void Jump(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable)
	void ToggleSprint(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable)
	void ToggleCamera(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable)
	void ZoomCamera(const FInputActionValue& Value);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UCapsuleComponent> Collision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<USkeletalMeshComponent> SkeletalMeshComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<USpringArmComponent> SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UCameraComponent> Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UMyCharacterMovement> MyMovement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double RunSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double SprintSpeed;

protected:
	virtual void BeginPlay() override;

private:
	// 카메라 회전 및 확대 제어 변수
	bool bRotateCameraOnly;
	FRotator SavedCameraRotator;
	double DestYaw;
	double DestPitch;
	bool bIsEaseTransition;
	FTimerHandle TransitionTimer;
	double CameraDistance;

	UPROPERTY(EditAnywhere, Category = "Camera")
	double CameraTransitionAlpha;

	UPROPERTY(EditAnywhere, Category = "Camera")
	double CameraMaxDistance;

	UPROPERTY(EditAnywhere, Category = "Camera")
	double CameraMinDistance;

	UPROPERTY(EditAnywhere, Category = "Camera")
	double CameraZoomSpeed;
};

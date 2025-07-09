#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyDrone.generated.h"

class UCapsuleComponent;
class USpringArmComponent;
class UCameraComponent;
class UMyDroneMovement;

struct FInputActionValue;

UCLASS()
class HOMEWORK7_API AMyDrone : public APawn
{
	GENERATED_BODY()

public:
	AMyDrone();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void Move(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable)
	void Stop(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable)
	void Rotate(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable)
	void Fly(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable)
	void Land(const FInputActionValue& Value);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UCapsuleComponent> Collision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> StaticMeshComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<USpringArmComponent> SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UCameraComponent> Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UMyDroneMovement> MyMovement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsFly;

};

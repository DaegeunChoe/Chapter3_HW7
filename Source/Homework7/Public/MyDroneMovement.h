#pragma once

#include "CoreMinimal.h"
#include "MyPhysicsMovement.h"
#include "MyDroneMovement.generated.h"


UCLASS()
class HOMEWORK7_API UMyDroneMovement : public UMyPhysicsMovement
{
	GENERATED_BODY()

public:
	UMyDroneMovement();
	FVector CalculateAdditionalForce() const override;

	UPROPERTY(BlueprintReadOnly, Category = "Physics|Base")
	FVector InputForce;

	/// <summary>
	/// 이동 가속도
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement|Attributes")
	double MoveAcceleration;

	/// <summary>
	/// 최대 속력
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double FlySpeed;

	UFUNCTION(BlueprintCallable)
	void Move(FVector Direction);

	UFUNCTION(BlueprintCallable)
	void Stop();

	double GetGravitationalAcceleration() const;
	void SetGravitationalAcceleration(double Value);
	void ResetGravitationalAcceleration();

protected:
	double OriginGravitationalAcceleration;

	UFUNCTION(BlueprintCallable)
	void SetInputForce(FVector NewForce);
};

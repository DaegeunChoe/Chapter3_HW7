#pragma once

#include "CoreMinimal.h"
#include "MyPhysicsMovement.h"
#include "MyCharacterMovement.generated.h"

UCLASS()
class HOMEWORK7_API UMyCharacterMovement : public UMyPhysicsMovement
{
	GENERATED_BODY()

public:
	UMyCharacterMovement();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void Jump();

	UFUNCTION(BlueprintCallable)
	void Move(FVector Direction);

	UFUNCTION(BlueprintCallable)
	void Stop();

	/// <summary>
	/// 점프 가속도
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement|Attributes")
	double JumpAcceleration;

	/// <summary>
	/// 이동 가속도
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement|Attributes")
	double MoveAcceleration;

	/// <summary>
	/// 최대 속력
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement|Attributes")
	double MaxMoveSpeed;

	/// <summary>
	/// 에어 컨트롤
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement|Attributes")
	double AirControl;

	/// <summary>
	/// 최대 점프 횟수
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement|Attributes")
	int32 MaxJumpCount;

protected:
	virtual void CalculateForce(float DeltaTime) override;
	void OnLanded();

	UPROPERTY(BlueprintReadOnly)
	int32 RemainJumpCount;

	/// <summary>
	/// 사용자 입력에 의해 발생한 힘. N = kg * m / s^2
	/// </summary>
	UPROPERTY(BlueprintReadOnly, Category = "Physics|Base")
	FVector InputForce;

	/// <summary>
	/// 입력에 의한 힘을 지정한다.
	/// </summary>
	/// <param name="NewForce">외부 힘</param>
	UFUNCTION(BlueprintCallable)
	void SetInputForce(FVector NewForce);
};

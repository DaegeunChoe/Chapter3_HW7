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
	virtual void PostProcess() override;
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
	/// 최대 점프 횟수
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement|Attributes")
	int32 MaxJumpCount;

protected:

	void OnLanded();

	UPROPERTY(BlueprintReadOnly)
	int32 RemainJumpCount;
};

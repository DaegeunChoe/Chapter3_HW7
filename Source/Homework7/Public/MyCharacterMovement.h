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
	/// ���� ���ӵ�
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement|Attributes")
	double JumpAcceleration;

	/// <summary>
	/// �̵� ���ӵ�
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement|Attributes")
	double MoveAcceleration;

	/// <summary>
	/// �ִ� �ӷ�
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement|Attributes")
	double MaxMoveSpeed;

	/// <summary>
	/// �ִ� ���� Ƚ��
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement|Attributes")
	int32 MaxJumpCount;

protected:

	void OnLanded();

	UPROPERTY(BlueprintReadOnly)
	int32 RemainJumpCount;
};

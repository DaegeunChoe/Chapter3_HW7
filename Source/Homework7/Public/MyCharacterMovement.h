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
	/// ���� ��Ʈ��
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement|Attributes")
	double AirControl;

	/// <summary>
	/// �ִ� ���� Ƚ��
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement|Attributes")
	int32 MaxJumpCount;

protected:
	virtual void CalculateForce(float DeltaTime) override;
	void OnLanded();

	UPROPERTY(BlueprintReadOnly)
	int32 RemainJumpCount;

	/// <summary>
	/// ����� �Է¿� ���� �߻��� ��. N = kg * m / s^2
	/// </summary>
	UPROPERTY(BlueprintReadOnly, Category = "Physics|Base")
	FVector InputForce;

	/// <summary>
	/// �Է¿� ���� ���� �����Ѵ�.
	/// </summary>
	/// <param name="NewForce">�ܺ� ��</param>
	UFUNCTION(BlueprintCallable)
	void SetInputForce(FVector NewForce);
};

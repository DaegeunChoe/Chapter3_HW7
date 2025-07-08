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

	UFUNCTION(BlueprintCallable)
	void Jump();

	UFUNCTION(BlueprintCallable)
	void Move(FVector Direction);

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

	UPROPERTY(BlueprintReadOnly)
	int32 RemainJumpCount;
};

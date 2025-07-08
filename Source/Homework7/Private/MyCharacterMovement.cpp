#include "MyCharacterMovement.h"

UMyCharacterMovement::UMyCharacterMovement()
{
	JumpAcceleration = 20;
	MaxMoveSpeed = 600;

	MaxJumpCount = 1;
	RemainJumpCount = MaxJumpCount;
}

void UMyCharacterMovement::PostProcess()
{
	// 내 힘으로 뛰고 있을 때, 최고 속도가 너무 빠르면 조절함
}

void UMyCharacterMovement::Jump()
{
	if (RemainJumpCount > 0)
	{
		SetInstantForce(FVector(0, 0, 100) * JumpAcceleration, 0.1);
		//RemainJumpCount -= 1;
	}
}

void UMyCharacterMovement::Move(FVector Direction)
{
	Direction.Normalize();

}

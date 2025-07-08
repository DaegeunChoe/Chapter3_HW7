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
	// �� ������ �ٰ� ���� ��, �ְ� �ӵ��� �ʹ� ������ ������
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

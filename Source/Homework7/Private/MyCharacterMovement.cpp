#include "MyCharacterMovement.h"

UMyCharacterMovement::UMyCharacterMovement()
{
	JumpAcceleration = 2000.0;
	MoveAcceleration = 110000.0;
	MaxMoveSpeed = 450.0;

	MaxJumpCount = 1;
	RemainJumpCount = MaxJumpCount;
}

void UMyCharacterMovement::PostProcess()
{
	// 내 힘으로 뛰고 있을 때, 최고 속도를 제한함
	if (IsLanded() && !FMath::IsNearlyZero(InputForce.Length()))
	{
		if (Velocity.Length() > MaxMoveSpeed)
		{
			Velocity.Normalize();
			Velocity *= MaxMoveSpeed;
		}
	}
}

void UMyCharacterMovement::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	bool BeforeLanded = IsLanded();
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	bool AfterLanded = IsLanded();
	if (!BeforeLanded && AfterLanded)
	{
		OnLanded();
	}
}

void UMyCharacterMovement::Jump()
{
	if (RemainJumpCount > 0)
	{
		SetInstantForce(FVector(0, 0, 100) * JumpAcceleration, 0.1);
		RemainJumpCount -= 1;
	}
}

void UMyCharacterMovement::Move(FVector Direction)
{
	Direction.Normalize();
	SetInputForce(Direction * MoveAcceleration);
}

void UMyCharacterMovement::OnLanded()
{
	RemainJumpCount = MaxJumpCount;
}

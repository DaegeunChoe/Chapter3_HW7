#include "MyCharacterMovement.h"

UMyCharacterMovement::UMyCharacterMovement()
{
	JumpAcceleration = 2000.0;
	MoveAcceleration = 110000.0;
	MaxMoveSpeed = 450.0;

	MaxJumpCount = 1;
	RemainJumpCount = MaxJumpCount;

	InputForce = FVector::ZeroVector;
	AirControl = 0.5;
}

FVector UMyCharacterMovement::CalculateAdditionalForce() const
{
	FVector NewForce = FVector::ZeroVector;
	NewForce += Super::CalculateAdditionalForce();

	// �ְ� �ӵ����� ���� ���, �Է¿� ���� �̵��� �� ����
	double SpeedXY = FMath::Sqrt(Velocity.X * Velocity.X + Velocity.Y * Velocity.Y);
	if (SpeedXY <= MaxMoveSpeed && !FMath::IsNearlyZero(InputForce.Length()))
	{
		// �Է¿� ���� �� �߰� ���
		NewForce += InputForce * (IsLanded() ? 1.0 : AirControl);
	}
	return NewForce;
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

void UMyCharacterMovement::Stop()
{
	SetInputForce(FVector::ZeroVector);
}

void UMyCharacterMovement::OnLanded()
{
	RemainJumpCount = MaxJumpCount;
}

void UMyCharacterMovement::SetInputForce(FVector NewForce)
{
	InputForce = NewForce;
}

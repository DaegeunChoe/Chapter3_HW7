#include "MyDroneMovement.h"

UMyDroneMovement::UMyDroneMovement()
{
	OriginGravitationalAcceleration = GravitationalAcceleration;
	
	FlySpeed = 500;
	MoveAcceleration = 110000.0;
	InputForce = FVector::ZeroVector;
}

FVector UMyDroneMovement::CalculateAdditionalForce() const
{
	FVector NewForce = FVector::ZeroVector;
	NewForce += Super::CalculateAdditionalForce();

	// �ְ� �ӵ����� ���� ���, �Է¿� ���� �̵��� �� ����
	double Speed = Velocity.Length();
	if (Speed <= FlySpeed && !FMath::IsNearlyZero(InputForce.Length()))
	{
		NewForce += InputForce;
	}
	return NewForce;
}

void UMyDroneMovement::Move(FVector Direction)
{
	Direction.Normalize();
	SetInputForce(Direction * MoveAcceleration);
}

void UMyDroneMovement::Stop()
{
	SetInputForce(FVector::ZeroVector);
}

double UMyDroneMovement::GetGravitationalAcceleration() const
{
	return GravitationalAcceleration;
}

void UMyDroneMovement::SetGravitationalAcceleration(double Value)
{
	GravitationalAcceleration = Value;
}

void UMyDroneMovement::ResetGravitationalAcceleration()
{
	GravitationalAcceleration = OriginGravitationalAcceleration;
}

void UMyDroneMovement::SetInputForce(FVector NewForce)
{
	InputForce = NewForce;
}

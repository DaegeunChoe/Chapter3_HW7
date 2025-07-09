#include "MyPhysicsMovement.h"
#include "Components/CapsuleComponent.h"


UMyPhysicsMovement::UMyPhysicsMovement()
{
	PrimaryComponentTick.bCanEverTick = true;

	ActorCollisionComp = nullptr;

	NetForce = FVector::ZeroVector;
	Acceleration = FVector::ZeroVector;
	Velocity = FVector::ZeroVector;
	Mass = 1;

	AdditionalForce = FVector::ZeroVector;
	
	AirDragCoefficient = 0.7;
	AirDensity = 1.225;

	GravitationalAcceleration = 9.80665;

	MaxStaticFrictionCoefficient = 0.7;
	KineticFrictionCoefficient = 0.4;

	AccelerationThreshold = 1.0;
	VelocityThreshold = 1.0;

	bIsLanding = true;
}

void UMyPhysicsMovement::BeginPlay()
{
	Super::BeginPlay();

	if (ActorCollisionComp == nullptr)
	{
		if (AActor* Actor = GetOwner())
		{
			ActorCollisionComp = Actor->GetComponentByClass<UCapsuleComponent>();
		}
	}
}

void UMyPhysicsMovement::CalculateForce(float DeltaTime)
{
	// 중력
	NetForce = FVector::ZeroVector;
	NetForce += GetGravityForce();

	// 외력
	NetForce += CalculateAdditionalForce();

	// 다른 물체에 의한 항력
	bool bIsHit = false;
	bIsLanding = false;
	FVector NormalForce = GetNormalForce(DeltaTime, NetForce, bIsHit);
	if (bIsHit)
	{
		Acceleration = CollisionCounter(NormalForce, Acceleration);
		Velocity = CollisionCounter(NormalForce, Velocity);
		NetForce += NormalForce;

		if (NormalForce.Z > 0)
		{
			bIsLanding = true;
		}
	}

	// 공기저항, 마찰력
	FVector TotalDragForce = FVector::ZeroVector;
	TotalDragForce += GetAirDragForce();
	if (bIsHit)
	{
		TotalDragForce += GetFrictionForce(NormalForce);
	}
	NetForce += TotalDragForce;
}

FVector UMyPhysicsMovement::CalculateAdditionalForce() const
{
	return AdditionalForce;
}

void UMyPhysicsMovement::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	CalculateForce(DeltaTime);

	Acceleration = NetForce / Mass;
	if (Acceleration.Length() < AccelerationThreshold)
	{
		Acceleration *= 0;
	}

	Velocity += Acceleration * DeltaTime;
	if (Velocity.Length() < VelocityThreshold)
	{
		Velocity *= 0;
	}

	FVector Displacement = Velocity * DeltaTime;
	if (AActor* Actor = GetOwner())
	{
		Actor->AddActorWorldOffset(Displacement);
	}
}

void UMyPhysicsMovement::SetActorCollisionComponent(UShapeComponent* ActorComp)
{
	ActorCollisionComp = ActorComp;
}

void UMyPhysicsMovement::SetAdditionalForce(FVector NewForce)
{
	AdditionalForce = NewForce;
}

void UMyPhysicsMovement::SetInstantForce(FVector NewForce, double Time)
{
	// 힘을 즉시 적용
	Velocity += (NewForce / Mass) * Time;
}

bool UMyPhysicsMovement::IsFalling() const
{
	return !bIsLanding && Acceleration.Z > 0;
}

bool UMyPhysicsMovement::IsLanded() const
{
	return bIsLanding;
}

FVector FORCEINLINE UMyPhysicsMovement::GetAirDragForce() const
{
	if (ActorCollisionComp && !FMath::IsNearlyZero(Velocity.Length()))
	{
		double Speed = Velocity.Length();
		double Area = 0;
		if (UCapsuleComponent* CapsuleComp = Cast<UCapsuleComponent>(ActorCollisionComp))
		{
			Area = 1e-4 * 2 * CapsuleComp->GetScaledCapsuleHalfHeight() * CapsuleComp->GetScaledCapsuleRadius();
		}
		double Cosine = FMath::Cos((FMath::Sqrt(Velocity.X * Velocity.X + Velocity.Y * Velocity.Y))/(Velocity.Length()));
		return -0.5 * Velocity.GetSafeNormal() * (Speed * Speed) * AirDragCoefficient * AirDensity * Cosine * Area;
	}
	else
	{
		return FVector::ZeroVector;
	}
}

FVector FORCEINLINE UMyPhysicsMovement::GetGravityForce() const
{
	return FVector(0, 0, -100) * Mass * GravitationalAcceleration;
}

FVector UMyPhysicsMovement::GetNormalForce(float DeltaTime, FVector TargetForce, bool& bIsHit) const
{
	UWorld* World = GetWorld();
	AActor* Actor = GetOwner();
	if (IsValid(World) && IsValid(Actor) && ActorCollisionComp)
	{
		FVector TempAcceleration = TargetForce / Mass;
		FVector TempVelocity = TempAcceleration * DeltaTime;
		FVector TempDisplacement = TempVelocity * DeltaTime;
		FCollisionQueryParams Params;
		Params.AddIgnoredActor(Actor);

		TArray<FHitResult> SweepResults;
		World->SweepMultiByChannel(
			SweepResults,
			Actor->GetActorLocation(),
			Actor->GetActorLocation() + TempDisplacement,
			ActorCollisionComp->GetComponentQuat(),
			ECollisionChannel::ECC_Visibility,
			ActorCollisionComp->GetCollisionShape(),
			Params);

		FVector TotalNormalForce = FVector::ZeroVector;
		for (FHitResult& HitResult : SweepResults)
		{
			if (HitResult.GetActor())
			{
				bIsHit = true;
				double ForceScale = FMath::Abs(HitResult.ImpactNormal.Dot(NetForce));
				TotalNormalForce += HitResult.ImpactNormal * ForceScale;
			}
		}
		return TotalNormalForce;
	}
	bIsHit = false;
	return FVector::ZeroVector;
}

FVector UMyPhysicsMovement::GetFrictionForce(FVector NormalForce) const
{
	// 정지마찰력이 작용하는 구간
	if (FMath::IsNearlyZero(Velocity.Length()))
	{
		if (NetForce.Length() < NormalForce.Length() * MaxStaticFrictionCoefficient)
		{
			return -1 * NetForce;
		}
	}
	// 운동마찰력이 작용하는 구간
	FVector Direction = -1 * Velocity;
	Direction.Normalize();
	return NormalForce.Length() * KineticFrictionCoefficient * Direction;
}

FVector UMyPhysicsMovement::CollisionCounter(FVector Normal, FVector Input) const
{
	// 충돌에 의한 벡터 값 상쇄하기
	if (Normal.Dot(Input) < 0)
	{
		FVector C0 = FVector::CrossProduct(Input, Normal);
		FVector C1 = FVector::CrossProduct(Normal, C0);
		C1.Normalize();
		return C1 * Input.Dot(C1);
	}
	else
	{
		return Input;
	}
}

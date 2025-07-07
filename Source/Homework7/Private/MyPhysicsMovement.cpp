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

void UMyPhysicsMovement::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Acceleration = NetForce / Mass;
	Velocity += Acceleration * DeltaTime;
	FVector Displacement = Velocity * DeltaTime;

	if (AActor* Actor = GetOwner())
	{
		bool bIsLanded = IsLanded();
		UE_LOG(LogTemp, Display, TEXT("bIsLanded: %d"), bIsLanded ? 1 : 0);

		Actor->AddActorWorldOffset(Displacement);
	}
}

void UMyPhysicsMovement::ActorCollisionComponent(UCapsuleComponent* ActorComp)
{
	ActorCollisionComp = ActorComp;
}

void UMyPhysicsMovement::AddForce(FVector NewForce)
{
	NetForce += NewForce;
}

bool UMyPhysicsMovement::IsFalling() const
{
	return false;
}

/// <summary>
/// 발이 바닥에 닿아있는가?
/// </summary>
/// <returns>발이 바닥에 닿아있으면 true, 공중에 떠 있으면 false</returns>
bool UMyPhysicsMovement::IsLanded() const
{
	UWorld* World = GetWorld();
	AActor* Actor = GetOwner();
	if (IsValid(World) && IsValid(Actor) && ActorCollisionComp)
	{
		FVector FootDisplacement(0, 0, -20); // -Z축. 발 아래를 체크
		FCollisionQueryParams Params;
		Params.AddIgnoredActor(Actor);

		FHitResult SweepResult;
		World->SweepSingleByChannel(
			SweepResult,
			Actor->GetActorLocation(),
			Actor->GetActorLocation() + FootDisplacement,
			ActorCollisionComp->GetComponentQuat(),
			ECollisionChannel::ECC_Visibility,
			ActorCollisionComp->GetCollisionShape(),
			Params);
		
		if (SweepResult.GetActor())
		{
			UE_LOG(LogTemp, Display, TEXT("SweepResult.GetActor() %s"), *SweepResult.GetActor()->GetName());
			return true;
		}
		else
		{
			UE_LOG(LogTemp, Display, TEXT("SweepResult.GetActor() false"));
			return false;
		}
	}
	UE_LOG(LogTemp, Display, TEXT("Something Wrong"));
	return false;
}


bool UMyPhysicsMovement::WillOverlap() const
{
	UWorld* World = GetWorld();
	AActor* Actor = GetOwner();
	if (IsValid(World) && IsValid(Actor) && ActorCollisionComp)
	{
		float DeltaTime = 1.0 / 30.0; // 일정 시간 뒤의 미래를 감지
		FVector TempAcceleration = NetForce / Mass;
		FVector TempVelocity = Acceleration + TempAcceleration * DeltaTime;
		FVector TempDisplacement = TempVelocity * DeltaTime;
		FCollisionQueryParams Params;
		Params.AddIgnoredActor(Actor);

		FHitResult SweepResult;
		World->SweepSingleByChannel(
			SweepResult,
			Actor->GetActorLocation(),
			Actor->GetActorLocation() + TempDisplacement,
			ActorCollisionComp->GetComponentQuat(),
			ECollisionChannel::ECC_Visibility,
			ActorCollisionComp->GetCollisionShape(),
			Params);

		if (SweepResult.GetActor())
		{
			UE_LOG(LogTemp, Display, TEXT("SweepResult.GetActor() %s"), *SweepResult.GetActor()->GetName());
			return true;
		}
		else
		{
			UE_LOG(LogTemp, Display, TEXT("SweepResult.GetActor() false"));
			return false;
		}
	}
	UE_LOG(LogTemp, Display, TEXT("Something Wrong"));
	return false;
}

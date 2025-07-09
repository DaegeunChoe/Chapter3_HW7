#include "MyDrone.h"
#include "MyDroneController.h"
#include "EnhancedInputComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "MyDroneMovement.h"

AMyDrone::AMyDrone()
{
 	PrimaryActorTick.bCanEverTick = true;

	Collision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collision"));
	SetRootComponent(Collision);

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DroneBody"));
	StaticMeshComp->SetupAttachment(Collision);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->TargetArmLength = 500;
	SpringArm->SetupAttachment(Collision);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	MyMovement = CreateDefaultSubobject<UMyDroneMovement>(TEXT("MyMovement"));
	MyMovement->SetActorCollisionComponent(Collision);

	bIsFly = false;
}

void AMyDrone::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMyDrone::Move(const FInputActionValue& Value)
{
	if (bIsFly)
	{
		if (MyMovement)
		{
			FVector MoveInput = Value.Get<FVector>();
			FVector ForwardVector = GetActorForwardVector() * MoveInput.X;
			FVector RightVector = GetActorRightVector() * MoveInput.Y;
			FVector UpVector = GetActorUpVector() * MoveInput.Z;
			MyMovement->Move(ForwardVector + RightVector + UpVector);
		}
	}
}

void AMyDrone::Stop(const FInputActionValue& Value)
{
	if (MyMovement)
	{
		MyMovement->Stop();
	}
}

void AMyDrone::Rotate(const FInputActionValue& Value)
{
	if (bIsFly)
	{
		if (MyMovement)
		{
			FVector LookInput = Value.Get<FVector>();
			GEngine->AddOnScreenDebugMessage(-1, 0.2, FColor::Magenta, 
				FString::Printf(TEXT("(%.2f, %.2f, %.2f)"), LookInput.X, LookInput.Y, LookInput.Z));
			AddActorLocalRotation(FRotator(0, LookInput.X, 0));
			AddActorLocalRotation(FRotator(LookInput.Y, 0, 0));
			AddActorLocalRotation(FRotator(0, 0, LookInput.Z));
		}
	}
}

void AMyDrone::Fly(const FInputActionValue& Value)
{
	if (!bIsFly && Value.Get<bool>())
	{
		if (MyMovement)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("Fly!!"));
			MyMovement->SetGravitationalAcceleration(0);
			MyMovement->SetInstantForce(FVector(0, 0, 1000), 0.2);
			bIsFly = true;
		}
	}
}

void AMyDrone::Land(const FInputActionValue& Value)
{
	if (bIsFly && Value.Get<bool>())
	{
		if (MyMovement)
		{
			MyMovement->ResetGravitationalAcceleration();
			bIsFly = false;
		}
	}
}

void AMyDrone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyDrone::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (AMyDroneController* DC = Cast<AMyDroneController>(GetController()))
		{
			if (DC->RotateAction)
			{
				EnhancedInput->BindAction(DC->RotateAction, ETriggerEvent::Triggered, this, &AMyDrone::Rotate);
			}
			if (DC->MoveAction)
			{
				EnhancedInput->BindAction(DC->MoveAction, ETriggerEvent::Triggered, this, &AMyDrone::Move);
				EnhancedInput->BindAction(DC->MoveAction, ETriggerEvent::Completed, this, &AMyDrone::Stop);
			}
			if (DC->FlyAction)
			{
				EnhancedInput->BindAction(DC->FlyAction, ETriggerEvent::Triggered, this, &AMyDrone::Fly);
			}
			if (DC->LandAction)
			{
				EnhancedInput->BindAction(DC->LandAction, ETriggerEvent::Triggered, this, &AMyDrone::Land);
			}
		}
	}
}


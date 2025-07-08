#include "MyPawn.h"
#include "MyPlayerController.h"
#include "EnhancedInputComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "MyCharacterMovement.h"

AMyPawn::AMyPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	Collision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collision"));
	SetRootComponent(Collision);

	SkeletalMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	SkeletalMeshComp->SetupAttachment(Collision);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(Collision);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	MyMovement = CreateDefaultSubobject<UMyCharacterMovement>(TEXT("MyMovement"));
	MyMovement->SetActorCollisionComponent(Collision);
}

void AMyPawn::BeginPlay()
{
	Super::BeginPlay();
}

void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (AMyPlayerController* PC = Cast<AMyPlayerController>(GetController()))
		{
			if (PC->JumpAction)
			{
				EnhancedInput->BindAction(PC->JumpAction, ETriggerEvent::Triggered, this, &AMyPawn::Jump);
			}
			if (PC->MoveAction)
			{
				EnhancedInput->BindAction(PC->MoveAction, ETriggerEvent::Triggered, this, &AMyPawn::Move);
				EnhancedInput->BindAction(PC->MoveAction, ETriggerEvent::Completed, this, &AMyPawn::Stop);
			}
		}
	}
}

void AMyPawn::Move(const FInputActionValue& Value)
{
	if (MyMovement)
	{
		FVector2D MoveInput = Value.Get<FVector2D>();
		FVector ForwardVector = GetActorForwardVector() * MoveInput.X;
		FVector RightVector = GetActorRightVector() * MoveInput.Y;
		MyMovement->Move(ForwardVector + RightVector);
	}
}

void AMyPawn::Stop(const FInputActionValue& Value)
{
	if (MyMovement)
	{
		MyMovement->Stop();
	}
}

void AMyPawn::Look(const FInputActionValue& Value)
{
}

void AMyPawn::Jump(const FInputActionValue& Value)
{
	if (MyMovement)
	{
		MyMovement->Jump();
	}
}


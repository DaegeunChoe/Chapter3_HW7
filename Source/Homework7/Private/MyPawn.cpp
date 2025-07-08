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

	bRotateCameraOnly = false;
	SavedCameraRotator = FRotator::ZeroRotator;

	RunSpeed = 450;
	SprintSpeed = RunSpeed * 1.65;
	MyMovement->MaxMoveSpeed = RunSpeed;
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
			if (PC->LookAction)
			{
				EnhancedInput->BindAction(PC->LookAction, ETriggerEvent::Triggered, this, &AMyPawn::Look);
			}
			if (PC->SprintAction)
			{
				EnhancedInput->BindAction(PC->SprintAction, ETriggerEvent::Triggered, this, &AMyPawn::ToggleSprint);
			}
			if (PC->CameraToggleAction)
			{
				EnhancedInput->BindAction(PC->CameraToggleAction, ETriggerEvent::Triggered, this, &AMyPawn::ToggleCamera);
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
	FVector2D LookInput = Value.Get<FVector2D>();

	if (bRotateCameraOnly)
	{
		double Yaw = SpringArm->GetComponentRotation().Yaw + LookInput.X;
		double Pitch = SpringArm->GetComponentRotation().Pitch + LookInput.Y;
		SpringArm->SetWorldRotation(FRotator(Pitch, Yaw, 0));
	}
	else
	{
		AddActorLocalRotation(FRotator(0, LookInput.X, 0));
		if (SpringArm)
		{
			SpringArm->AddLocalRotation(FRotator(LookInput.Y, 0, 0));
		}
	}

	
}

void AMyPawn::Jump(const FInputActionValue& Value)
{
	if (MyMovement)
	{
		MyMovement->Jump();
	}
}

void AMyPawn::ToggleSprint(const FInputActionValue& Value)
{
	if (MyMovement)
	{
		if (Value.Get<bool>())
		{
			MyMovement->MaxMoveSpeed = SprintSpeed;
		}
		else
		{
			MyMovement->MaxMoveSpeed = RunSpeed;
		}
	}
}

void AMyPawn::ToggleCamera(const FInputActionValue& Value)
{
	if (Value.Get<bool>())
	{
		bRotateCameraOnly = true;
		if (SpringArm)
		{
			SavedCameraRotator = SpringArm->GetRelativeRotation();
		}
	}
	else
	{
		bRotateCameraOnly = false;
		SpringArm->SetRelativeRotation(SavedCameraRotator);
	}
}


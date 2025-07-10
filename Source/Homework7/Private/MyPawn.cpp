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
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	MyMovement = CreateDefaultSubobject<UMyCharacterMovement>(TEXT("MyMovement"));
	MyMovement->SetActorCollisionComponent(Collision);

	bRotateCameraOnly = false;
	DestYaw = DestPitch = 0;
	SavedCameraRotator = FRotator::ZeroRotator;
	bIsEaseTransition = false;
	CameraTransitionAlpha = 0.5;

	RunSpeed = 350;
	SprintSpeed = RunSpeed * 1.75;
	MyMovement->MaxMoveSpeed = RunSpeed;

	CameraZoomSpeed = 20;
	CameraMaxDistance = 600;
	CameraMinDistance = 200;
	CameraDistance = (CameraMaxDistance + CameraMinDistance) / 2.0;
	SpringArm->TargetArmLength = CameraDistance;
}

void AMyPawn::BeginPlay()
{
	Super::BeginPlay();
	DestYaw = SpringArm->GetComponentRotation().Yaw;
	DestPitch = SpringArm->GetComponentRotation().Pitch;
}

void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsEaseTransition)
	{
		FRotator A = SpringArm->GetRelativeRotation();
		FRotator B = FRotator(DestPitch, DestYaw, 0);
		FRotator Interp = A * (1 - CameraTransitionAlpha) + B * CameraTransitionAlpha;
		if ((FMath::Abs(A.Pitch - B.Pitch) + FMath::Abs(A.Yaw - B.Yaw)) <= 5)
		{
			SpringArm->SetRelativeRotation(B);
			bIsEaseTransition = false;
		}
		else
		{
			SpringArm->SetRelativeRotation(Interp);
		}
	}
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
			if (PC->CameraZoomAction)
			{
				EnhancedInput->BindAction(PC->CameraZoomAction, ETriggerEvent::Triggered, this, &AMyPawn::ZoomCamera);
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
		if (SpringArm)
		{
			DestYaw += LookInput.X;
			DestPitch += LookInput.Y;
		}
	}
	else
	{
		AddActorLocalRotation(FRotator(0, LookInput.X, 0));
		if (SpringArm)
		{
			DestPitch += LookInput.Y;
		}
	}

	if (!bIsEaseTransition)
	{
		SpringArm->SetRelativeRotation(FRotator(DestPitch, DestYaw, 0));
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
		bIsEaseTransition = true;
		DestYaw = SavedCameraRotator.Yaw;
		DestPitch = SavedCameraRotator.Pitch;
		if (TransitionTimer.IsValid())
		{
			GetWorldTimerManager().ClearTimer(TransitionTimer);
		}
		GetWorldTimerManager().SetTimer(TransitionTimer, [this]() {bIsEaseTransition = false;}, 1, false);
	}
}

void AMyPawn::ZoomCamera(const FInputActionValue& Value)
{
	float Single = Value.Get<float>();
	CameraDistance += Single * CameraZoomSpeed;
	CameraDistance = FMath::Clamp(CameraDistance, CameraMinDistance, CameraMaxDistance);
	SpringArm->TargetArmLength = CameraDistance;
}

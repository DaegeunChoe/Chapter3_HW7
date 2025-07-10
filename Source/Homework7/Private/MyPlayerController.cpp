#include "MyPlayerController.h"
#include "EnhancedInputSubsystems.h" 

AMyPlayerController::AMyPlayerController()
{
	IMC_Character = nullptr;
	MoveAction = nullptr;
	LookAction = nullptr;
	JumpAction = nullptr;
	SprintAction = nullptr;
	CameraZoomAction = nullptr;
	CameraToggleAction = nullptr;
}

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (ULocalPlayer* LP = GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = LP->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			if (IMC_Character)
			{
				Subsystem->AddMappingContext(IMC_Character, 0);
			}
		}
	}
}

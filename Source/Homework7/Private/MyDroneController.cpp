#include "MyDroneController.h"
#include "EnhancedInputSubsystems.h" 

AMyDroneController::AMyDroneController()
{
	IMC_Drone = nullptr;
	MoveAction = nullptr;
	RotateAction = nullptr;
	FlyAction = nullptr;
	LandAction = nullptr;
}

void AMyDroneController::BeginPlay()
{
	Super::BeginPlay();

	if (ULocalPlayer* LP = GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = LP->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			if (IMC_Drone)
			{
				Subsystem->AddMappingContext(IMC_Drone, 0);
			}
		}
	}
}

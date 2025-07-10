#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyDroneController.generated.h"

class UInputMappingContext;
class UInputAction;

UCLASS()
class HOMEWORK7_API AMyDroneController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AMyDroneController();
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TObjectPtr<UInputMappingContext> IMC_Drone;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TObjectPtr<UInputAction> RotateAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TObjectPtr<UInputAction> FlyAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TObjectPtr<UInputAction> LandAction;
};

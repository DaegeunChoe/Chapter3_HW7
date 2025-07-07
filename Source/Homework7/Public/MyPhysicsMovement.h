#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MyPhysicsMovement.generated.h"

class UCapsuleComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HOMEWORK7_API UMyPhysicsMovement : public UActorComponent
{
	GENERATED_BODY()

public:
	UMyPhysicsMovement();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void ActorCollisionComponent(UCapsuleComponent* ActorComp);

	UFUNCTION(BlueprintCallable)
	void AddForce(FVector NewForce);

	UFUNCTION(BlueprintCallable)
	bool IsFalling() const;

	UFUNCTION(BlueprintCallable)
	bool IsLanded() const;

	UFUNCTION(BlueprintCallable)
	bool WillOverlap() const;

protected:
	virtual void BeginPlay() override;

	/// <summary>
	/// 이 과제에서는 캡슐 컴포넌트만 고려한다.
	/// </summary>
	TObjectPtr<UCapsuleComponent> ActorCollisionComp;

	/// <summary>
	/// 알짜힘, 합력. N = kg * m / s^2
	/// </summary>
	UPROPERTY(BlueprintReadOnly, Category = "Physics|Base")
	FVector NetForce;

	/// <summary>
	/// 현재 가속도. m/s^2
	/// </summary>
	UPROPERTY(BlueprintReadOnly, Category = "Physics|Base")
	FVector Acceleration;

	/// <summary>
	/// 현재 속도. m/s
	/// </summary>
	UPROPERTY(BlueprintReadOnly, Category = "Physics|Base")
	FVector Velocity;

	/// <summary>
	/// 중력가속도. m/s^2
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Physics|Attributes")
	double GravitationalAcceleration;

	/// <summary>
	/// 물체 질량. kg
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Physics|Attributes")
	double Mass;
};

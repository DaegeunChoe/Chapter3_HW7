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
	
	/// <summary>
	/// 이 Component가 물리 시뮬레이션을 하는 물체의 생김새를 나타내는 UShapeComponent의 참조를 설정하는 함수
	/// UCapsuleComponent, UBoxComponent, 그리고 USphereComponent을 지원한다.
	/// </summary>
	/// <param name="ActorComp">Actor의 충돌을 처리하는 UShapeComponent 참조</param>
	UFUNCTION(BlueprintCallable)
	void SetActorCollisionComponent(UShapeComponent* ActorComp);

	/// <summary>
	/// 시뮬레이션 되는 힘 외에 다른 외부 힘을 지정한다.
	/// </summary>
	/// <param name="NewForce">외부 힘</param>
	UFUNCTION(BlueprintCallable)
	void SetAdditionalForce(FVector NewForce);

	/// <summary>
	/// 물체가 중력의 영향을 받아 아래로 떨어지는 중인가?
	/// </summary>
	/// <returns>공중에 떠 있으며, 바닥으로 떨어지는 중이면 True</returns>
	UFUNCTION(BlueprintCallable)
	bool IsFalling() const;

	/// <summary>
	/// 물체가 단단한 바닥 위에 있는가?
	/// </summary>
	/// <returns>바닥에 발이 닿아 있으면 True</returns>
	UFUNCTION(BlueprintCallable)
	bool IsLanded() const;

protected:
	virtual void BeginPlay() override;

	TObjectPtr<UShapeComponent> ActorCollisionComp;

	/// <summary>
	/// 알짜힘, 합력. N = kg * m / s^2
	/// </summary>
	UPROPERTY(BlueprintReadOnly, Category = "Physics|Base")
	FVector NetForce;

	/// <summary>
	/// 위부에서 가해지는 추가적인 힘. N = kg * m / s^2
	/// </summary>
	UPROPERTY(BlueprintReadOnly, Category = "Physics|Base")
	FVector AdditionalForce;

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

	/// <summary>
	/// 물체의 공기 저항 계수
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Physics|Attributes")
	double AirDragCoefficient;

	/// <summary>
	/// 물체가 있는 공간의 공기 밀도. kg/m^3
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Physics|Attributes")
	double AirDensity;

	/// <summary>
	/// 물체의 최대 정지 마찰 계수
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Physics|Attributes")
	double MaxStaticFrictionCoefficient;

	/// <summary>
	/// 물체의 운동 마찰 계수
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Physics|Attributes")
	double KineticFrictionCoefficient;

	/// <summary>
	/// 가속도가 이 값보다 작으면 적용하지 않음
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Physics|Attributes")
	double AccelerationThreshold;

	/// <summary>
	/// 속도가 이 값보다 작으면 적용하지 않음
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Physics|Attributes")
	double VelocityThreshold;


private:
	FVector GetAirDragForce() const;
	FVector GetGravityForce() const;
	FVector GetNormalForce(float DeltaTime, FVector TargetForce, bool& bIsHit) const;
	FVector GetFrictionForce(FVector NormalForce) const;
	FVector CollisionCounter(FVector Normal, FVector Input) const;

	bool bIsLanding;
};

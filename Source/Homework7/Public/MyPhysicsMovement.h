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
	/// �� Component�� ���� �ùķ��̼��� �ϴ� ��ü�� ������� ��Ÿ���� UShapeComponent�� ������ �����ϴ� �Լ�
	/// UCapsuleComponent, UBoxComponent, �׸��� USphereComponent�� �����Ѵ�.
	/// </summary>
	/// <param name="ActorComp">Actor�� �浹�� ó���ϴ� UShapeComponent ����</param>
	UFUNCTION(BlueprintCallable)
	void SetActorCollisionComponent(UShapeComponent* ActorComp);

	/// <summary>
	/// �ùķ��̼� �Ǵ� �� �ܿ� �ٸ� �ܺ� ���� �����Ѵ�.
	/// </summary>
	/// <param name="NewForce">�ܺ� ��</param>
	UFUNCTION(BlueprintCallable)
	void SetAdditionalForce(FVector NewForce);

	/// <summary>
	/// ��ü�� �߷��� ������ �޾� �Ʒ��� �������� ���ΰ�?
	/// </summary>
	/// <returns>���߿� �� ������, �ٴ����� �������� ���̸� True</returns>
	UFUNCTION(BlueprintCallable)
	bool IsFalling() const;

	/// <summary>
	/// ��ü�� �ܴ��� �ٴ� ���� �ִ°�?
	/// </summary>
	/// <returns>�ٴڿ� ���� ��� ������ True</returns>
	UFUNCTION(BlueprintCallable)
	bool IsLanded() const;

protected:
	virtual void BeginPlay() override;

	TObjectPtr<UShapeComponent> ActorCollisionComp;

	/// <summary>
	/// ��¥��, �շ�. N = kg * m / s^2
	/// </summary>
	UPROPERTY(BlueprintReadOnly, Category = "Physics|Base")
	FVector NetForce;

	/// <summary>
	/// ���ο��� �������� �߰����� ��. N = kg * m / s^2
	/// </summary>
	UPROPERTY(BlueprintReadOnly, Category = "Physics|Base")
	FVector AdditionalForce;

	/// <summary>
	/// ���� ���ӵ�. m/s^2
	/// </summary>
	UPROPERTY(BlueprintReadOnly, Category = "Physics|Base")
	FVector Acceleration;

	/// <summary>
	/// ���� �ӵ�. m/s
	/// </summary>
	UPROPERTY(BlueprintReadOnly, Category = "Physics|Base")
	FVector Velocity;

	/// <summary>
	/// �߷°��ӵ�. m/s^2
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Physics|Attributes")
	double GravitationalAcceleration;

	/// <summary>
	/// ��ü ����. kg
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Physics|Attributes")
	double Mass;

	/// <summary>
	/// ��ü�� ���� ���� ���
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Physics|Attributes")
	double AirDragCoefficient;

	/// <summary>
	/// ��ü�� �ִ� ������ ���� �е�. kg/m^3
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Physics|Attributes")
	double AirDensity;

	/// <summary>
	/// ��ü�� �ִ� ���� ���� ���
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Physics|Attributes")
	double MaxStaticFrictionCoefficient;

	/// <summary>
	/// ��ü�� � ���� ���
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Physics|Attributes")
	double KineticFrictionCoefficient;

	/// <summary>
	/// ���ӵ��� �� ������ ������ �������� ����
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Physics|Attributes")
	double AccelerationThreshold;

	/// <summary>
	/// �ӵ��� �� ������ ������ �������� ����
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

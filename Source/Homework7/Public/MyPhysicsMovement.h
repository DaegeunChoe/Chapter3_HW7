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
	/// �� ���������� ĸ�� ������Ʈ�� ����Ѵ�.
	/// </summary>
	TObjectPtr<UCapsuleComponent> ActorCollisionComp;

	/// <summary>
	/// ��¥��, �շ�. N = kg * m / s^2
	/// </summary>
	UPROPERTY(BlueprintReadOnly, Category = "Physics|Base")
	FVector NetForce;

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
};

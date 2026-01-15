// Zelda Games

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ZeldaSwimmingComponent.generated.h"

class AZeldaPlayerCharacter;
class UCharacterMovementComponent;
class USpringArmComponent;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ZELDA_API UZeldaSwimmingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UZeldaSwimmingComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	void SetupSwimmingPhysics() const;
	
private:
	// 自动获取 Owner 的指针
	UPROPERTY()
	TObjectPtr<AZeldaPlayerCharacter> OwnerCharacter;

	UPROPERTY()
	TObjectPtr<UCharacterMovementComponent> MovementComp;

	// 水面检测逻辑
	void HandleWaterFloating(float DeltaTime) const;
	
	void ApplyBuoyancyForce(float WaterLevel, float DeltaTime) const;
};

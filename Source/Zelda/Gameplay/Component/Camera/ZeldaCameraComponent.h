// Zelda Games

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ZeldaCameraComponent.generated.h"

class USpringArmComponent;
class UCameraComponent;

UENUM(BlueprintType)
enum class EZeldaCameraState : uint8
{
	Default,
	Swimming,
	Combat,
	Climbing
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ZELDA_API UZeldaCameraComponent : public UActorComponent
{
	GENERATED_BODY()
	
	UPROPERTY()
	TObjectPtr<USpringArmComponent> TargetSpringArm;

	FVector TargetSocketOffset;
	float TargetArmLength;
	
	EZeldaCameraState CurrentState = EZeldaCameraState::Default;
	
	void UpdateStateParameters();

protected:
	virtual void BeginPlay() override;
	
public:
	UZeldaCameraComponent();
	
	void Init(TObjectPtr<USpringArmComponent> Arm);
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetCameraState(EZeldaCameraState NewState);
};

// Zelda Games


#include "ZeldaCameraComponent.h"
#include "GameFramework/SpringArmComponent.h"


UZeldaCameraComponent::UZeldaCameraComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	TargetArmLength = 300.0f;
	TargetSocketOffset = FVector::ZeroVector;
}

void UZeldaCameraComponent::Init(TObjectPtr<USpringArmComponent> Arm)
{
	TargetSpringArm = Arm;
}


void UZeldaCameraComponent::UpdateStateParameters()
{
	switch (CurrentState)
	{
	case EZeldaCameraState::Default:
		TargetArmLength = 300.0f;
		TargetSocketOffset = FVector::ZeroVector;
		break;

	case EZeldaCameraState::Swimming:
		TargetArmLength = 600.0f;
		TargetSocketOffset = FVector(0.0f, 60.0f, 180.0f);
		break;
	default:
		TargetArmLength = 300.0f;
	}
}

void UZeldaCameraComponent::BeginPlay()
{
	Super::BeginPlay();
	
	
}


void UZeldaCameraComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if (!TargetSpringArm) return;
	
	TargetSpringArm->TargetArmLength = FMath::FInterpTo(TargetSpringArm->TargetArmLength, TargetArmLength, DeltaTime, 3.0f);
	TargetSpringArm->SocketOffset = FMath::VInterpTo(TargetSpringArm->SocketOffset, TargetSocketOffset, DeltaTime, 3.0f);
}

void UZeldaCameraComponent::SetCameraState(EZeldaCameraState NewState)
{
	if (CurrentState == NewState) return;
	CurrentState = NewState;
	UpdateStateParameters();
}


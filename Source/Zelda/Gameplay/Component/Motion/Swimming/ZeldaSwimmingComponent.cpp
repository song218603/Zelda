// Zelda Games


#include "ZeldaSwimmingComponent.h"

#include "Gameplay/Character/ZeldaPlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Character.h"


UZeldaSwimmingComponent::UZeldaSwimmingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	
}


void UZeldaSwimmingComponent::BeginPlay()
{
	Super::BeginPlay();
	
	OwnerCharacter = Cast<AZeldaPlayerCharacter>(GetOwner());
	if (OwnerCharacter)
	{
		MovementComp = Cast<UCharacterMovementComponent>(OwnerCharacter->GetMovementComponent());
	}
}


void UZeldaSwimmingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if (MovementComp && MovementComp->MovementMode == MOVE_Swimming)
	{
		HandleWaterFloating(DeltaTime);
	}

}

void UZeldaSwimmingComponent::SetupSwimmingPhysics() const
{
	if (MovementComp)
	{
		MovementComp->BrakingDecelerationSwimming = 2000.f;			// 增加阻力，松开键即停
		MovementComp->BrakingFrictionFactor = 2.0f;					// 增加切水感
		MovementComp->Buoyancy = 1.0f;								// 降低引擎默认浮力，改用我们组件的逻辑
	}
}

void UZeldaSwimmingComponent::HandleWaterFloating(float DeltaTime) const
{
	if (!OwnerCharacter || !MovementComp) return;
	
	FVector TraceStart = OwnerCharacter->GetActorLocation() + FVector(0.f, 0.f, 200.f); 
	FVector TraceEnd = OwnerCharacter->GetActorLocation() + FVector(0.f, 0.f, -200.f);

	FHitResult Hit;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(OwnerCharacter);

	// 使用刚才创建的 Water 频道进行检测
	if (GetWorld()->LineTraceSingleByChannel(Hit, TraceStart, TraceEnd, ECC_GameTraceChannel1, Params)) // 假设 Water 是第一个自定义通道
	{
		float WaterLevel = Hit.ImpactPoint.Z;
		ApplyBuoyancyForce(WaterLevel, DeltaTime);
	}
}

void UZeldaSwimmingComponent::ApplyBuoyancyForce(float WaterLevel, float DeltaTime) const
{
	float CharacterZ = OwnerCharacter->GetActorLocation().Z;
	float TargetZ = WaterLevel - 40.0f;
	if (CharacterZ < TargetZ)
	{
		// 计算高度差并应用向上的推力
		float Depth = TargetZ - CharacterZ;
		float BuoyancyStrength = 3.5f; // 调节浮力强弱
        
		// 核心公式：根据深度给予向上的速度补偿，配合 DeltaTime 实现平滑过渡
		MovementComp->Velocity.Z += (Depth * BuoyancyStrength) * DeltaTime * 100.f;

		// 限制最大上升速度，防止弹射
		MovementComp->Velocity.Z = FMath::Clamp(MovementComp->Velocity.Z, -500.f, 300.f);
	}
}
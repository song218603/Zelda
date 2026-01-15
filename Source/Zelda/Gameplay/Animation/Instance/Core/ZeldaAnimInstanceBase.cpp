// Zelda Games


#include "ZeldaAnimInstanceBase.h"
#include "Gameplay/Character/Core/ZeldaCharacterBase.h"
#include "KismetAnimationLibrary.h"
#include "GameFramework/PawnMovementComponent.h"
#include "AdvancedAnimation/BPInterface/AdvancedAnimationBPLibrary.h"

UZeldaAnimInstanceBase::UZeldaAnimInstanceBase() 
	: bDeath(false),
	bInAir(false),
	Direction(0.f),
	Velocity(0.f),
	Rotation(0.f),
	bArmed(false),
	bFootIK(false),
	FootIKID(INDEX_NONE),
	LeftBoneName(TEXT("foot_l")),
	RightBoneName(TEXT("foot_r"))
{
	
}

void UZeldaAnimInstanceBase::InitAnimInstance(ACharacter* InCharacter)
{
	if (!bFootIK) return;
	BoneNames.Add(LeftBoneName);
	BoneNames.Add(RightBoneName);
	FootIKID = UAdvancedAnimationBPLibrary::CreateFootIK(InCharacter, BoneNames);
}

float UZeldaAnimInstanceBase::GetFootIKOffset(const FName& BoneName)
{
	if (FootIKID == INDEX_NONE) return 0.f;
	return UAdvancedAnimationBPLibrary::FindOffset(FootIKID, BoneName);
}

void UZeldaAnimInstanceBase::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
}

void UZeldaAnimInstanceBase::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	
	if (AZeldaCharacterBase* CharacterBase = Cast<AZeldaCharacterBase>(TryGetPawnOwner()))
	{
		bInAir = CharacterBase->GetMovementComponent()->IsFalling();
		Rotation = CharacterBase->GetActorRotation().Vector();
		Velocity = CharacterBase->GetVelocity();
		Direction = UKismetAnimationLibrary::CalculateDirection(Velocity, CharacterBase->GetActorRotation());
		bArmed = CharacterBase->IsArmed();
	}
	
	if (FootIKID != INDEX_NONE)
	{
		TArray<float> FootIKOffsets;
		float LOffset = GetFootIKOffset(LeftBoneName);
		float ROffset = GetFootIKOffset(RightBoneName);
		FootIKOffsets.Add(LOffset);
		FootIKOffsets.Add(ROffset);
		ButtZOffset = UAdvancedAnimationBPLibrary::GetButtZOffset(FootIKOffsets);
		
		LeftOffset = ButtZOffset - LOffset;
		RightOffset = -(ButtZOffset - ROffset);
	}
	else
	{
		// 在不执行 IK 时重置偏移量，防止切换状态时骨骼瞬间位移
		LeftOffset = 0.f;
		RightOffset = 0.f;
		ButtZOffset = 0.f;
	}
}

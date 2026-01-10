// Zelda Games


#include "ZeldaAnimInstanceBase.h"
#include "Gameplay/Character/Core/ZeldaCharacterBase.h"
#include "KismetAnimationLibrary.h"
#include "GameFramework/PawnMovementComponent.h"

UZeldaAnimInstanceBase::UZeldaAnimInstanceBase() 
	: bDeath(false), bInAir(false), Direction(0.f), Velocity(0.f), Rotation(0.f), bArmed(false)
{
	
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
}

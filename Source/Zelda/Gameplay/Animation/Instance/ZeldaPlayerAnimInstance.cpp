// Zelda Games


#include "ZeldaPlayerAnimInstance.h"
#include "Gameplay/Character/ZeldaPlayerCharacter.h"

UZeldaPlayerAnimInstance::UZeldaPlayerAnimInstance() : MovementState(EPlayerMovementState::Standing)
{
	bArmed = false;
}

void UZeldaPlayerAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
}

void UZeldaPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	
	if (AZeldaPlayerCharacter* PlayerCharacter = Cast<AZeldaPlayerCharacter>(TryGetPawnOwner()))
	{
		MovementState = PlayerCharacter->GetMovementState();
		RightVector = PlayerCharacter->GetActorRightVector();
	}
}


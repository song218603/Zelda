// Zelda Games

#pragma once

#include "CoreMinimal.h"
#include "Core/ZeldaAnimInstanceBase.h"
#include "Gameplay/Core/ZeldaCharacterState.h"
#include "ZeldaPlayerAnimInstance.generated.h"


UCLASS()
class ZELDA_API UZeldaPlayerAnimInstance : public UZeldaAnimInstanceBase
{
	GENERATED_BODY()
	
public:
	UZeldaPlayerAnimInstance();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Zelda|AnimAttribute")
	EPlayerMovementState MovementState;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Zelda|AnimAttribute")
	FVector RightVector;
	
	FORCEINLINE EPlayerMovementState GetMovementState() const { return MovementState; }
	
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
};

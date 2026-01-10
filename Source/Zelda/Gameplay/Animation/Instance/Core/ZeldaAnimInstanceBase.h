// Zelda Games

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "ZeldaAnimInstanceBase.generated.h"


UCLASS()
class ZELDA_API UZeldaAnimInstanceBase : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Zelda|AnimAttribute")
	bool bDeath;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Zelda|AnimAttribute")
	bool bInAir;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Zelda|AnimAttribute")
	float Direction;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Zelda|AnimAttribute")
	FVector Velocity;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Zelda|AnimAttribute")
	FVector Rotation;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Zelda|AnimAttribute")
	bool bArmed;
	
	UZeldaAnimInstanceBase();
	
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
};

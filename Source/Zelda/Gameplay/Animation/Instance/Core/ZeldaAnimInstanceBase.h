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
	
	UPROPERTY(EditDefaultsOnly, Category = "Zelda|AnimAttribute|FootIK")
	bool bFootIK;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Zelda|AnimAttribute|FootIK")
	int32 FootIKID;
	
	UPROPERTY(EditDefaultsOnly, Category = "Zelda|AnimAttribute|FootIK")
	FName LeftBoneName;
	
	UPROPERTY(EditDefaultsOnly, Category = "Zelda|AnimAttribute|FootIK")
	FName RightBoneName;
	
	UPROPERTY(EditDefaultsOnly, Category = "Zelda|AnimAttribute|FootIK")
	TArray<FName> BoneNames;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Zelda|AnimAttribute|FootIK")
	float LeftOffset;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Zelda|AnimAttribute|FootIK")
	float RightOffset;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Zelda|AnimAttribute|FootIK")
	float ButtZOffset;
	
	UZeldaAnimInstanceBase();
	
	virtual void InitAnimInstance(ACharacter* InCharacter);
	
	UFUNCTION(BlueprintPure, BlueprintCallable)
	float GetFootIKOffset(const FName& BoneName);
	
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
};

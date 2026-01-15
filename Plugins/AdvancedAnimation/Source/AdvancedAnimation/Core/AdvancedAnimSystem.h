// Zelda Games

#pragma once

#include "CoreMinimal.h"
#include "Tickable.h"
#include "AdvancedAnimation/Core/Element/FootIK.h"
#include "AdvancedAnimation/Core/AdvancedAnimType.h"
// #include "AdvancedAnimSystem.generated.h"

class FAdvancedAnimSystem : public FTickableGameObject
{
public:
	static FAdvancedAnimSystem* Get();
	static void Destroy();
	
	virtual void Tick(float DeltaTime) override;
	virtual bool IsTickable() const override { return true; }
	virtual TStatId GetStatId() const override;
	
	FFootIK* FindFootIK(const AAHandle Handle);
	AAHandle CreateFootIK(ACharacter* InCharacter, const TArray<FName>& BoneNames, float TraceDistance = 50.f, float InterSpeed = 18.f, float TraceStart = 50.f);
	float FindOffset(const AAHandle Handle, const FName& InName);
	FFootIKInfo* FindFootIKInfo(const AAHandle Handle, const FName& InName);
	
protected:
	static FAdvancedAnimSystem* AdvancedAnimSystem;
	TMap<AAHandle, FFootIK> FootIKs;
};


// Zelda Games

#pragma once

#include "CoreMinimal.h"
#include "AdvancedAnimation/Core/AdvancedAnimType.h"
// #include "FootIK.generated.h"

struct FFootIK
{
	FFootIK();
	void Init(ACharacter* InCharacter, const TArray<FName>& BoneNames, float TraceDistance = 50.f, float InterSpeed = 18.f, float TraceStart = 50.f);
	void Tick(float DeltaTime);
	
	float FindOffset(const FName& InName);
	FFootIKInfo* FindFootIKInfo(const FName& InName);
	bool IsPendingKill() const { return bPendingKill; };
	
protected:
	ACharacter* CharacterInstance;
	TMap<FName, FFootIKInfo> IKInfos;
	float FootTraceDistance;
	float FootInterSpeed;
	float FootTraceStart;
	bool bPendingKill;
	
	float FootTrace(const FName& BoneName, float TraceDistance);
	
};

// Zelda Games


#include "AdvancedAnimSystem.h"

FAdvancedAnimSystem* FAdvancedAnimSystem::AdvancedAnimSystem = nullptr;

FAdvancedAnimSystem* FAdvancedAnimSystem::Get()
{
	if (!AdvancedAnimSystem) AdvancedAnimSystem = new FAdvancedAnimSystem();
	return AdvancedAnimSystem;
}

void FAdvancedAnimSystem::Destroy()
{
	if (AdvancedAnimSystem) delete AdvancedAnimSystem;
	AdvancedAnimSystem = nullptr;
}

void FAdvancedAnimSystem::Tick(float DeltaTime)
{
	GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Yellow, FString::Printf(TEXT("System Ticking... Count: %d"), FootIKs.Num()));
	for (auto& ik : FootIKs)
	{
		ik.Value.Tick(DeltaTime);
	}
	// 移除要被销毁的
	TArray<AAHandle> RemoveHandle;
	for (auto& ik : FootIKs)
	{
		if (!ik.Value.IsPendingKill()) continue;
		RemoveHandle.Add(ik.Key);
	}
	for (auto& handle : RemoveHandle)
	{
		FootIKs.Remove(handle);
	}
}

TStatId FAdvancedAnimSystem::GetStatId() const
{
	// return TStatId();
	RETURN_QUICK_DECLARE_CYCLE_STAT(FAdvancedAnimSystem, STATGROUP_Tickables);
}

FFootIK* FAdvancedAnimSystem::FindFootIK(const AAHandle Handle)
{
	return FootIKs.Find(Handle);
}

AAHandle FAdvancedAnimSystem::CreateFootIK(ACharacter* InCharacter, const TArray<FName>& BoneNames, float TraceDistance,
                                           float InterSpeed, float TraceStart)
{
	AAHandle Handle = FMath::RandRange(0, 9999999);
	while (FootIKs.Contains(Handle)) Handle = FMath::RandRange(0, 9999999);
	FFootIK& InFootIK = FootIKs.Add(Handle, FFootIK());
	InFootIK.Init(InCharacter, BoneNames, TraceDistance, InterSpeed, TraceStart);
	return Handle;
}

float FAdvancedAnimSystem::FindOffset(const AAHandle Handle, const FName& InName)
{
	if (FFootIK* IK = FindFootIK(Handle)) return IK->FindOffset(InName);
	return 0.0f;
}

FFootIKInfo* FAdvancedAnimSystem::FindFootIKInfo(const AAHandle Handle, const FName& InName)
{
	if (FFootIK* IK = FindFootIK(Handle)) return IK->FindFootIKInfo(InName);
	return nullptr;
}

// Zelda Games


#include "AdvancedAnimationBPLibrary.h"
#include "AdvancedAnimation/AdvancedAnimation.h"
#include "AdvancedAnimation/Core/AdvancedAnimSystem.h"

int32 UAdvancedAnimationBPLibrary::CreateFootIK(ACharacter* InCharacter, const TArray<FName>& InBoneName,
	float TraceDistance, float InterSpeed, float TraceStart)
{
	return FAdvancedAnimSystem::Get()->CreateFootIK(InCharacter, InBoneName, TraceDistance, InterSpeed, TraceStart);
}

float UAdvancedAnimationBPLibrary::FindOffset(const int32 InKey, const FName& InKeyName)
{
	return FAdvancedAnimSystem::Get()->FindOffset(InKey, InKeyName);
}

FFootIKInfo UAdvancedAnimationBPLibrary::FindFootIKInfo(const int32 InKey, const FName& InKeyName)
{
	return *FAdvancedAnimSystem::Get()->FindFootIKInfo(InKey, InKeyName);
}

float UAdvancedAnimationBPLibrary::GetButtZOffset(const TArray<float>& InOffsets)
{
	float Offset = INFINITY;
	for (const auto& offset : InOffsets) Offset = FMath::Min(Offset, offset);
	return Offset < 0.f ? Offset : 0.f;
}

void UAdvancedAnimationBPLibrary::ClearAdvancedAnimSystem()
{
	FAdvancedAnimSystem::Destroy();
}

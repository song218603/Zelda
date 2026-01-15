// Zelda Games


#include "FootIK.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetSystemLibrary.h"

FFootIK::FFootIK() 
	: CharacterInstance(nullptr), FootTraceDistance(50.f), FootInterSpeed(18.f), bPendingKill(false), FootTraceStart(50.f)
{
}

void FFootIK::Init(ACharacter* InCharacter, const TArray<FName>& BoneNames, float TraceDistance, float InterSpeed, float TraceStart)
{
	CharacterInstance = InCharacter;
	FootTraceDistance = TraceDistance;
	FootInterSpeed = InterSpeed;
	FootTraceStart = TraceStart;
	
	for (auto& name : BoneNames)
	{
		IKInfos.Add(name, FFootIKInfo());
	}
}

void FFootIK::Tick(float DeltaTime)
{
	for (auto& ik : IKInfos)
	{
		float OffsetTarget = FootTrace(ik.Key, FootTraceDistance);
		ik.Value.Offset = FMath::FInterpTo(ik.Value.Offset, OffsetTarget, DeltaTime, FootInterSpeed);
	}
}

float FFootIK::FindOffset(const FName& InName)
{
	if (!IKInfos.Contains(InName)) return 0.f;
	return IKInfos[InName].Offset;
}

FFootIKInfo* FFootIK::FindFootIKInfo(const FName& InName)
{
	if (!IKInfos.Contains(InName)) return nullptr;
	return IKInfos.Find(InName);
}

float FFootIK::FootTrace(const FName& BoneName, float TraceDistance)
{
	if (!CharacterInstance) return 0.f;
	if (CharacterInstance->IsPendingKillPending())
	{
		bPendingKill = true;
		CharacterInstance = nullptr;
		return 0.f;
	}

	float CharacterLocationZ = CharacterInstance->GetActorLocation().Z;
	float CapsuleHalfHeight = CharacterInstance->GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
	
	FVector FootSocketLocation = CharacterInstance->GetMesh()->GetSocketLocation(BoneName);
	
	FVector StartLocation = FootSocketLocation + FVector(0.f, 0.f, FootTraceStart);
	FVector EndLocation = FVector(StartLocation.X, StartLocation.Y, StartLocation.Z - (CapsuleHalfHeight + TraceDistance));
	
	FHitResult HitResult;
	UKismetSystemLibrary::LineTraceSingle(
		CharacterInstance->GetWorld(),
		StartLocation,
		EndLocation,
		ETraceTypeQuery::TraceTypeQuery1,
		false,
		TArray<AActor*>(),
		EDrawDebugTrace::None,
		HitResult,
		true,
		FLinearColor::Green,
		FLinearColor::Blue,
		1.f
		);
	if (HitResult.bBlockingHit)
	{
		// float Offset = HitResult.Location.Z - EndLocation.Z;
		// return Offset - TraceDistance;
		float Offset = HitResult.ImpactPoint.Z - FootSocketLocation.Z;
		return Offset;
	}
	
	return 0.f;
}

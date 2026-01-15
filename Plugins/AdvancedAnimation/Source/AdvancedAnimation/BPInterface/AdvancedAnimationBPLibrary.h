// Zelda Games

#pragma once

#include "CoreMinimal.h"
#include "AdvancedAnimation/Core/AdvancedAnimType.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AdvancedAnimationBPLibrary.generated.h"


UCLASS()
class ADVANCEDANIMATION_API UAdvancedAnimationBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "AdvancedAnimation|FootIK")
	static int32 CreateFootIK(ACharacter* InCharacter, const TArray<FName>& InBoneName, float TraceDistance = 50.f, float InterSpeed = 18.f, float TraceStart = 50.f);
	
	UFUNCTION(BlueprintCallable, Category = "AdvancedAnimation|FootIK")
	static float FindOffset(const int32 InKey, const FName& InKeyName);
	
	UFUNCTION(BlueprintCallable, Category = "AdvancedAnimation|FootIK")
	static FFootIKInfo FindFootIKInfo(const int32 InKey, const FName& InKeyName);
	
	UFUNCTION(BlueprintCallable, Category = "AdvancedAnimation|FootIK")
	static float GetButtZOffset(const TArray<float>& InOffsets);
	
	UFUNCTION(BlueprintCallable, Category = "AdvancedAnimation|FootIK")
	static void ClearAdvancedAnimSystem();
};

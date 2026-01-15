// Zelda Games

#pragma once

#include "CoreMinimal.h"
#include "AdvancedAnimType.generated.h"


typedef uint32 AAHandle;

USTRUCT(BlueprintType)
struct FFootIKInfo
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "AdvancedAnimation|FootIKInfo")
	float Offset;
};
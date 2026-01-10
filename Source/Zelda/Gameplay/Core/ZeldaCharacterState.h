// Zelda Games

#pragma once

#include "CoreMinimal.h"
#include "ZeldaCharacterState.generated.h"

UENUM(BlueprintType)
enum class EPlayerMovementState : uint8
{
	Standing		UMETA(DisplayName = "Standing"),
	Crouching		UMETA(DisplayName = "Crouching"),
	Proning			UMETA(DisplayName = "Proning"),
	Climbing		UMETA(DisplayName = "Climbing"),
	Swimming		UMETA(DisplayName = "Swimming")
};

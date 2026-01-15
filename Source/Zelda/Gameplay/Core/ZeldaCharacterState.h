// Zelda Games

#pragma once

#include "CoreMinimal.h"
#include "ZeldaCharacterState.generated.h"

UENUM(BlueprintType)
enum class EPlayerMovementState : uint8
{
	Default			UMETA(DisplayName = "Default"),
	Climbing		UMETA(DisplayName = "Climbing"),
	Swimming		UMETA(DisplayName = "Swimming")
};

// Zelda Games

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"

#include "CombatInterface.generated.h"


UINTERFACE(Blueprintable, BlueprintType, meta = (CannotImplementInterfaceBlueprint))
class COMBAT_API UCombatInterface : public UInterface
{
	GENERATED_BODY()
};


class COMBAT_API ICombatInterface
{
	GENERATED_BODY()

	
public:
	UFUNCTION(Category = "CombatPlugin|AnimSignal")
	virtual void AnimSignal(int32 InSignal);
};

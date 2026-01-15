// Zelda Games

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ZeldaCharacterAnimTable.generated.h"


USTRUCT(BlueprintType)
struct FZeldaCharacterAnimTable : public FTableRowBase
{
	GENERATED_BODY()
	
	FZeldaCharacterAnimTable();
	
	UPROPERTY(EditDefaultsOnly, Category = "Zelda|Player|AnimAttribute")
	UAnimMontage* Montage;
};

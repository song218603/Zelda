// Zelda Games

#pragma once

#include "CoreMinimal.h"
#include "Core/ZeldaCharacterBase.h"
#include "ZeldaNPCCharacter.generated.h"

UCLASS()
class ZELDA_API AZeldaNPCCharacter : public AZeldaCharacterBase
{
	GENERATED_BODY()

public:
	AZeldaNPCCharacter();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};

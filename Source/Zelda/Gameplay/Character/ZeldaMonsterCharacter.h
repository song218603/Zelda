// Zelda Games

#pragma once

#include "CoreMinimal.h"
#include "ZeldaNPCCharacter.h"
#include "ZeldaMonsterCharacter.generated.h"

UCLASS()
class ZELDA_API AZeldaMonsterCharacter : public AZeldaNPCCharacter
{
	GENERATED_BODY()

public:
	AZeldaMonsterCharacter();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};

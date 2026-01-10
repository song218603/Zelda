// Zelda Games

#pragma once

#include "CoreMinimal.h"
#include "ZeldaMonsterCharacter.h"
#include "ZeldaBossCharacter.generated.h"

UCLASS()
class ZELDA_API AZeldaBossCharacter : public AZeldaMonsterCharacter
{
	GENERATED_BODY()

public:
	AZeldaBossCharacter();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};

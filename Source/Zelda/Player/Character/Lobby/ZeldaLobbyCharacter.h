// Zelda Games

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ZeldaLobbyCharacter.generated.h"

UCLASS()
class ZELDA_API AZeldaLobbyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AZeldaLobbyCharacter();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};

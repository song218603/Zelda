// Zelda Games

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "LoginPawn.generated.h"

UCLASS()
class ZELDA_API ALoginPawn : public APawn
{
	GENERATED_BODY()

public:
	ALoginPawn();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};

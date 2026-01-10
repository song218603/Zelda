// Zelda Games


#include "LoginPawn.h"


ALoginPawn::ALoginPawn()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ALoginPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

void ALoginPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ALoginPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}


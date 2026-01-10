// Zelda Games


#include "ZeldaNPCCharacter.h"


AZeldaNPCCharacter::AZeldaNPCCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AZeldaNPCCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AZeldaNPCCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AZeldaNPCCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}


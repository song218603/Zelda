// Zelda Games


#include "ZeldaMonsterCharacter.h"


AZeldaMonsterCharacter::AZeldaMonsterCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AZeldaMonsterCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AZeldaMonsterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AZeldaMonsterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}


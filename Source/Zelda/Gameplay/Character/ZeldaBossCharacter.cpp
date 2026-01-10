// Zelda Games


#include "ZeldaBossCharacter.h"


AZeldaBossCharacter::AZeldaBossCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AZeldaBossCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AZeldaBossCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AZeldaBossCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}


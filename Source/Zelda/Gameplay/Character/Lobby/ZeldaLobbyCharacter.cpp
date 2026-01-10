// Zelda Games


#include "ZeldaLobbyCharacter.h"


AZeldaLobbyCharacter::AZeldaLobbyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AZeldaLobbyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AZeldaLobbyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AZeldaLobbyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}


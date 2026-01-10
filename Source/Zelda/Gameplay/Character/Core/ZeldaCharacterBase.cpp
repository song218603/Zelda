// Zelda Games


#include "ZeldaCharacterBase.h"


AZeldaCharacterBase::AZeldaCharacterBase() : bArmed(false), ID(INDEX_NONE)
{
	PrimaryActorTick.bCanEverTick = true;
}

void AZeldaCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AZeldaCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AZeldaCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

// void AZeldaCharacterBase::AnimSignal(int32 InSignal)
// {
// 	ICombatInterface::AnimSignal(InSignal);
// 	// K2_AnimSignal(InSignal);
// }

void AZeldaCharacterBase::OnRep_ArmedChanged()
{
}

void AZeldaCharacterBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AZeldaCharacterBase, bArmed);
}

void AZeldaCharacterBase::SwitchArmedStateOnServer_Implementation(bool bInArmed)
{
	bArmed = bInArmed;
}

// Zelda Games


#include "ZeldaCharacterBase.h"
#include "GameBase/GameState/ZeldaGameState.h"
#include "Gameplay/Animation/Instance/Core/ZeldaAnimInstanceBase.h"
#include "Components/SkeletalMeshComponent.h"

AZeldaCharacterBase::AZeldaCharacterBase() : bArmed(false), ID(INDEX_NONE)
{
	PrimaryActorTick.bCanEverTick = true;
}

void AZeldaCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
	if (GetWorld())
	{
		
		// if (!HasAuthority())
		// {
		if (UZeldaAnimInstanceBase* InAnimInstance = Cast<UZeldaAnimInstanceBase>(GetMesh()->GetAnimInstance()))
		{
			InAnimInstance->InitAnimInstance(this);
		}
		// }
	}
}

void AZeldaCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AZeldaCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

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

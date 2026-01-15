// Zelda Games


#include "ZeldaWeapon.h"


AZeldaWeapon::AZeldaWeapon()
{
	PrimaryActorTick.bCanEverTick = true;
	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	RootComponent = WeaponMesh;
	WeaponMesh->SetSimulatePhysics(false);
	static ConstructorHelpers::FObjectFinder<UDataTable> CharacterAnimDataTable(TEXT("/Game/ZeldaGame/GameAbility/DataTable/DT_ZeldaCharacterAnimDataTable"));
	
	if (CharacterAnimDataTable.Succeeded())
	{
		AnimDataTable = CharacterAnimDataTable.Object;
	}
}


void AZeldaWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}


void AZeldaWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


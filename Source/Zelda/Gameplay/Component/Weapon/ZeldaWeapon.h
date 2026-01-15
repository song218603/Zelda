// Zelda Games

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gameplay/Animation/Instance/Core/ZeldaAnimInstanceBase.h"
#include "Gameplay/GameAbility/DataTable/ZeldaCharacterAnimTable.h"
#include "ZeldaWeapon.generated.h"

UCLASS()
class ZELDA_API AZeldaWeapon : public AActor
{
	GENERATED_BODY()

public:
	AZeldaWeapon();

protected:
	// 武器模型
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Zelda|Weapon")
	UStaticMeshComponent* WeaponMesh;
	
	
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Zelda|Weapon|Animation")
	TSubclassOf<UZeldaAnimInstanceBase> LocomotionLayerClass;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Zelda|Data")
	class UDataTable* AnimDataTable;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Zelda|Weapon|Combat")
	FName AttackRowName;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Zelda|Weapon")
	float BaseDamage = 10.f;
};

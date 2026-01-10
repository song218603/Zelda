// Zelda Games

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Gameplay/GameAbility/DataTable/ZeldaCharacterAnimTable.h"
#include "Net/UnrealNetwork.h"
#include "Combat/Interface/CombatInterface.h"
#include "ZeldaCharacterBase.generated.h"

UCLASS()
class ZELDA_API AZeldaCharacterBase : public ACharacter, public ICombatInterface
{
	GENERATED_BODY()

public:
	AZeldaCharacterBase();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	FORCEINLINE bool IsArmed() const { return bArmed; }
	FORCEINLINE FZeldaCharacterAnimTable GetAnimTable() const { return AnimTable; }
	FORCEINLINE int32 GetID() const { return ID; }
	
protected:
	UPROPERTY(ReplicatedUsing = OnRep_ArmedChanged, EditDefaultsOnly, Category = "Zelda|Character|State")
	bool bArmed;
	
	UPROPERTY(EditDefaultsOnly, Category = "Zelda|Character|ID")
	int32 ID;
	
	UPROPERTY()
	FZeldaCharacterAnimTable AnimTable;
	
	UFUNCTION()
	virtual void OnRep_ArmedChanged();
	
	UFUNCTION(Server, Reliable)
	void SwitchArmedStateOnServer(bool bInArmed);
	
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;
};

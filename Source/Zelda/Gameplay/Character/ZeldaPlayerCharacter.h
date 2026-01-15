// Zelda Games

#pragma once

#include "CoreMinimal.h"
#include "Core/ZeldaCharacterBase.h"
#include "Gameplay/Component/Camera/ZeldaCameraComponent.h"
#include "Gameplay/Component/Weapon/ZeldaWeapon.h"
#include "Gameplay/Core/ZeldaCharacterState.h"
#include "ZeldaPlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputAction;
struct FInputActionValue;
class UZeldaSwimmingComponent;

enum class EPlayerAttack : uint8
{
	Normal,
	Heavy,
};

UCLASS(abstract)
class ZELDA_API AZeldaPlayerCharacter : public AZeldaCharacterBase
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Zelda|Player|Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Zelda|Player|Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> FollowCamera;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Zelda|Player|Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UZeldaCameraComponent> CameraComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Zelda|Player|Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UZeldaSwimmingComponent> SwimmingComponent;
	
protected:
	// InputAction
	UPROPERTY(EditAnywhere, Category="Zelda|Player|Input")
	UInputAction* JumpAction;
	UPROPERTY(EditAnywhere, Category="Zelda|Player|Input")
	UInputAction* MoveAction;
	UPROPERTY(EditAnywhere, Category="Zelda|Player|Input")
	UInputAction* LookAction;
	UPROPERTY(EditAnywhere, Category="Zelda|Player|Input")
	UInputAction* MouseLookAction;
	UPROPERTY(EditAnywhere, Category="Zelda|Player|Input")
	UInputAction* NormalAttackAction;
	UPROPERTY(EditAnywhere, Category="Zelda|Player|Input")
	UInputAction* HeavyAttackAction;
	UPROPERTY(EditAnywhere, Category="Zelda|Player|Input")
	UInputAction* ArmedAction;
	
	UPROPERTY(EditAnywhere, Category="Zelda|Player|Movement")
	EPlayerMovementState MovementState;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Zelda|Player|Combat")
	bool bIsAttacking;
	
	// 连招重置的时间间隔
	UPROPERTY(EditAnywhere, Category = "Zelda|Player|Combat")
	float ComboResetTime = 1.5f;
	
	TArray<EPlayerAttack> AttackSequence;	// 根据不同的攻击序列来触发不同的 Combo
	
	// 定时器句柄
	FTimerHandle TimerHandle_ResetCombo;
	
	// Weapon
	UPROPERTY(EditDefaultsOnly, Category = "Zelda|Player|Weapon")
	TArray<TSubclassOf<class AZeldaWeapon>> StartingWeaponClasses;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Zelda|Player|Weapon")
	TArray<AZeldaWeapon*> HeldWeapons;
	
	UPROPERTY(EditDefaultsOnly, Category = "Zelda|Player|Weapon")
	int32 CurrentWeaponIndex = -1;
	
	UPROPERTY(BlueprintReadOnly, Category = "Zelda|Player|Weapon")
	AZeldaWeapon* ActiveWeapon;
	

	virtual void BeginPlay() override;
	
	void Move(const FInputActionValue& Value);
	
	void Look(const FInputActionValue& Value);
	
	void NormalAttack();
	
	void HeavyAttack();
	
	void SwitchArmed();
	
	void PickUp();
	
public:
	AZeldaPlayerCharacter();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	virtual void OnMovementModeChanged(EMovementMode PrevMovementMode, uint8 PreviousCustomMode) override;
	
	// InputAction
	UFUNCTION(BlueprintCallable, Category="Zelda|Player|Input")
	virtual void DoMove(float Right, float Forward);
	UFUNCTION(BlueprintCallable, Category="Zelda|Player|Input")
	virtual void DoLook(float Yaw, float Pitch);
	UFUNCTION(BlueprintCallable, Category="Zelda|Player|Input")
	virtual void DoJumpStart();
	UFUNCTION(BlueprintCallable, Category="Zelda|Player|Input")
	virtual void DoJumpEnd();
	
	// Attack
	UFUNCTION(BlueprintCallable, Category = "Zelda|Player|Combat")
	void ResetAttack();
	
	UFUNCTION(BlueprintCallable, Category = "Zelda|Player|Combat")
	void OnExecuteAttack(FName SkillName);
	
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	
	FORCEINLINE EPlayerMovementState GetMovementState() const { return MovementState; }
	
	void SetMovementState(EPlayerMovementState NewState);
	
	void ResetAttackSequence();
	
	void UpdateCharacterWeaponState();
};

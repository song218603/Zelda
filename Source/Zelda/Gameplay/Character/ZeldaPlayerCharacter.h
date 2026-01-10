// Zelda Games

#pragma once

#include "CoreMinimal.h"
#include "Core/ZeldaCharacterBase.h"
#include "Gameplay/Core/ZeldaCharacterState.h"
#include "ZeldaPlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputAction;
struct FInputActionValue;

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
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Zelda|Player|Components", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	
protected:
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
	
	UPROPERTY(EditAnywhere, Category="Zelda|Player|Movement")
	EPlayerMovementState MovementState;
	
	// 攻击动画蒙太奇
	UPROPERTY(EditAnywhere, Category = "Zelda|Player|Combat")
	UAnimMontage* NormalAttackMontage;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Zelda|Player|Combat")
	bool bIsAttacking;
	
	// 连招重置的时间间隔
	UPROPERTY(EditAnywhere, Category = "Combat")
	float ComboResetTime = 1.5f;
	
	TArray<EPlayerAttack> AttackSequence;	// 根据不同的攻击序列来触发不同的 Combo
	
	// 定时器句柄
	FTimerHandle TimerHandle_ResetCombo;
	

public:
	AZeldaPlayerCharacter();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
protected:
	virtual void BeginPlay() override;
	
	void Move(const FInputActionValue& Value);
	
	void Look(const FInputActionValue& Value);
	
	void NormalAttack();
	
	void HeavyAttack();

public:
	UFUNCTION(BlueprintCallable, Category="Zelda|Player|Input")
	virtual void DoMove(float Right, float Forward);
	
	UFUNCTION(BlueprintCallable, Category="Zelda|Player|Input")
	virtual void DoLook(float Yaw, float Pitch);
	
	UFUNCTION(BlueprintCallable, Category="Zelda|Player|Input")
	virtual void DoJumpStart();
	
	UFUNCTION(BlueprintCallable, Category="Zelda|Player|Input")
	virtual void DoJumpEnd();
	
	UFUNCTION(BlueprintCallable, Category = "Zelda|Player|Combat")
	void ResetAttack();
	
	UFUNCTION(BlueprintCallable, Category = "Zelda|Player|Combat")
	void OnExecuteAttack(FName SkillName);
	
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	
	FORCEINLINE EPlayerMovementState GetMovementState() const { return MovementState; }
	
	// 切换状态
	void SwitchArmedState();
	
	void SetMovementState(EPlayerMovementState NewState);
	
	void ResetAttackSequence();
	
	void ArmedChanged();
	
	// 网络同步
	// UFUNCTION() 父类写过子类就不能写了
	virtual void OnRep_ArmedChanged();
};

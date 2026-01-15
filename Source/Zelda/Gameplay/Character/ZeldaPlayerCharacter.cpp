// Zelda Games


#include "ZeldaPlayerCharacter.h"

#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Gameplay/Component/Motion/Swimming/ZeldaSwimmingComponent.h"
#include "Zelda.h"

#define CheckFunction(Message) GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, Message);

AZeldaPlayerCharacter::AZeldaPlayerCharacter() : MovementState(EPlayerMovementState::Default)
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;
	
	GetCharacterMovement()->bOrientRotationToMovement = false;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
	
	GetCharacterMovement()->JumpZVelocity = 500.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Camera
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
	
	CameraComponent = CreateDefaultSubobject<UZeldaCameraComponent>(TEXT("CameraComponent"));
	
	GetCharacterMovement()->MaxWalkSpeedCrouched = 150.f;
	// 允许角色蹲下
	GetCharacterMovement()->GetNavAgentPropertiesRef().bCanCrouch = true;
	
	// Swimming Component
	SwimmingComponent = CreateDefaultSubobject<UZeldaSwimmingComponent>(TEXT("SwimmingComponent"));
}

void AZeldaPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (CameraComponent) CameraComponent->Init(CameraBoom);
	
	if (StartingWeaponClasses.IsEmpty()) return;
	
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = GetInstigator();

	for (TSubclassOf<AZeldaWeapon> WeaponClass : StartingWeaponClasses)
	{
		if (WeaponClass)
		{
			if (AZeldaWeapon* NewWeapon = GetWorld()->SpawnActor<AZeldaWeapon>(WeaponClass, SpawnParams))
			{
				NewWeapon->SetActorHiddenInGame(true);
				HeldWeapons.Add(NewWeapon);
			}
		}
	}
}

void AZeldaPlayerCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();
	DoMove(MovementVector.X, MovementVector.Y);
}

void AZeldaPlayerCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	// route the input
	DoLook(LookAxisVector.X, LookAxisVector.Y);
}

// 普通攻击
void AZeldaPlayerCharacter::NormalAttack()
{
	if (!bArmed) return;
	if (bIsAttacking || MovementState != EPlayerMovementState::Default) return;
	
	AttackSequence.Add(EPlayerAttack::Normal);
	bIsAttacking = true;
	FName AttackName = TEXT("SwordNormalAttack");
	OnExecuteAttack(AttackName);
	ResetAttack();
	GetWorldTimerManager().SetTimer(TimerHandle_ResetCombo, this, &ThisClass::ResetAttackSequence, ComboResetTime, false);
}

// 重攻击
void AZeldaPlayerCharacter::HeavyAttack()
{
	if (!bArmed) return;
	if (bIsAttacking || MovementState != EPlayerMovementState::Default) return;
	
	AttackSequence.Add(EPlayerAttack::Heavy);
	
	bIsAttacking = true;
	// OnExecuteAttack("");
	// ResetAttack();
	GetWorldTimerManager().SetTimer(TimerHandle_ResetCombo, this, &ThisClass::ResetAttackSequence, ComboResetTime, false);
}

void AZeldaPlayerCharacter::SwitchArmed()
{
	if (HeldWeapons.IsEmpty() || bArmed) bArmed = false;
	else
	{
		bArmed = true;
		if (CurrentWeaponIndex == -1) CurrentWeaponIndex = 0;
		ActiveWeapon = HeldWeapons[CurrentWeaponIndex];
	}
	UpdateCharacterWeaponState();
	// 稍后再考虑服务器同步
	// SwitchArmedStateOnServer(bArmed);
}

// 捡起物品（包括武器和道具）
void AZeldaPlayerCharacter::PickUp()
{
	// TO DO
}

void AZeldaPlayerCharacter::DoMove(float Right, float Forward)
{
	if (GetController() != nullptr)
	{
		float FinalForward = Forward;
		
		if (MovementState == EPlayerMovementState::Swimming)
		{
			FinalForward = FMath::Max(0.0f, Forward);
		}
		
		const FRotator Rotation = GetController()->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(ForwardDirection, FinalForward);
		AddMovementInput(RightDirection, Right);
	}
}

void AZeldaPlayerCharacter::DoLook(float Yaw, float Pitch)
{
	if (GetController() != nullptr)
	{
		AddControllerYawInput(Yaw);
		AddControllerPitchInput(Pitch);
	}
}

void AZeldaPlayerCharacter::DoJumpStart()
{
	Jump();
}

void AZeldaPlayerCharacter::DoJumpEnd()
{
	StopJumping();
}

void AZeldaPlayerCharacter::ResetAttack()
{
	bIsAttacking = false;
}

// 播放攻击蒙太奇
void AZeldaPlayerCharacter::OnExecuteAttack(FName SkillName)
{
	if (!ActiveWeapon->AnimDataTable)
	{
		UE_LOG(LogZelda, Error, TEXT("Can`t Access ActiveWeapon`s AnimDataTable"));
		return;
	}
	FZeldaCharacterAnimTable* DataRow = ActiveWeapon->AnimDataTable->FindRow<FZeldaCharacterAnimTable>(SkillName, TEXT("NormalAttackContext"));
	
	if (DataRow)
	{
		// 将查找到的数据同步到你的成员变量 AnimTable 中（如果你后续还需要用到它）
		AnimTable = *DataRow;

		// 播放蒙太奇
		if (AnimTable.Montage)
		{
			// 使用你指定的 Slot 或 Section "1"
			PlayAnimMontage(AnimTable.Montage, 1.0f, TEXT("Sec1"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("在数据表中未找到行：%s"), *SkillName.ToString());
	}
}

void AZeldaPlayerCharacter::SetMovementState(EPlayerMovementState NewState)
{
	MovementState = NewState;
}

// 清空攻击序列，Combo重新计算
void AZeldaPlayerCharacter::ResetAttackSequence()
{
	if (AttackSequence.Num() > 0)
	{
		AttackSequence.Empty();
		UE_LOG(LogZelda, Log, TEXT("Attack Sequence Cleared due to timeout."));
	}
}

// 更新玩家持有武器的状态
void AZeldaPlayerCharacter::UpdateCharacterWeaponState()
{
	UZeldaAnimInstanceBase* AnimInst = Cast<UZeldaAnimInstanceBase>(GetMesh()->GetAnimInstance());
	if (bArmed)
	{
		ActiveWeapon->SetActorHiddenInGame(false);
		ActiveWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("WeaponSocket"));
		if (AnimInst && ActiveWeapon->LocomotionLayerClass)
			AnimInst->LinkAnimClassLayers(ActiveWeapon->LocomotionLayerClass);
	}
	else
	{
		if (AnimInst) AnimInst->StopAllMontages(0.2f);
		ActiveWeapon->SetActorHiddenInGame(true);
		ActiveWeapon->SetActorEnableCollision(false);
		AnimInst->UnlinkAnimClassLayers(ActiveWeapon->LocomotionLayerClass);
		FString ModeDec = StaticEnum<EMovementMode>()->GetValueAsString(GetCharacterMovement()->MovementMode);
	}
}

void AZeldaPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AZeldaPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
		
		// Attack
		EnhancedInputComponent->BindAction(NormalAttackAction, ETriggerEvent::Triggered, this, &ThisClass::NormalAttack);
		EnhancedInputComponent->BindAction(HeavyAttackAction, ETriggerEvent::Triggered, this, &ThisClass::HeavyAttack);
		EnhancedInputComponent->BindAction(ArmedAction, ETriggerEvent::Triggered, this, &ThisClass::SwitchArmed);
		
		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ThisClass::Move);
		EnhancedInputComponent->BindAction(MouseLookAction, ETriggerEvent::Triggered, this, &ThisClass::Look);
		
		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ThisClass::Look);
	}
	else
	{
		UE_LOG(LogZelda, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AZeldaPlayerCharacter::OnMovementModeChanged(EMovementMode PrevMovementMode, uint8 PreviousCustomMode)
{
	Super::OnMovementModeChanged(PrevMovementMode, PreviousCustomMode);
	
	if (SwimmingComponent)
	{
		if (GetCharacterMovement()->MovementMode == MOVE_Swimming)
		{
			if (MovementState != EPlayerMovementState::Swimming) MovementState = EPlayerMovementState::Swimming;
			SwimmingComponent->SetupSwimmingPhysics();
			CameraComponent->SetCameraState(EZeldaCameraState::Swimming);
			bArmed = false;
			UpdateCharacterWeaponState();
		}
		else if (PrevMovementMode == MOVE_Swimming)
		{
			if (MovementState != EPlayerMovementState::Default) MovementState = EPlayerMovementState::Default;
			CameraComponent->SetCameraState(EZeldaCameraState::Default);
		}
	}
}

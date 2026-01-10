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
#include "Zelda.h"


AZeldaPlayerCharacter::AZeldaPlayerCharacter() : MovementState(EPlayerMovementState::Standing)
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

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
}

void AZeldaPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
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
	if (bIsAttacking || MovementState != EPlayerMovementState::Standing) return;
	
	
	AttackSequence.Add(EPlayerAttack::Normal);
	
	bIsAttacking = true;
	OnExecuteAttack("");
	
	GetWorldTimerManager().SetTimer(TimerHandle_ResetCombo, this, &ThisClass::ResetAttackSequence, ComboResetTime, false);
}

// 重攻击
void AZeldaPlayerCharacter::HeavyAttack()
{
	if (bIsAttacking || MovementState != EPlayerMovementState::Standing) return;
	
	AttackSequence.Add(EPlayerAttack::Heavy);
	
	bIsAttacking = true;
	OnExecuteAttack("");
	
	GetWorldTimerManager().SetTimer(TimerHandle_ResetCombo, this, &ThisClass::ResetAttackSequence, ComboResetTime, false);
}

void AZeldaPlayerCharacter::DoMove(float Right, float Forward)
{
	if (GetController() != nullptr)
	{
		const FRotator Rotation = GetController()->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(ForwardDirection, Forward);
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
	if (AnimTable.Montage)
		PlayAnimMontage(AnimTable.Montage, 1, TEXT("1"));
}

void AZeldaPlayerCharacter::SwitchArmedState()
{
	bArmed = !bArmed;
	SwitchArmedStateOnServer(bArmed);
}

void AZeldaPlayerCharacter::SetMovementState(EPlayerMovementState NewState)
{
	MovementState = NewState;
}

void AZeldaPlayerCharacter::ResetAttackSequence()
{
	if (AttackSequence.Num() > 0)
	{
		AttackSequence.Empty();
		UE_LOG(LogZelda, Log, TEXT("Attack Sequence Cleared due to timeout."));
	}
}

void AZeldaPlayerCharacter::ArmedChanged()
{
	FZeldaCharacterAnimTable InAnimTable = GetAnimTable();

	if (InAnimTable.Montage)
	{
		PlayAnimMontage(InAnimTable.Montage, 1, bArmed ? TEXT("1") : TEXT("0"));
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

///
///
///
void AZeldaPlayerCharacter::OnRep_ArmedChanged()
{
	if (!HasAuthority())
	{
		
	}
}
// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CPCharacterPlayer.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Animation/AnimMontage.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Component/CPStatComponent.h"
#include "UI/CPPlayerHUD.h"
#include "GameMode/CPPlayerController.h"
#include "Instance/CPMonsterDelegateManager.h"


ACPCharacterPlayer::ACPCharacterPlayer()
{

	GetCharacterMovement()->GravityScale = 2.0f;
	GetCharacterMovement()->JumpZVelocity = 980.0f;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));	// CameraBoom ������Ʈ�� ������
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 500.0f;
	CameraBoom->bUsePawnControlRotation = true;
	CameraBoom->SetRelativeLocation(FVector(0.0f, 0.0f, 100.0f));

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));	// FollowCamera ������Ʈ�� ������
	Camera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	Camera->bUsePawnControlRotation = false;
	Camera->FieldOfView = 80.0f;

	AttackRate = 1.0f;

	StatComponent = CreateDefaultSubobject<UCPStatComponent>(TEXT("StatComponent"));

	bCanHit = true;
	HitDelay = 0.2f;
}

void ACPCharacterPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);

	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ACPCharacterPlayer::Move);
	EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ACPCharacterPlayer::Look);
	EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Triggered, this, &ACPCharacterPlayer::Attack);
}

void ACPCharacterPlayer::TakeDamage(float Damage, EHitReactionType HitReactionType, FVector AttackDir)
{
	/*if (GetCharacterMovement()->MovementMode == EMovementMode::MOVE_None)
	{
		GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
	}*/

	if (!bCanHit)
	{
		return;
	}

	StatComponent->SetCurrentHP(-Damage);
	HitReaction(HitReactionType, AttackDir);

	bCanHit = false;

	GetWorld()->GetTimerManager().SetTimer(HitDelayTimer, this, &ACPCharacterPlayer::SetCanHit, HitDelay, false);
}

void ACPCharacterPlayer::Attack(FName SocketName, float AttackRange)
{

}

UCPStatComponent* ACPCharacterPlayer::GetStatComponent()
{
	return StatComponent.Get();
}

void ACPCharacterPlayer::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	StatComponent->DeadEvent.BindUObject(this, &ACPCharacterPlayer::Dead);

}

void ACPCharacterPlayer::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PlayerController = CastChecked<APlayerController>(GetController());
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}

	ACPPlayerController* CPPlayerController = Cast<ACPPlayerController>(GetController());
	if (CPPlayerController)
	{
		StatComponent->SetHPWidget(CPPlayerController->HUD.Get());
		StatComponent->InitializeStat(100.0f, 10.0f);
	}

	UCPMonsterDelegateManager* MonsterDelegateManager = GetGameInstance<UCPMonsterDelegateManager>();
	MonsterDelegateManager->SetPlayer(CPPlayerController);
	MonsterDelegateManager->SetDelegate();

	/*HUD->AddToViewport();

	StatComponent->SetHPWidget(HUD.Get());
	*/
}

void ACPCharacterPlayer::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(ForwardDirection, MovementVector.X);
	AddMovementInput(RightDirection, MovementVector.Y);
}

void ACPCharacterPlayer::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	AddControllerYawInput(LookAxisVector.X);
	AddControllerPitchInput(LookAxisVector.Y);
}

void ACPCharacterPlayer::Attack()
{
	UE_LOG(LogTemp, Log, TEXT("Attack"));

	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);

	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (!AnimInstance->Montage_IsPlaying(AttackMontage))
	{
		AnimInstance->Montage_Play(AttackMontage, AttackRate);

		FOnMontageEnded AttackMontageEnded;
		AttackMontageEnded.BindUObject(this, &ACPCharacterPlayer::AttackEnded);
		AnimInstance->Montage_SetEndDelegate(AttackMontageEnded, AttackMontage);
	}
}

void ACPCharacterPlayer::AttackEnded(UAnimMontage* Montage, bool IsProperlyEnded)
{
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
}

void ACPCharacterPlayer::SetCanHit()
{
	bCanHit = true;
	UE_LOG(LogTemp, Warning, TEXT("Can Hit"));
}

void ACPCharacterPlayer::Dead()
{
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
}

void ACPCharacterPlayer::HitReaction(EHitReactionType HitReactionType, FVector AttackDir)
{
	switch (HitReactionType)
	{
		case EHitReactionType::Flinch:
		{

			break;
		}
		case EHitReactionType::Knockback:
		{
			if (GetCharacterMovement()->MovementMode == EMovementMode::MOVE_Falling)
			{
				LaunchCharacter(AttackDir/4.0f, true, true);
			}
			else
			{
				LaunchCharacter(AttackDir, true, true);
			}

			
			break;
		}
		case EHitReactionType::Downed:
		{

			break;
		}
		default:
		{
			break;
		}
	}
}

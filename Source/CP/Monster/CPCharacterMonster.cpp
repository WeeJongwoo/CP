// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/CPCharacterMonster.h"
#include "AI/CPAIController.h"
#include "GameFramework/CharacterMovementComponent.h"


// Sets default values
ACPCharacterMonster::ACPCharacterMonster()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -100.0f), FRotator(0.0f, -90.0f, 0.0f));

	AIControllerClass = ACPAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 270.0f, 0.f);

	AttackSpeed = 1.0f;

}

// Called when the game starts or when spawned
void ACPCharacterMonster::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACPCharacterMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


const float ACPCharacterMonster::GetAIPatrolRadius()
{
	return 1000.0f;
}

const float ACPCharacterMonster::GetAIDetectRange()
{
	return 1500.f;
}

const float ACPCharacterMonster::GetAIAttackRange()
{
	return 500.0f;
}

const float ACPCharacterMonster::GetAIAttackSpeed()
{
	return AttackSpeed;
}

EAttackReturnType ACPCharacterMonster::Attack(EAttackType InAttackType)
{
	if (AttackActionMontage == nullptr)
	{
		return EAttackReturnType::Error;
	}

	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);

	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	float AnimPlayRate = GetAIAttackSpeed();

	if (InAttackType == EAttackType::Dead)
	{
		AnimInstance->Montage_JumpToSection(TEXT("Dead"), AttackActionMontage);

		ACPAIController* MonsterController = Cast<ACPAIController>(GetController());
		if (MonsterController)
		{
			MonsterController->StopAI();
		}
		AnimInstance->Montage_Play(AttackActionMontage, AnimPlayRate);

		return EAttackReturnType::Error;
	}

	uint8 AttackType = static_cast<uint8>(InAttackType);
	FString AttackSection = TEXT("Attack") + FString::FromInt(AttackType);

	UE_LOG(LogTemp, Log, TEXT("Attack Section: %s"), *AttackSection);

	AnimInstance->Montage_Play(AttackActionMontage, AnimPlayRate);
	AnimInstance->Montage_JumpToSection(*AttackSection, AttackActionMontage);

	FOnMontageEnded AttackEndElegate;
	AttackEndElegate.BindUObject(this, &ACPCharacterMonster::AttackEnd);
	AnimInstance->Montage_SetEndDelegate(AttackEndElegate, AttackActionMontage);

	return EAttackReturnType::Hit;
}

UAnimMontage* ACPCharacterMonster::GetAttackMontage()
{
	return AttackActionMontage;
}

UCharacterMovementComponent* ACPCharacterMonster::GetMonsterMovement()
{
	return GetCharacterMovement();
}

UAnimInstance* ACPCharacterMonster::GetMonsterAnimInstnce()
{
	return GetMesh()->GetAnimInstance();
}

void ACPCharacterMonster::AttackEnd(UAnimMontage* Montage, bool IsProperlyEnded)
{
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
}


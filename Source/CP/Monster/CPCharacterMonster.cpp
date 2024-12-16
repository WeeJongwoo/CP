// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/CPCharacterMonster.h"
#include "AI/CPAIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/BoxComponent.h"


// Sets default values
ACPCharacterMonster::ACPCharacterMonster()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MonsterMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/Animation/untitled.untitled'"));
	if (MonsterMesh.Object)
	{
		GetMesh()->SetSkeletalMesh(MonsterMesh.Object);
	}

	GetMesh()->SetRelativeLocationAndRotation(FVector(-60.0f, 0.0f, -100.0f), FRotator(0.0f, -90.0f, 0.0f));

	AIControllerClass = ACPAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 270.0f, 0.f);

	AttackSpeed = 1.0f;

	LeftHandTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("LeftHandTrigger"));
	LeftHandTrigger->SetupAttachment(GetMesh(), TEXT("LeftHand"));
	LeftHandTrigger->SetBoxExtent(FVector(100.0f, 100.0f, 100.0f));
	LeftHandTrigger->SetCollisionProfileName(TEXT("EnemyAttackTrigger"));

	RightHandTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("RightHandTrigger"));
	RightHandTrigger->SetupAttachment(GetMesh(), TEXT("RightHand"));
	RightHandTrigger->SetBoxExtent(FVector(100.0f, 100.0f, 100.0f));
	RightHandTrigger->SetCollisionProfileName(TEXT("EnemyAttackTrigger"));

	LeftWingTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("LeftWingTrigger"));
	LeftWingTrigger->SetupAttachment(GetMesh(), TEXT("LeftWing"));
	LeftWingTrigger->SetBoxExtent(FVector(100.0f, 100.0f, 100.0f));
	LeftWingTrigger->SetCollisionProfileName(TEXT("EnemyAttackTrigger"));

	RightWingTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("RightWingTrigger"));
	RightWingTrigger->SetupAttachment(GetMesh(), TEXT("RightWing"));
	RightWingTrigger->SetBoxExtent(FVector(100.0f, 100.0f, 100.0f));
	RightWingTrigger->SetCollisionProfileName(TEXT("EnemyAttackTrigger"));

	TailTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TailTrigger"));
	TailTrigger->SetupAttachment(GetMesh(), TEXT("Tail"));
	TailTrigger->SetBoxExtent(FVector(100.0f, 100.0f, 100.0f));
	TailTrigger->SetCollisionProfileName(TEXT("EnemyAttackTrigger"));


	LeftHandTrigger->SetHiddenInGame(false);
	RightHandTrigger->SetHiddenInGame(false);
	LeftWingTrigger->SetHiddenInGame(false);
	RightWingTrigger->SetHiddenInGame(false);
	TailTrigger->SetHiddenInGame(false);
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

void ACPCharacterMonster::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	LeftHandTrigger->OnComponentBeginOverlap.AddDynamic(this, &ACPCharacterMonster::LHandAttackHit);
	RightHandTrigger->OnComponentBeginOverlap.AddDynamic(this, &ACPCharacterMonster::RHandAttackHit);
	LeftWingTrigger->OnComponentBeginOverlap.AddDynamic(this, &ACPCharacterMonster::LWingAttackHit);
	RightWingTrigger->OnComponentBeginOverlap.AddDynamic(this, &ACPCharacterMonster::RWingAttackHit);
	TailTrigger->OnComponentBeginOverlap.AddDynamic(this, &ACPCharacterMonster::TailAttackHit);


	LeftHandTrigger->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RightHandTrigger->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	LeftWingTrigger->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RightWingTrigger->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	TailTrigger->SetCollisionEnabled(ECollisionEnabled::NoCollision);
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

uint8 ACPCharacterMonster::GetMaxAttakType()
{
	return 5;
}

void ACPCharacterMonster::AttackTriggerOn(AttackTriggerType InAttackTriggerType)
{
	switch (InAttackTriggerType)
	{
	case AttackTriggerType::LHand:
		LeftHandTrigger->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		break;
	case AttackTriggerType::RHand:
		RightHandTrigger->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		break;
	case AttackTriggerType::LWing:
		LeftWingTrigger->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		break;
	case AttackTriggerType::RWing:
		RightWingTrigger->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		break;
	case AttackTriggerType::Tail:
		TailTrigger->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		break;
	default:
		break;
	}
}

void ACPCharacterMonster::AttackTriggerOff(AttackTriggerType InAttackTriggerType)
{
	switch (InAttackTriggerType)
	{
	case AttackTriggerType::LHand:
		LeftHandTrigger->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		
		break;
	case AttackTriggerType::RHand:
		RightHandTrigger->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		
		break;
	case AttackTriggerType::LWing:
		LeftWingTrigger->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		
		break;
	case AttackTriggerType::RWing:
		RightWingTrigger->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		
		break;
	case AttackTriggerType::Tail:
		TailTrigger->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		break;
	default:
		break;
	}
}

void ACPCharacterMonster::LHandAttackHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("LHand"));
}

void ACPCharacterMonster::RHandAttackHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("RHand"));
}

void ACPCharacterMonster::LWingAttackHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("LWing"));
}

void ACPCharacterMonster::RWingAttackHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("RWing"));
}

void ACPCharacterMonster::TailAttackHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Tail"));
}

uint8 ACPCharacterMonster::GetMinAttakType()
{
	return 1;
}

void ACPCharacterMonster::AttackEnd(UAnimMontage* Montage, bool IsProperlyEnded)
{
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
}


// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_AttackPlayer.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Interface/CPMonsterAIInterface.h"
#include "Math/UnrealMathUtility.h"

UBTTask_AttackPlayer::UBTTask_AttackPlayer()
{
}

EBTNodeResult::Type UBTTask_AttackPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

//Basic Val
	APawn* AIPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (AIPawn == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Attack: Not Found AIPawn"));
		return EBTNodeResult::Failed;
	}
	ICPMonsterAIInterface* AIMonster = Cast<ICPMonsterAIInterface>(AIPawn);
	if (AIMonster == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Attack: AIPawn Is Not Monster"));
	}
//Set Attack Type
	uint8 MinAttackType = static_cast<uint8>(EAttackType::Attack1);
	uint8 MaxAttackType = static_cast<uint8>(EAttackType::Attack5);

	uint8 AttackTypeInt = FMath::RandRange(MinAttackType, MaxAttackType);
	UE_LOG(LogTemp, Log, TEXT("%d"), AttackTypeInt);

	EAttackType AttackType = static_cast<EAttackType>(AttackTypeInt);

//Play Attack Anim
	AIMonster->GetMonsterMovement()->SetMovementMode(EMovementMode::MOVE_None);
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("bIsAttacking"), true);
	UAnimMontage* AttackMontage = AIMonster->GetAttackMontage();
	if (AttackMontage == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	UAnimInstance* AnimInstance = AIMonster->GetMonsterAnimInstnce();
	if (AnimInstance == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	float AttackSpeed = AIMonster->GetAIAttackSpeed();

	FString AttackSection = TEXT("Attack") + FString::FromInt(AttackTypeInt);

	UE_LOG(LogTemp, Log, TEXT("Attack Section: %s"), *AttackSection);

	AnimInstance->Montage_Play(AttackMontage, AttackSpeed);
	AnimInstance->Montage_JumpToSection(*AttackSection, AttackMontage);
//Set End Delegate
	FOnMontageEnded AttackEndElegate;
	AttackEndElegate.BindLambda([this, AIMonster, &OwnerComp](UAnimMontage* InAnimMontage, bool bInterrupted) {
		AIMonster->GetMonsterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("bIsAttacking"), false);
	});
	AnimInstance->Montage_SetEndDelegate(AttackEndElegate, AttackMontage);

	return EBTNodeResult::InProgress;
}

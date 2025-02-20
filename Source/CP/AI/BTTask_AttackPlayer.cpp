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
	if (!IsValid(AIPawn))
	{
		UE_LOG(LogTemp, Warning, TEXT("Attack: Not Found AIPawn"));
		return EBTNodeResult::Failed;
	}
	ICPMonsterAIInterface* AIMonster = Cast<ICPMonsterAIInterface>(AIPawn);
	if (AIMonster == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Attack: AIPawn Is Not Monster"));
		return EBTNodeResult::Failed;
	}
//Set Attack Type
	uint8 MinAttackType = AIMonster->GetMinAttakType();
	uint8 MaxAttackType = AIMonster->GetMaxAttakType();

	uint8 AttackTypeInt = FMath::RandRange(MinAttackType, MaxAttackType);
	UE_LOG(LogTemp, Log, TEXT("%d"), AttackTypeInt);

//Play Attack Anim
	AIMonster->GetMonsterMovement()->SetMovementMode(EMovementMode::MOVE_None);
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("bIsAttacking"), true);
	UAnimMontage* AttackMontage = AIMonster->GetAttackMontage();
	if (!IsValid(AttackMontage))
	{
		return EBTNodeResult::Failed;
	}
	UAnimInstance* AnimInstance = AIMonster->GetMonsterAnimInstnce();
	if (!IsValid(AnimInstance))
	{
		return EBTNodeResult::Failed;
	}
	const float AttackSpeed = AIMonster->GetAIAttackSpeed();

	FString AttackSection = FString::Printf(TEXT("Attack %d"), AttackTypeInt);
		//TEXT("Attack") + FString::FromInt(AttackTypeInt);

	UE_LOG(LogTemp, Log, TEXT("Attack Section: %s"), *AttackSection);

	AnimInstance->Montage_Play(AttackMontage, AttackSpeed);
	AnimInstance->Montage_JumpToSection(*AttackSection, AttackMontage);

//Set End Delegate
	FOnMontageEnded AttackEndElegate;

	TWeakObjectPtr<UBTTask_AttackPlayer> WeakThis = this;

	AttackEndElegate.BindLambda([WeakThis, AIMonster, &OwnerComp](UAnimMontage* InAnimMontage, bool bInterrupted) {
		if (!WeakThis.IsValid())
		{
			return;
		}
		AIMonster->GetMonsterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
		WeakThis->FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("bIsAttacking"), false);
	});
	AnimInstance->Montage_SetEndDelegate(AttackEndElegate, AttackMontage);

	return EBTNodeResult::InProgress;
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTService_AttackRangeCheck.h"
#include "AIController.h"
#include "Interface/CPMonsterAIInterface.h"
#include "Engine/OverlapResult.h"
#include "Math/UnrealMathUtility.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_AttackRangeCheck::UBTService_AttackRangeCheck()
{
	NodeName = TEXT("AttackRangeCheck");
	Interval = 0.001;
}

void UBTService_AttackRangeCheck::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* AIPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (AIPawn == nullptr)
	{
		return;
	}                                                                                                                                  

	ICPMonsterAIInterface* AIMonster = Cast<ICPMonsterAIInterface>(AIPawn);
	if (AIMonster == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("AttackRange: AIPawn Is Not Monster"));
		return;
	}

	FVector ActorLocation = AIPawn->GetActorLocation();
	float AttackRange = AIMonster->GetAIAttackRange();

	APawn* Target = Cast<APawn>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TEXT("Target")));
	if (Target == nullptr)
	{
		return;
	}

	FVector DistanceVector = Target->GetActorLocation() - ActorLocation;
	float Distance = DistanceVector.Length();

	UWorld* World = AIPawn->GetWorld();

	bool bResult = (AttackRange >= Distance);

	/*TArray<FOverlapResult> DetectOverlapResult;
	FCollisionQueryParams DetectCollisionQueryParams(SCENE_QUERY_STAT(Detect), false, AIPawn);
	bool bResult = World->OverlapMultiByChannel(
		DetectOverlapResult,
		ActorLocation,
		FQuat::Identity,
		ECC_GameTraceChannel1,
		FCollisionShape::MakeSphere(AttackRange),
		DetectCollisionQueryParams
	);

	if (bResult)
	{
		int32 TargetIndex = FMath::RandRange(1, DetectOverlapResult.Num());
		APawn* HitPawn = Cast<APawn>(DetectOverlapResult[TargetIndex - 1].GetActor());
		if (HitPawn)
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsObject(TEXT("Target"), HitPawn);
		}
	}*/

	OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("bCanAttack"), bResult);

}

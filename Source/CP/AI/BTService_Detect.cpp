// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTService_Detect.h"
#include "AIController.h"
#include "Interface/CPMonsterAIInterface.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/OverlapResult.h"

UBTService_Detect::UBTService_Detect()
{
	NodeName = TEXT("Detect");
	//Interval = 0.5f //�⺻ ���� 0.5��
}

void UBTService_Detect::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (ControllingPawn == nullptr)
	{
		return;
	}

	FVector Center = ControllingPawn->GetActorLocation();
	UWorld* World = ControllingPawn->GetWorld();
	if (World == nullptr)
	{
		return;
	}

	ICPMonsterAIInterface* AIMonster = Cast<ICPMonsterAIInterface>(ControllingPawn);
	if (AIMonster == nullptr)
	{
		return;
	}

	float DetectRange = AIMonster->GetAIDetectRange();

	TArray<FOverlapResult> DetectOverlapResult;
	FCollisionQueryParams DetectCollisionQueryParams(SCENE_QUERY_STAT(Detect), false, ControllingPawn);
	bool bResult = World->OverlapMultiByChannel(
		DetectOverlapResult, 
		Center, 
		FQuat::Identity, 
		ECC_GameTraceChannel1, 
		FCollisionShape::MakeSphere(DetectRange), 
		DetectCollisionQueryParams
	);

	if (bResult)
	{
		for (auto& OverlapResult : DetectOverlapResult)
		{
			APawn* HitPawn = Cast<APawn>(OverlapResult.GetActor());
			if (HitPawn && HitPawn->GetController()->IsPlayerController())
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsObject(TEXT("Target"), HitPawn);
				DrawDebugSphere(World, Center, DetectRange, 16, FColor::Green, false, 1.0f);

				return;
			}
		}
	}

	OwnerComp.GetBlackboardComponent()->SetValueAsObject(TEXT("Target"), nullptr);
	DrawDebugSphere(World, Center, DetectRange, 16, FColor::Red, false, 1.0f);
}

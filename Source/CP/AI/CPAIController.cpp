// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/CPAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

ACPAIController::ACPAIController()
{
	bAllowTickBeforeBeginPlay = true;

	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBAssetRef(TEXT("/Script/AIModule.BlackboardData'/Game/AI/BB_CPAcates.BB_CPAcates'"));
	if (BBAssetRef.Object)
	{
		BBAsset = BBAssetRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTAssetRef(TEXT("/Script/AIModule.BehaviorTree'/Game/AI/BT_CPAcates.BT_CPAcates'"));
	if (BTAssetRef.Object)
	{
		BTAsset = BTAssetRef.Object;
	}
}

void ACPAIController::RunAI()
{
	UBlackboardComponent* BlackboradPtr = Blackboard.Get();
	if (UseBlackboard(BBAsset, BlackboradPtr))
	{
		Blackboard->SetValueAsVector(TEXT("CurrentPos"), GetPawn()->GetActorLocation());

		bool RunResult = RunBehaviorTree(BTAsset);
		ensure(RunResult);
	}

}

void ACPAIController::StopAI()
{
	UBehaviorTreeComponent* BTComponent = Cast<UBehaviorTreeComponent>(BrainComponent);
	if (BTComponent)
	{
		BTComponent->StopTree();
	}
}

void ACPAIController::Tick(float DeltaTime)
{
	Blackboard->SetValueAsVector(TEXT("ForwardDirction"), GetPawn()->GetActorForwardVector());
}

void ACPAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	RunAI();
}

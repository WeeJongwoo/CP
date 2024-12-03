// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNode_LookAtTarget.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTaskNode_LookAtTarget::UBTTaskNode_LookAtTarget()
{
    RotationSpeed = 1.0f;
}

EBTNodeResult::Type UBTTaskNode_LookAtTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    APawn* AIPawn = OwnerComp.GetAIOwner()->GetPawn();
    if (AIPawn == nullptr)
    {
        return EBTNodeResult::Failed;
    }

    APawn* Target = Cast<APawn>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TEXT("Target")));
    if (Target == nullptr)
    {
        return EBTNodeResult::Failed;
    }

    FVector TargetLocation = Target->GetActorLocation();
    FRotator DesiredRotation = (TargetLocation - AIPawn->GetActorLocation()).Rotation();
    FRotator NewRotation = FMath::RInterpTo(AIPawn->GetActorRotation(), DesiredRotation, GetWorld()->DeltaTimeSeconds, RotationSpeed);

    AIPawn->SetActorRotation(NewRotation);

    return EBTNodeResult::Succeeded;
}

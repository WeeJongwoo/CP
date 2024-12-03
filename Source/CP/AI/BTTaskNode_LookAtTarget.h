// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskNode_LookAtTarget.generated.h"

/**
 * 
 */
UCLASS()
class CP_API UBTTaskNode_LookAtTarget : public UBTTaskNode
{
	GENERATED_BODY()
	
	
public:
	UBTTaskNode_LookAtTarget();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
protected:

	UPROPERTY(EditAnywhere)
	float RotationSpeed;
};

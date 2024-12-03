// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_AttackRangeCheck.generated.h"

/**
 * 
 */
UCLASS()
class CP_API UBTService_AttackRangeCheck : public UBTService
{
	GENERATED_BODY()
	
	
public:
	UBTService_AttackRangeCheck();

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
};

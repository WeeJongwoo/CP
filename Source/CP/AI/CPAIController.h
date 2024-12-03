// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "CPAIController.generated.h"

/**
 * 
 */
UCLASS()
class CP_API ACPAIController : public AAIController
{
	GENERATED_BODY()
public:
	ACPAIController();

	void RunAI();
	void StopAI();

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void OnPossess(APawn* InPawn) override;

private:

	TObjectPtr<class UBlackboardData> BBAsset;

	TObjectPtr<class UBehaviorTree> BTAsset;

	
};

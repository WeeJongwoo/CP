// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"

#include "CPAttackTrigger.generated.h"

enum class AttackTriggerType : uint8 {
	LHand,
	RHand,
	LWing,
	RWing,
	Tail
};

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UCPAttackTrigger : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class CP_API ICPAttackTrigger
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	
	virtual void AttackTriggerOn(AttackTriggerType InAttackTriggerType) = 0;
	virtual void AttackTriggerOff(AttackTriggerType InAttackTriggerType) = 0;
};

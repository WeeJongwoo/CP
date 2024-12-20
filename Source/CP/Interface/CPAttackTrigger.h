// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"

#include "CPAttackTrigger.generated.h"

enum class EAttackTriggerType : uint8 {
	LHand,
	RHand,
	LWing,
	RWing,
	Tail,

	Weapon
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
	
	virtual void AttackTriggerOn(EAttackTriggerType InAttackTriggerType) = 0;
	virtual void AttackTriggerOff(EAttackTriggerType InAttackTriggerType) = 0;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "CPMonsterAIInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UCPMonsterAIInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
enum class EAttackType : uint8
{
	Attack1 = 1,
	Attack2,
	Attack3,
	Attack4,
	Attack5,
	Attack6,
	Attack7,
	Attack8,
	Attack9,


	Dead = 99
};

enum class EAttackReturnType : uint8
{
	False = 0,
	Hit,

	Error = 99
};


class CP_API ICPMonsterAIInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	
	virtual const float GetAIPatrolRadius() = 0;
	virtual const float GetAIDetectRange() = 0;
	virtual const float GetAIAttackRange() = 0;
	virtual const float GetAIAttackSpeed() = 0;

	virtual EAttackReturnType Attack(EAttackType InAttackType) = 0;

	virtual UAnimMontage* GetAttackMontage() = 0;
	virtual UCharacterMovementComponent* GetMonsterMovement() = 0;
	virtual UAnimInstance* GetMonsterAnimInstnce() = 0;
};

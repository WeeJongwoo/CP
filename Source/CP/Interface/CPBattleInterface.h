// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Component/CPStatComponent.h"

#include "CPBattleInterface.generated.h"

enum class EHitReactionType : uint8 {
	Flinch,     // 1. ¿òÂñ
	Knockback,
	Downed
};

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UCPBattleInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class CP_API ICPBattleInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual void TakeDamage(float Damage, EHitReactionType HitReactionType, FVector AttackDir) = 0;
	virtual void Attack(FName SocketName, float AttackRange) = 0;
	virtual UCPStatComponent* GetStatComponent() = 0;

};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/CPMonsterAIInterface.h"
#include "CPCharacterMonster.generated.h"

UCLASS()
class CP_API ACPCharacterMonster : public ACharacter, public ICPMonsterAIInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACPCharacterMonster();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual const float GetAIPatrolRadius() override;
	virtual const float GetAIDetectRange() override;
	virtual const float GetAIAttackRange() override;
	virtual const float GetAIAttackSpeed() override;

	virtual EAttackReturnType Attack(EAttackType AttackType) override;

	virtual UAnimMontage* GetAttackMontage() override;
	virtual UCharacterMovementComponent* GetMonsterMovement() override;
	virtual UAnimInstance* GetMonsterAnimInstnce() override;

protected:

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UAnimMontage> AttackActionMontage;

	float AttackSpeed;
	
	void AttackEnd(UAnimMontage* Montage, bool IsProperlyEnded);
};

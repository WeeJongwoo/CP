// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/CPMonsterAIInterface.h"
#include "Interface/CPAttackTrigger.h"
#include "CPCharacterMonster.generated.h"

UCLASS()
class CP_API ACPCharacterMonster : public ACharacter, public ICPMonsterAIInterface, public ICPAttackTrigger
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

	virtual void PostInitializeComponents() override;

	virtual EAttackReturnType Attack(EAttackType AttackType) override;

	virtual UAnimMontage* GetAttackMontage() override;
	virtual UCharacterMovementComponent* GetMonsterMovement() override;
	virtual UAnimInstance* GetMonsterAnimInstnce() override;

	virtual uint8 GetMinAttakType() override;
	virtual uint8 GetMaxAttakType() override;

	virtual void AttackTriggerOn(AttackTriggerType InAttackTriggerType) override;
	virtual void AttackTriggerOff(AttackTriggerType InAttackTriggerType) override;

	UFUNCTION()
	void LHandAttackHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void RHandAttackHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void LWingAttackHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void RWingAttackHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void TailAttackHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
protected:

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UAnimMontage> AttackActionMontage;

	float AttackSpeed;
	
	void AttackEnd(UAnimMontage* Montage, bool IsProperlyEnded);

	TObjectPtr<class USkeletalMesh> Mesh;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UBoxComponent> LeftHandTrigger;
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UBoxComponent> RightHandTrigger;
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UBoxComponent> LeftWingTrigger;
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UBoxComponent> RightWingTrigger;
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UBoxComponent> TailTrigger;

};

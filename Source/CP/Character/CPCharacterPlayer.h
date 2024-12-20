// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/CPCharacterBase.h"
#include "InputActionValue.h"
#include "Interface/CPBattleInterface.h"
#include "CPCharacterPlayer.generated.h"

/**
 * 
 */
UCLASS()
class CP_API ACPCharacterPlayer : public ACPCharacterBase, public ICPBattleInterface
{
	GENERATED_BODY()
	
public:
	ACPCharacterPlayer();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void TakeDamage(float Damage, EHitReactionType HitReactionType, FVector AttackDir) override;
	virtual void Attack(FName SocketName, float AttackRange) override;
	virtual UCPStatComponent* GetStatComponent() override;

	virtual void PostInitializeComponents() override;

protected:

	virtual void BeginPlay() override;

// Input
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputMappingContext> DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> AttackAction;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Attack();
	void AttackEnded(class UAnimMontage* Montage, bool IsProperlyEnded);

// Camera
	UPROPERTY(EditAnywhere, Category = Camera, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USpringArmComponent> CameraBoom;

	UPROPERTY(EditAnywhere, Category = Camera, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCameraComponent> Camera;


// Attack

	float AttackRate;

	float HitDelay;
	bool bCanHit;

	FTimerHandle HitDelayTimer;

	UPROPERTY(EditAnywhere, Category = Anim)
	TObjectPtr<class UAnimMontage> AttackMontage;

	void SetCanHit();

//stat
	UPROPERTY(EditAnywhere, Category = Stat)
	TObjectPtr<class UCPStatComponent> StatComponent;

	void Dead();

	void HitReaction(EHitReactionType HitReactionType, FVector AttackDir);
};

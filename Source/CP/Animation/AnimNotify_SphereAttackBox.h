// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_SphereAttackBox.generated.h"

/**
 * 
 */
UCLASS()
class CP_API UAnimNotify_SphereAttackBox : public UAnimNotify
{
	GENERATED_BODY()
	
public:

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

	UPROPERTY(EditAnywhere)
	float AttackRange;
	
	UPROPERTY(EditAnywhere)
	FName SocketName;
	
};

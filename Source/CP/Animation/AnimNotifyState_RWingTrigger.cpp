// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotifyState_RWingTrigger.h"
#include "Interface/CPAttackTrigger.h"

void UAnimNotifyState_RWingTrigger::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	ICPAttackTrigger* AttackTriggerOwner = Cast<ICPAttackTrigger>(MeshComp->GetOwner());
	if (AttackTriggerOwner)
	{
		AttackTriggerOwner->AttackTriggerOn(EAttackTriggerType::RWing);
	}
}

void UAnimNotifyState_RWingTrigger::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	ICPAttackTrigger* AttackTriggerOwner = Cast<ICPAttackTrigger>(MeshComp->GetOwner());
	if (AttackTriggerOwner)
	{
		AttackTriggerOwner->AttackTriggerOff(EAttackTriggerType::RWing);
	}
}

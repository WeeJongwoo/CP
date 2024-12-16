// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotifyState_LHandTrigger.h"
#include "Interface/CPAttackTrigger.h"

void UAnimNotifyState_LHandTrigger::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	ICPAttackTrigger* AttackTriggerOwner = Cast<ICPAttackTrigger>(MeshComp->GetOwner());
	if (AttackTriggerOwner)
	{
		AttackTriggerOwner->AttackTriggerOn(AttackTriggerType::LHand);
	}
}

void UAnimNotifyState_LHandTrigger::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	ICPAttackTrigger* AttackTriggerOwner = Cast<ICPAttackTrigger>(MeshComp->GetOwner());
	if (AttackTriggerOwner)
	{
		AttackTriggerOwner->AttackTriggerOff(AttackTriggerType::LHand);
	}
}

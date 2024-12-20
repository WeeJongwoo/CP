// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotifyState_TailTrigger.h"
#include "Interface/CPAttackTrigger.h"

void UAnimNotifyState_TailTrigger::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	ICPAttackTrigger* AttackTriggerOwner = Cast<ICPAttackTrigger>(MeshComp->GetOwner());
	if (AttackTriggerOwner)
	{
		AttackTriggerOwner->AttackTriggerOn(EAttackTriggerType::Tail);
	}
}

void UAnimNotifyState_TailTrigger::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	ICPAttackTrigger* AttackTriggerOwner = Cast<ICPAttackTrigger>(MeshComp->GetOwner());
	if (AttackTriggerOwner)
	{
		AttackTriggerOwner->AttackTriggerOff(EAttackTriggerType::Tail);
	}
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotifyState_LWingTrigger.h"
#include "Interface/CPAttackTrigger.h"

void UAnimNotifyState_LWingTrigger::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	ICPAttackTrigger* AttackTriggerOwner = Cast<ICPAttackTrigger>(MeshComp->GetOwner());
	if (AttackTriggerOwner)
	{
		AttackTriggerOwner->AttackTriggerOn(EAttackTriggerType::LWing);
	}
}

void UAnimNotifyState_LWingTrigger::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	ICPAttackTrigger* AttackTriggerOwner = Cast<ICPAttackTrigger>(MeshComp->GetOwner());
	if (AttackTriggerOwner)
	{
		AttackTriggerOwner->AttackTriggerOff(EAttackTriggerType::LWing);
	}
}

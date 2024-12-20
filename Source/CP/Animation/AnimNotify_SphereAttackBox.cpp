// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotify_SphereAttackBox.h"
#include "Interface/CPBattleInterface.h"


void UAnimNotify_SphereAttackBox::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	ICPBattleInterface* BattleActor = Cast<ICPBattleInterface>(MeshComp->GetOwner());
	if (BattleActor)
	{
		BattleActor->Attack(SocketName, AttackRange);
	}

}

// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/CPAnimNotifyState_WeaponAttack.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Interface/CPBattleInterface.h"


void UCPAnimNotifyState_WeaponAttack::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
}

void UCPAnimNotifyState_WeaponAttack::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	FVector StartPos = MeshComp->GetSocketLocation(TEXT("FX_weapon_base"));

	FVector EndPos = MeshComp->GetSocketLocation(TEXT("FX_weapon_tip"));

	UWorld* World = MeshComp->GetOwner()->GetWorld();

	DrawDebugSphere(World, StartPos, 5.0f, 10, FColor::Green, false, 2.0f);
	DrawDebugSphere(World, EndPos, 5.0f, 10, FColor::Green, false, 2.0f);

	FVector HitBoxHalfExtent = FVector(30.0f, 30.0f, 30.0f);

	FCollisionQueryParams CollisionParam(TEXT("Weapon Attack"), false, MeshComp->GetOwner());
	TArray<FHitResult> HitResults;
	bool bIsHit = World->SweepMultiByChannel(HitResults, StartPos, EndPos, FQuat::Identity, ECC_GameTraceChannel3, FCollisionShape::MakeBox(HitBoxHalfExtent), CollisionParam);
	if (bIsHit)
	{
		AActor* Owner = MeshComp->GetOwner();
		if (!IsValid(Owner))
		{
			return;
		}

		float magnitude = (EndPos - StartPos).Length();
		FVector Up = FVector::UpVector * magnitude;
		FVector Direction = (EndPos - StartPos + Up).GetSafeNormal();
		FVector Velocity = Direction * 500.0f;

		for (auto HitResult : HitResults)
		{
			AActor* HitActor = HitResult.GetActor();

			if (!IsValid(HitActor))
			{
				return;
			}

			ICPBattleInterface* HitCharacter = Cast<ICPBattleInterface>(HitActor);
			ICPBattleInterface* BattleOwner = Cast<ICPBattleInterface>(Owner);

			if (HitCharacter && BattleOwner)
			{
				UCPStatComponent* OwnerStatComp = BattleOwner->GetStatComponent();

				float ATK = OwnerStatComp->GetATK();
					
				HitCharacter->TakeDamage(ATK, EHitReactionType::Flinch, FVector::ZeroVector);

				UE_LOG(LogTemp, Warning, TEXT("Player Attack"));
			}
	
		}
	}

	FColor HitBoxColor = bIsHit ? FColor::Green : FColor::Red;
	FVector Center = StartPos + ((EndPos - StartPos) / 2.0f);
	DrawDebugBox(World, Center, HitBoxHalfExtent, HitBoxColor, false, 5.0f);
}

void UCPAnimNotifyState_WeaponAttack::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/CPStatComponent.h"
#include "UI/CPPlayerHUD.h"


// Sets default values for this component's properties
UCPStatComponent::UCPStatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	MaxHP = 100.0f;
	CurrentHp = MaxHP;
	ATK = 10.0f;
	bIsDead = false;
	// ...
}


// Called when the game starts
void UCPStatComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UCPStatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// ...
}

void UCPStatComponent::InitializeStat(float InMaxHP, float InATK)
{
	MaxHP = InMaxHP;
	CurrentHp = MaxHP;
	ATK = InATK;
	bIsDead = false;

	float HPPercent = CurrentHp / MaxHP;

	if (PlayerWidget)
	{
		PlayerWidget->SetPlayerHPBar(HPPercent);
	}
}


void UCPStatComponent::SetMaxHP(float NewMaxHP)
{
	if (NewMaxHP != 0)
	{
		MaxHP = NewMaxHP;
	}
}

void UCPStatComponent::SetATK(float NewATK)
{
	ATK = NewATK;
}

const float UCPStatComponent::GetATK()
{
	return ATK;
}

void UCPStatComponent::SetCurrentHP(float val)
{
	CurrentHp = FMath::Clamp(CurrentHp+val, 0.0f, MaxHP);

	float HPPercent = CurrentHp / MaxHP;

	if (PlayerWidget)
	{
		PlayerWidget->SetPlayerHPBar(HPPercent);
	}

	if (CurrentHp <= 0.0f)
	{
		bIsDead = true;

		if (DeadEvent.IsBound())
		{
			DeadEvent.Execute();
		}
	}
}

const float UCPStatComponent::GetCurrentHP()
{
	return CurrentHp;
}

void UCPStatComponent::SetHPWidget(UCPPlayerHUD* InPlayerWidget)
{
	PlayerWidget = InPlayerWidget;
}


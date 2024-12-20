// Fill out your copyright notice in the Description page of Project Settings.


#include "CPMonsterDelegateManager.h"
#include "Monster/CPCharacterMonster.h"
#include "GameMode/CPPlayerController.h"
#include "UI/CPPlayerHUD.h"

UCPMonsterDelegateManager::UCPMonsterDelegateManager()
{
}

void UCPMonsterDelegateManager::Init()
{
	Super::Init();
}

void UCPMonsterDelegateManager::SetMonster(ACPCharacterMonster* InMonster)
{
	Monster = InMonster;
}

void UCPMonsterDelegateManager::SetPlayer(ACPPlayerController* InPlayer)
{
	Player = InPlayer;
}

void UCPMonsterDelegateManager::SetDelegate()
{
	if (Monster && Player)
	{
		Monster->DeadDelegate.AddUObject(Player->HUD, &UCPPlayerHUD::Clear);
		UE_LOG(LogTemp, Log, TEXT("Set Delegate"));
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("Set Fail"));
}

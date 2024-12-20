// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "CPMonsterDelegateManager.generated.h"

/**
 * 
 */
UCLASS()
class CP_API UCPMonsterDelegateManager : public UGameInstance
{
	GENERATED_BODY()
	
	
public:

	UCPMonsterDelegateManager();

	virtual void Init() override;

	void SetMonster(class ACPCharacterMonster* InMonster);
	void SetPlayer(class ACPPlayerController* InPlayer);

	void SetDelegate();

private:

	TObjectPtr<class ACPCharacterMonster> Monster;

	TObjectPtr<class ACPPlayerController> Player;
	
};

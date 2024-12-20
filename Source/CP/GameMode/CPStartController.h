// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CPStartController.generated.h"

/**
 * 
 */
UCLASS()
class CP_API ACPStartController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ACPStartController();

	virtual void BeginPlay() override;

private:

	TSubclassOf<class UUserWidget> HUDClass;

	TObjectPtr<class UUserWidget> HUD;
	
	
};

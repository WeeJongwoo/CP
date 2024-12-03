// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CPPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class CP_API ACPPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ACPPlayerController();

protected:

	virtual void BeginPlay() override;
	
	
};

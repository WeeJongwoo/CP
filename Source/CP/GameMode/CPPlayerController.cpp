// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/CPPlayerController.h"

ACPPlayerController::ACPPlayerController()
{
}

void ACPPlayerController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeGameOnly InputMode;
	SetInputMode(InputMode);

}

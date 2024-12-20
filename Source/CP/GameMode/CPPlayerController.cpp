// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/CPPlayerController.h"
#include "UI/CPPlayerHUD.h"

ACPPlayerController::ACPPlayerController()
{
	static ConstructorHelpers::FClassFinder<UCPPlayerHUD> HUDRef(TEXT("/Game/UI/WBP_PlayerHUD.WBP_PlayerHUD_C"));
	if (HUDRef.Class)
	{
		HUDClass = HUDRef.Class;
	}
}

const UCPPlayerHUD* ACPPlayerController::GetHUD()
{
	return HUD.Get();
}

void ACPPlayerController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeGameOnly InputMode;
	SetInputMode(InputMode);

	HUD = CreateWidget<UCPPlayerHUD>(this, HUDClass);
	if (HUD)
	{
		HUD->AddToViewport();
	}

}

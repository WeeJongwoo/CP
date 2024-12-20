// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/CPStartController.h"
#include "UI/CPStartHUD.h"

ACPStartController::ACPStartController()
{
	static ConstructorHelpers::FClassFinder<UCPStartHUD> HUDRef(TEXT("/Game/UI/WBP_Start.WBP_Start_C"));
	if (HUDRef.Class)
	{
		HUDClass = HUDRef.Class;
	}
}

void ACPStartController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeUIOnly StartInputMode;
	SetInputMode(StartInputMode);
	bShowMouseCursor = true;

	HUD = CreateWidget<UUserWidget>(this, HUDClass);
	UCPStartHUD* LobbyMenuWidget = Cast<UCPStartHUD>(HUD);
	if (LobbyMenuWidget)
	{
		HUD->AddToViewport();
	}
}

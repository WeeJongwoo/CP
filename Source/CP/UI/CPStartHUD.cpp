// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/CPStartHUD.h"
#include "CPStartWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

UCPStartHUD::UCPStartHUD(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UCPStartHUD::NativeConstruct()
{
	Super::NativeConstruct();

	if (WBP_StartButton && WBP_StartButton->GetButton())
	{
		UE_LOG(LogTemp, Log, TEXT("Start"));
		WBP_StartButton->GetButton()->OnClicked.AddDynamic(this, &UCPStartHUD::StartButtonClick);
	}

	if (WBP_ExitButton && WBP_ExitButton->GetButton())
	{
		WBP_ExitButton->GetButton()->OnClicked.AddDynamic(this, &UCPStartHUD::ExitButtonClick);
	}

}

void UCPStartHUD::StartButtonClick()
{
	UE_LOG(LogTemp, Log, TEXT("StartGame"));
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("Stage"));
}

void UCPStartHUD::ExitButtonClick()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), GetOwningPlayer(), EQuitPreference::Quit, true);
}

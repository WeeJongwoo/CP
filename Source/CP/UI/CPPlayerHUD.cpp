// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/CPPlayerHUD.h"
#include "Components/ProgressBar.h"
#include "CPHPBar.h"
#include "CPClearHUD.h"

UCPPlayerHUD::UCPPlayerHUD(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UCPPlayerHUD::SetPlayerHPBar(float Percent)
{
	WBP_HPBar->SetHPBar(Percent);
}

void UCPPlayerHUD::Clear()
{
	WBP_HPBar->SetVisibility(ESlateVisibility::Hidden);
	WBP_Clear->SetVisibility(ESlateVisibility::Visible);
}

void UCPPlayerHUD::NativeConstruct()
{
	Super::NativeConstruct();
}

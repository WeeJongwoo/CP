// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/CPClearHUD.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

UCPClearHUD::UCPClearHUD(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
}

void UCPClearHUD::NativeConstruct()
{
	Super::NativeConstruct();

	ClearText = Cast<UTextBlock>(GetWidgetFromName(TEXT("Clear")));
	check(ClearText);
	CountdownText = Cast<UTextBlock>(GetWidgetFromName(TEXT("Countdown")));
	check(CountdownText);

	CountdownNum = 5;

	OnVisibilityChanged.AddDynamic(this, &UCPClearHUD::SetCountdownTimer);

	SetVisibility(ESlateVisibility::Hidden);
}

void UCPClearHUD::SetCountdownTimer(ESlateVisibility InVisibility)
{
	if (InVisibility == ESlateVisibility::Visible)
	{
		GetWorld()->GetTimerManager().SetTimer(CountdownTimer, this, &UCPClearHUD::DecreasCount, 1.0f, true);
	}
}

void UCPClearHUD::DecreasCount()
{
	CountdownNum--;
	CountdownText->SetText(FText::FromString(FString::FromInt(CountdownNum)));

	if (CountdownNum <= 0)
	{
		UGameplayStatics::OpenLevel(GetWorld(), TEXT("StartMap"));
	}
}

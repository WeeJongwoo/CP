// Fill out your copyright notice in the Description page of Project Settings.


#include "CPHPBar.h"
#include "Components/ProgressBar.h"

UCPHPBar::UCPHPBar(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
}

void UCPHPBar::SetHPBar(float Percent)
{
	HPBar->SetPercent(Percent);
}

void UCPHPBar::NativeConstruct()
{
	Super::NativeConstruct();

	HPBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("HPBar")));
	check(HPBar);
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/CPStartWidget.h"
#include "Components/Button.h"

UCPStartWidget::UCPStartWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UCPStartWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Button = Cast<UButton>(GetWidgetFromName(TEXT("Button")));
}

UButton* UCPStartWidget::GetButton()
{
	return Button.Get();
}

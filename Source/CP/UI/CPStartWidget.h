// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CPStartWidget.generated.h"

/**
 * 
 */
UCLASS()
class CP_API UCPStartWidget : public UUserWidget
{
	GENERATED_BODY()
	
	
public:
	UCPStartWidget(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;

	class UButton* GetButton();

	UPROPERTY(VisibleAnywhere, Category = Button, meta = (BindWidget))
	TObjectPtr<class UButton> Button;
	
};

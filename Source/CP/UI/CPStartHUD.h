// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CPStartHUD.generated.h"

/**
 * 
 */
UCLASS()
class CP_API UCPStartHUD : public UUserWidget
{
	GENERATED_BODY()
	
	
public:
	UCPStartHUD(const FObjectInitializer& ObjectInitializer);

protected:

	virtual void NativeConstruct() override;

	UPROPERTY(VisibleAnywhere, Category = Button, meta = (BindWidget))
	TObjectPtr<class UCPStartWidget> WBP_StartButton;
	
	UPROPERTY(VisibleAnywhere, Category = Button, meta = (BindWidget))
	TObjectPtr<class UCPStartWidget> WBP_ExitButton;

	UFUNCTION()
	void StartButtonClick();

	UFUNCTION()
	void ExitButtonClick();
};

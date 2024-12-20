// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CPClearHUD.generated.h"

/**
 * 
 */
UCLASS()
class CP_API UCPClearHUD : public UUserWidget
{
	GENERATED_BODY()
	
	
public:

	UCPClearHUD(const FObjectInitializer& ObjectInitializer);

protected:

	virtual void NativeConstruct() override;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UTextBlock> ClearText;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UTextBlock> CountdownText;

	UFUNCTION()
	void SetCountdownTimer(ESlateVisibility InVisibility);

	void DecreasCount();

	FTimerHandle CountdownTimer;
	int32 CountdownNum;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CPHPBar.generated.h"

/**
 * 
 */
UCLASS()
class CP_API UCPHPBar : public UUserWidget
{
	GENERATED_BODY()
	
	
public:

	UCPHPBar(const FObjectInitializer& ObjectInitializer);

	void SetHPBar(float Percent);

protected:

	virtual void NativeConstruct() override;

	UPROPERTY(VisibleAnywhere, Category = HP, meta = (BindWidget))
	TObjectPtr<class UProgressBar> HPBar;
	
};

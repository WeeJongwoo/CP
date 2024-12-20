// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CPPlayerHUD.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FUpdateHUDDelegate, float)

/**
 * 
 */
UCLASS()
class CP_API UCPPlayerHUD : public UUserWidget
{
	GENERATED_BODY()

public:

	UCPPlayerHUD(const FObjectInitializer& ObjectInitializer);

	void SetPlayerHPBar(float Percent);

	void Clear();

protected:

	virtual void NativeConstruct() override;

	UPROPERTY(VisibleAnywhere, Category = HP, meta = (BindWidget))
	TObjectPtr<class UCPHPBar> WBP_HPBar;

	UPROPERTY(VisibleAnywhere, Category = Clear, meta = (BindWidget))
	TObjectPtr<class UCPClearHUD> WBP_Clear;
};

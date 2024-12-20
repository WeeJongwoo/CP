// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CPStatComponent.generated.h"

DECLARE_DELEGATE(DeadEventDelegate);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CP_API UCPStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCPStatComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void InitializeStat(float InMaxHP, float InATK);

	void SetMaxHP(float NewMaxHP);
	void SetATK(float NewATK);
	const float GetATK();
	void SetCurrentHP(float val);
	const float GetCurrentHP();

	void SetHPWidget(class UCPPlayerHUD* InPlayerWidget);

	DeadEventDelegate DeadEvent;

private:

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UCPPlayerHUD> PlayerWidget;

	float MaxHP;
	float CurrentHp;
	float ATK;

	bool bIsDead;
};

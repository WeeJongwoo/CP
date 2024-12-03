// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/CPGameModeBase.h"

ACPGameModeBase::ACPGameModeBase()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassRef(TEXT("/Game/Character/BP_CPCharacter.BP_CPCharacter_C"));
	if (PlayerPawnClassRef.Class)
	{
		DefaultPawnClass = PlayerPawnClassRef.Class;
	}

	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerClassRef(TEXT("/Game/GameMode/BP_CPController.BP_CPController"));
	if (PlayerControllerClassRef.Class)
	{
		PlayerControllerClass = PlayerControllerClassRef.Class;
	}
}

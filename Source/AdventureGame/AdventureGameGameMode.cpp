// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "AdventureGameGameMode.h"
#include "AdventureGameCharacter.h"
#include "UObject/ConstructorHelpers.h"

AAdventureGameGameMode::AAdventureGameGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/Player/BP_PlayerCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

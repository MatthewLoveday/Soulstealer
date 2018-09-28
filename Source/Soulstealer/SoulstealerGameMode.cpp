// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "SoulstealerGameMode.h"
#include "SoulstealerPlayerController.h"
#include "SoulstealerCharacter.h"
#include "UObject/ConstructorHelpers.h"

ASoulstealerGameMode::ASoulstealerGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = ASoulstealerPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
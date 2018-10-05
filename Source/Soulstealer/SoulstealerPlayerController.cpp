// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "SoulstealerPlayerController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "SoulstealerCharacter.h"
#include "Engine/World.h"
#include "Engine/Engine.h"
#include "Kismet/KismetMathLibrary.h"

ASoulstealerPlayerController::ASoulstealerPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}

void ASoulstealerPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);


}

void ASoulstealerPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	//Setup input callbacks
	InputComponent->BindAxis("MouseX", this, &ASoulstealerPlayerController::LookAtMouse);
	InputComponent->BindAxis("MouseY", this, &ASoulstealerPlayerController::LookAtMouse);
}

void ASoulstealerPlayerController::GetMouseInWorld(FVector &WorldLocation)
{
	FHitResult mouseHit;
	GetHitResultUnderCursor(ECC_GameTraceChannel1, false, mouseHit);
	
	//If linetrace has hit a target
	if (mouseHit.bBlockingHit)
	{
		WorldLocation = mouseHit.ImpactPoint;
	}
}

void ASoulstealerPlayerController::LookAtMouse(float axisValue)
{
	//Get mouse position in world
	FVector targetLocation;
	GetMouseInWorld(targetLocation);

	//Normalise Z Coordinate
	targetLocation.Z = GetCharacter()->GetActorLocation().Z;

	//Set player rotation to look at position
	FRotator lookAtRot = UKismetMathLibrary::FindLookAtRotation(GetCharacter()->GetActorLocation(), targetLocation);

	GetCharacter()->SetActorRotation(lookAtRot);
}


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

	MovementVector = FVector::ZeroVector;
}

void ASoulstealerPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	LookAtMouse(0.0f);
	MoveCharacter();
}

void ASoulstealerPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();
	InputComponent->BindAxis("MoveForward", this, &ASoulstealerPlayerController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ASoulstealerPlayerController::MoveRight);
	InputComponent->BindAction("Aim", IE_Pressed, this, &ASoulstealerPlayerController::Aim);
	InputComponent->BindAction("Aim", IE_Released, this, &ASoulstealerPlayerController::StopAim);
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

FVector ASoulstealerPlayerController::GetCameraForward()
{
	FRotator camForward = PlayerCameraManager->GetCameraRotation();
	camForward.Pitch = 0;
	return UKismetMathLibrary::GetForwardVector(camForward);
}

FVector ASoulstealerPlayerController::GetCameraRight()
{
	FRotator camRight = PlayerCameraManager->GetCameraRotation();
	camRight.Pitch = 0;
	return UKismetMathLibrary::GetRightVector(camRight);
}

void ASoulstealerPlayerController::MoveRight(float axisValue)
{
	MovementVector += GetCameraRight() * axisValue;
}

void ASoulstealerPlayerController::MoveForward(float axisValue)
{
	MovementVector += GetCameraForward() * axisValue;
}

void ASoulstealerPlayerController::MoveCharacter()
{
	GetCharacter()->AddMovementInput(MovementVector, MoveSpeed, false);
	MovementVector = FVector::ZeroVector;
}



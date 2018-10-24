// Fill out your copyright notice in the Description page of Project Settings.

#include "ZombieController.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Engine/World.h"
#include "Engine/Engine.h"
#include "Kismet/KismetMathLibrary.h"
#include "OutputDeviceNull.h"

#include <string>

void AZombieController::BeginPlay()
{
	Super::BeginPlay();

	//Set the target
	target = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	//Set actor tick
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void AZombieController::TakenDamage()
{
	try
	{
		FEditorScriptExecutionGuard ScriptGuard;
		FOutputDeviceNull ar;
		this->CallFunctionByNameWithArguments(TEXT("RecievedDamage"), ar, NULL, true);
	}
	catch(std::string e)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to call recieved damage on blueprint: "));
	}
}

void AZombieController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	//Use navmesh to navigate to actor
	MoveToActor(target, -1.f);
	FaceActor(target->GetActorLocation());
}

void AZombieController::FaceActor(FVector Location)
{
	//Normalise Z Coordinate
	Location.Z = GetCharacter()->GetActorLocation().Z;

	//Set player rotation to look at position
	FRotator lookAtRot = UKismetMathLibrary::FindLookAtRotation(GetCharacter()->GetActorLocation(), Location);

	GetCharacter()->SetActorRotation(lookAtRot);
}

void AZombieController::FaceActor(const AActor * Actor)
{
	FaceActor(Actor->GetActorLocation());
}



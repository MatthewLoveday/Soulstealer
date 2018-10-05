// Fill out your copyright notice in the Description page of Project Settings.

#include "ZombieController.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Engine/Engine.h"

void AZombieController::BeginPlay()
{
	//Set the target
	target = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	if (target != nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Aqquired Target " + target->GetName() + " at position " + target->GetActorLocation().ToString()));
	}

	MoveToLocation(target->GetActorLocation(), -1, true, true);
}

void AZombieController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	MoveToLocation(target->GetActorLocation(), -1, true, true);
}



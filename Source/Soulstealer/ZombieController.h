// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ZombieController.generated.h"

/**
 * 
 */
UCLASS()
class SOULSTEALER_API AZombieController : public AAIController
{
	GENERATED_BODY()
	
public:
	void BeginPlay() override;


private:
	UPROPERTY(VisibleAnywhere)
	AActor* target;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
};

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MaxHealth = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Health = 100;

	UFUNCTION()
	void TakenDamage();

private:
	UPROPERTY(VisibleAnywhere)
	AActor* target;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	void FaceActor(FVector Location);
	void FaceActor(const AActor * Actor);
};

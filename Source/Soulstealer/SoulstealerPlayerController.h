// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SoulstealerPlayerController.generated.h"

UCLASS()
class ASoulstealerPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ASoulstealerPlayerController();


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MoveSpeed = 20.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Aiming = false;

protected:
	/** True if the controlled character should navigate to the mouse cursor. */
	uint32 bMoveToMouseCursor : 1;

	// Begin PlayerController interface
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;


	void GetMouseInWorld(FVector &WorldLocation);

	void LookAtMouse(float axisValue);

	//Movement
	FVector MovementVector;

	FVector GetCameraForward();
	FVector GetCameraRight();

	void MoveForward(float axisValue);
	void MoveRight(float axisValue);

	void MoveCharacter();

	void Aim() { Aiming = true; }
	void StopAim() { Aiming = false; }
};



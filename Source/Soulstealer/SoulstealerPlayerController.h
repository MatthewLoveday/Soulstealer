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

protected:
	/** True if the controlled character should navigate to the mouse cursor. */
	uint32 bMoveToMouseCursor : 1;

	// Begin PlayerController interface
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;


	void GetMouseInWorld(FVector &WorldLocation);

	void LookAtMouse(float axisValue);

};



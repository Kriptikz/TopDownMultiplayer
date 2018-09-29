// Fill out your copyright notice in the Description page of Project Settings.

#include "TDMPlayerController.h"




ATDMPlayerController::ATDMPlayerController()
{
	bRightMouseDown = false;
	bShowMouseCursor = true;
	bEnableTouchEvents = false;
}

void ATDMPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (bRightMouseDown)
	{
		// Tell the server we right clicked and send updated mouse location

	}
}

void ATDMPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("RightClick", IE_Pressed, this, &ATDMPlayerController::RightMousePressed);
	InputComponent->BindAction("RightClick", IE_Released, this, &ATDMPlayerController::RightMouseReleased);
}

void ATDMPlayerController::RightMousePressed()
{
	bRightMouseDown = true;
}

void ATDMPlayerController::RightMouseReleased()
{
	bRightMouseDown = false;
}

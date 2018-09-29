// Fill out your copyright notice in the Description page of Project Settings.

#include "TDMPlayerController.h"




ATDMPlayerController::ATDMPlayerController()
{
	// Set some mouse defaults
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

		float MouseX;
		float MouseY;

		if (GetMousePosition(MouseX, MouseY))
		{
			ServerOnRightClick(MouseX, MouseY);
		}

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

void ATDMPlayerController::ServerOnRightClick_Implementation(float MouseX, float MouseY)
{
	UE_LOG(LogTemp, Warning, TEXT("ServerOnRightClick"));
}

bool ATDMPlayerController::ServerOnRightClick_Validate(float MouseX, float MouseY)
{
	return true;
}


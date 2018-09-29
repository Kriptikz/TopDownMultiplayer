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


		// Convert our mouse location on our screen (which is in 2D) to world space (3D)
		FVector MouseLocationWorldSpace;
		FVector MouseDirectionWorldSpace;

		if (DeprojectMousePositionToWorld(MouseLocationWorldSpace, MouseDirectionWorldSpace))
		{
			// Extract the X and Y from our mouse world space location
			float MouseX = MouseLocationWorldSpace.X;
			float MouseY = MouseLocationWorldSpace.Y;

			// Send RPC to server notifying that we have done a right click on the client and giving the location we right clicked from
			ServerOnRightClick(MouseX, MouseY);
		}

	}
}

void ATDMPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Bind action inputs
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
	// Need the angle of the camera setup so we can line trace from our MouseX and Y world space locations
}

bool ATDMPlayerController::ServerOnRightClick_Validate(float MouseX, float MouseY)
{
	// Nothing to validate currently
	return true;
}


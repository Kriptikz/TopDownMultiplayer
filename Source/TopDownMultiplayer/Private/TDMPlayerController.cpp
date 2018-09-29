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

		FVector MouseLocationWorldSpace;
		FVector MouseDirectionWorldSpace;

		if (DeprojectMousePositionToWorld(MouseLocationWorldSpace, MouseDirectionWorldSpace))
		{
			float MouseX = MouseLocationWorldSpace.X;
			float MouseY = MouseLocationWorldSpace.Y;
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
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Red, FString::Printf(TEXT("MouseX: %f \n MouseY: %f "), MouseX, MouseY));
	}
}

bool ATDMPlayerController::ServerOnRightClick_Validate(float MouseX, float MouseY)
{
	return true;
}


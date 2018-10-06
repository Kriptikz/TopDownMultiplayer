// Fill out your copyright notice in the Description page of Project Settings.

#include "TDMPlayerController.h"



ATDMPlayerController::ATDMPlayerController()
{
	// Set up our MoveCommandTimer function delegate
	MoveCommandTimerDelegate = FTimerDelegate::CreateUObject(this, &ATDMPlayerController::ServerMoveCommand, CurrentCursorHitResult);

	// Set up to have our timer run ever 0.1 seconds to issue ServerMoveCommand RPC
	MoveCommandRPCRate = 0.1f;

	// Set some mouse defaults
	bShowMouseCursor = true;
	bEnableTouchEvents = false;
}

void ATDMPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

}

void ATDMPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Bind action inputs
	InputComponent->BindAction("MoveCommand", IE_Pressed, this, &ATDMPlayerController::MoveCommandKeyPressed);
	InputComponent->BindAction("MoveCommand", IE_Released, this, &ATDMPlayerController::MoveCommandKeyReleased);
}

void ATDMPlayerController::MoveCommandKeyPressed()
{
	// Start our MoveCommand Timer
	GetWorldTimerManager().SetTimer(MoveCommandTimerHandle, MoveCommandTimerDelegate, MoveCommandRPCRate, true, 0.0f);
}

void ATDMPlayerController::MoveCommandKeyReleased()
{
	// Stop our MoveCommand Timer
	GetWorldTimerManager().ClearTimer(MoveCommandTimerHandle);
}

void ATDMPlayerController::ServerMoveCommand_Implementation(FHitResult CurrentHitResult)
{
	// Implement movement
}

bool ATDMPlayerController::ServerMoveCommand_Validate(FHitResult CurrentHitResult)
{
	return true;
}


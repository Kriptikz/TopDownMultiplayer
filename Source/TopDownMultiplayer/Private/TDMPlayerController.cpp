// Fill out your copyright notice in the Description page of Project Settings.

#include "TDMPlayerController.h"
#include "TopDownMultiplayer.h"
#include "DrawDebugHelpers.h"



ATDMPlayerController::ATDMPlayerController()
{
	// Set up our MoveCommandTimer function delegate
	MoveCommandTimerDelegate = FTimerDelegate::CreateUObject(this, &ATDMPlayerController::ServerMoveCommand, CurrentCursorHitResult);

	// Set up our TTQ_Floor and TTQ_Targetable
	TTQ_Floor = UEngineTypes::ConvertToTraceType(ECC_Floor);
	TTQ_Targetable = UEngineTypes::ConvertToTraceType(ECC_Targetable);

	// Set up to have our timer run ever 0.1 seconds to issue ServerMoveCommand RPC
	MoveCommandRPCRate = 0.1f;

	// Rate at which we update our client controllers CurrentCursor data.
	UpdateCursorDataRate = 0.05f;

	// Set some mouse defaults
	bShowMouseCursor = true;
	bEnableTouchEvents = false;
}

void ATDMPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (IsLocalPlayerController())
	{
		GetWorldTimerManager().SetTimer(UpdateCursorDataTimerHandle, this, &ATDMPlayerController::ClientUpdateCurrentCursorData, UpdateCursorDataRate, true, 0.0f);
	}
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

void ATDMPlayerController::ClientUpdateCurrentCursorData_Implementation()
{
	// Update CurrentCursorHitResult
	GetHitResultUnderCursorByChannel(TTQ_Targetable, false, CurrentCursorHitResult);

	// Update CurrentCursorAimedLocation by doing a line trace and getting the hit location
	FHitResult HitResult;

	GetHitResultUnderCursorByChannel(TTQ_Floor, true, HitResult);
	CurrentCursorAimedLocation = HitResult.Location;
}

void ATDMPlayerController::ServerMoveCommand_Implementation(FHitResult CurrentHitResult)
{
	// Implement movement
}

bool ATDMPlayerController::ServerMoveCommand_Validate(FHitResult CurrentHitResult)
{
	return true;
}


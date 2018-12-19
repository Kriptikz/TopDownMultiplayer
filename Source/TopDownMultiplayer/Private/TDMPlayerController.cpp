// Fill out your copyright notice in the Description page of Project Settings.

#include "TDMPlayerController.h"
#include "TopDownMultiplayer.h"
#include "DrawDebugHelpers.h"
#include "Blueprint//AIBlueprintHelperLibrary.h"
#include "TDMCharacter.h"
#include "TargetableInterface.h"
#include "Net/UnrealNetwork.h"



ATDMPlayerController::ATDMPlayerController()
{

	// Set up our TTQ_Floor and TTQ_Targetable
	TTQ_Floor = UEngineTypes::ConvertToTraceType(ECC_Floor);
	TTQ_Targetable = UEngineTypes::ConvertToTraceType(ECC_Targetable);


	// Rate at which we update our client controllers current cursor data.
	UpdateCursorDataRate = 0.02f;

	// Set some mouse defaults
	bShowMouseCursor = true;
	bEnableTouchEvents = false;
}

FVector ATDMPlayerController::GetTargetLocation(AActor* RequestedBy /*= nullptr*/) const
{
	return TargetLocation;
}

AActor* ATDMPlayerController::GetHoveredActor()
{
	return HoveredActor;
}

AActor* ATDMPlayerController::GetSelectedActor()
{
	return SelectedActor;
}

AActor* ATDMPlayerController::GetTargetActor()
{
	return TargetActor;
}

void ATDMPlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ATDMPlayerController, TargetActor);
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

}

void ATDMPlayerController::ClientUpdateCurrentCursorData_Implementation()
{
	// Scan for an actor under the cursor
	FHitResult CursorHitResult;

	if (GetHitResultUnderCursorByChannel(TTQ_Targetable, true, CursorHitResult))
	{
		HoveredActor = CursorHitResult.GetActor();
	}

	// Scan for the floor to update our current TargetLocation
	if (GetHitResultUnderCursorByChannel(TTQ_Floor, true, CursorHitResult))
	{
		TargetLocation = CursorHitResult.Location;
	}
}


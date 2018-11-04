// Fill out your copyright notice in the Description page of Project Settings.

#include "TDMPlayerController.h"
#include "TopDownMultiplayer.h"
#include "DrawDebugHelpers.h"
#include "Blueprint//AIBlueprintHelperLibrary.h"
#include "AIController.h"
#include "TDMCharacter.h"
#include "TargetableInterface.h"



ATDMPlayerController::ATDMPlayerController()
{

	// Set up our TTQ_Floor and TTQ_Targetable
	TTQ_Floor = UEngineTypes::ConvertToTraceType(ECC_Floor);
	TTQ_Targetable = UEngineTypes::ConvertToTraceType(ECC_Targetable);

	// Set up to have our timer run ever 0.1 seconds to issue ServerMoveCommand RPC
	MoveCommandRPCRate = 0.1f;

	// Rate at which we update our client controllers CurrentCursor data.
	UpdateCursorDataRate = 0.02f;

	// Set some mouse defaults
	bShowMouseCursor = true;
	bEnableTouchEvents = false;
}

void ATDMPlayerController::Possess(APawn* aPawn)
{
	Super::Possess(aPawn);

	// Ensure we are only doing this server side
	if (Role == ROLE_Authority)
	{
		FTransform SpawnTransform;
		SpawnTransform = aPawn->GetActorTransform();
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		// Spawn the Character we will control and cache a reference
		ControlledCharacter = (ATDMCharacter*) GetWorld()->SpawnActor(SpawnCharacterClass, &SpawnTransform, SpawnParams);

		// Spawn the AIController that will handle pathfinding replicated movement and cache a reference
		CharacterAIController = (AAIController*) GetWorld()->SpawnActor(AAIController::StaticClass(), &SpawnTransform, SpawnParams);

		// Set the AIController to Possess the Character
		CharacterAIController->Possess(ControlledCharacter);
	}
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

ATDMCharacter* ATDMPlayerController::GetControlledCharacter()
{
	return ControlledCharacter;
}

AAIController* ATDMPlayerController::GetCharacterAIController()
{
	return CharacterAIController;
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
	ClientUpdateCurrentCursorData();
	GetWorldTimerManager().SetTimer(MoveCommandTimerHandle, this, &ATDMPlayerController::ClientSendMoveCommand, MoveCommandRPCRate, true, 0.0f);
}

void ATDMPlayerController::MoveCommandKeyReleased()
{
	// Stop our MoveCommand Timer
	GetWorldTimerManager().ClearTimer(MoveCommandTimerHandle);
}

void ATDMPlayerController::ClientSendMoveCommand_Implementation()
{
	ServerMoveCommand(CurrentCursorHitResult);
}

void ATDMPlayerController::ClientUpdateCurrentCursorData_Implementation()
{
	// Update CurrentCursorHitResult
	if (GetHitResultUnderCursorByChannel(TTQ_Targetable, true, CurrentCursorHitResult))
	{
		HoveredActor = CurrentCursorHitResult.GetActor();
	}


	// Update CurrentCursorAimedLocation by doing a line trace directly to the floor and getting the hit location
	FHitResult HitResult;

	GetHitResultUnderCursorByChannel(TTQ_Floor, true, HitResult);
	CurrentCursorAimedLocation = HitResult.Location;
}

void ATDMPlayerController::ServerMoveCommand_Implementation(FHitResult CurrentHitResult)
{
	// Implement movement

	UE_LOG(LogTemp, Warning, TEXT("SERVER MOVE COMMAND"));

	if (CharacterAIController)
	{
		CharacterAIController->MoveToLocation(CurrentHitResult.Location, 1.0f);
	}

}

bool ATDMPlayerController::ServerMoveCommand_Validate(FHitResult CurrentHitResult)
{
	return true;
}


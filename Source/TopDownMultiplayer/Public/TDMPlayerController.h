// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TimerManager.h"
#include "TDMPlayerController.generated.h"

/**
 * This is our base player controller. All input will be routed through here where the inputs function will send an RPC to the server side
 * version of this controller where it will handle the players input. This will mean there is very little client prediction so what you see 
 * is what is happening on the server but this also means there will be some input lag based on ping. 
 */
UCLASS()
class TOPDOWNMULTIPLAYER_API ATDMPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	ATDMPlayerController();
	

	virtual void Tick(float DeltaSeconds) override;

protected:
	
	/** The rate at which we call our ClientUpdateCurrentCursorData function while the timer is active */
	UPROPERTY(EditDefaultsOnly, Category = "Rates")
	float UpdateCursorDataRate;

	/** Current client cursor hit result, updated using ClientUpdateCurrentCursorData  */
	UPROPERTY(BlueprintReadOnly, Category = "Cursor")
	FHitResult CurrentCursorHitResult;

	/** A conversion of our ECC_Floor trace channel to an ETraceTypeQuery */
	UPROPERTY()
	TEnumAsByte<ETraceTypeQuery> TTQ_Floor;

	/** A conversion of our ECC_Targetable trace channel to an ETraceTypeQuery */
	UPROPERTY()
	TEnumAsByte<ETraceTypeQuery> TTQ_Targetable;

	/** Current client cursor aimed location on the floor */
	UPROPERTY(BlueprintReadOnly, Category = "Cursor")
	FVector_NetQuantize CurrentCursorAimedLocation;

	/** Timer that updates our current cursor data every 0.1s */
	UPROPERTY()
	FTimerHandle UpdateCursorDataTimerHandle;

	/** The rate at which we call our ServerMoveCommand RPC while the MoveCommand key is pressed */
	UPROPERTY(EditDefaultsOnly, Category = "Rates")
	float MoveCommandRPCRate;

	/** Timer runs based on our MoveCommandRPCRate to call the ServerMoveCommand and pass in the CurrentHitResult */
	UPROPERTY()
	FTimerHandle MoveCommandTimerHandle;

	/** A function delegate that should be set to the MoveCommand server function in the constructor, used so our delegate can have a parameter */
	FTimerDelegate MoveCommandTimerDelegate;

	/** This is where we setup our input delegates. These will call local functions which will send an RPC to call the server side version. */
	virtual void SetupInputComponent() override;

	/** Client function delegate for when the move command key is pressed, it will start our timer that calls our ServerMoveCommand. */
	UFUNCTION()
	void MoveCommandKeyPressed();

	/** Client function delegate for when the move command is released, it will stop our timer that calls our ServerMoveCommand. */
	UFUNCTION()
	void MoveCommandKeyReleased();

	/**
	 * Server function called from a timer every 0.1 seconds to handle updating our target goal/actor
	 *
	 * @param CurrentHitResult The FHitResult in the PlayerController on the client at the time this function was called
	 */
	UFUNCTION(Server, WithValidation, Reliable)
	void ServerMoveCommand(FHitResult CurrentHitResult);

	/**
	 * Delegate function called from a timer every 0.1 seconds to handle updating our controller variables: CurrentCursorHitResult CurrentCursorAimedLocation
	 */
	UFUNCTION(Client, Reliable)
	void ClientUpdateCurrentCursorData();

	virtual void BeginPlay() override;

};

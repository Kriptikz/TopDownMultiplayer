// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TimerManager.h"
#include "UObject/ScriptInterface.h"
#include "TargetableInterface.h"
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

protected:
	
	/** The rate at which we call our ClientUpdateCurrentCursorData function while the timer is active */
	UPROPERTY(EditDefaultsOnly, Category = "Rates")
	float UpdateCursorDataRate;

	/** Handle for our timer that updates cursor data on the client based on the UpdateCursorDataRate */
	UPROPERTY()
	FTimerHandle UpdateCursorDataTimerHandle;

	/** Current client cursor target location on the floor, this is primarily updated on the client and should be sent to the server when needed. */
	UPROPERTY(BlueprintReadOnly, Category = "CursorTargetData")
	FVector CursorAimLocation;

	/** Current client hovered actor that is targetable, this should be the most up to date targetable actor variable on the client and should be sent to the server when needed. */
	UPROPERTY(BlueprintReadOnly, Category = "CursorTargetData")
	AActor* HoveredActor;

	/** The currently selected actor, this should always be up to date on the server and then replicated to the clients */
	UPROPERTY(BlueprintReadOnly, Replicated, Category = "CursorTargetData")
	AActor* SelectedActor;

	/** The currently targeted actor, this should always be up to date on the server and then replicated to the clients */
	UPROPERTY(BlueprintReadWrite, Replicated, Category = "CursorTargetData")
	AActor* TargetActor;

	/** A conversion of our ECC_Floor trace channel to an ETraceTypeQuery */
	UPROPERTY()
	TEnumAsByte<ETraceTypeQuery> TTQ_Floor;

	/** A conversion of our ECC_Targetable trace channel to an ETraceTypeQuery */
	UPROPERTY()
	TEnumAsByte<ETraceTypeQuery> TTQ_Targetable;

	/** Timer runs based on our MoveCommandRPCRate to call the ServerMoveCommand and pass in the CurrentHitResult */
	UPROPERTY()
	FTimerHandle MoveCommandTimerHandle;

	/** This is where we setup our input delegates. These will call local functions which will send an RPC to call the server side version. */
	virtual void SetupInputComponent() override;

	/**
	 * Delegate function called from a timer using UpdateCursorDataRate to handle updating our client-side cursor target data: CurrentCursorHitResult CurrentCursorAimedLocation
	 */
	UFUNCTION(Client, Reliable)
	void ClientUpdateCurrentCursorData();

	virtual void BeginPlay() override;

public:
	
	virtual void Tick(float DeltaSeconds) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) const override;


	UFUNCTION(BlueprintPure)
	AActor* GetHoveredActor();

	UFUNCTION(BlueprintPure)
	AActor* GetSelectedActor();

	UFUNCTION(BlueprintPure)
	AActor* GetTargetActor();

	UFUNCTION(BlueprintPure)
	FVector GetCursorAimLocation();
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
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

	/** A toggle for handling when the right mouse button is held down, checked on tick. */
	UPROPERTY(BlueprintReadOnly, Category = "Input")
	bool bRightMouseDown;

	/** This is where we setup our input delegates. These will call local functions which will send an RPC to call the server side version. */
	virtual void SetupInputComponent() override;

	/** Client function delegate for when the right mouse button is pressed, it will toggle our bool bRightMouseDown to true where it is checked on tick. */
	UFUNCTION()
	void RightMousePressed();

	/** Client function delegate for when the right mouse button is released, it will toggle our bool bRightMouseDown to false where it is checked on tick. */
	UFUNCTION()
	void RightMouseReleased();

};

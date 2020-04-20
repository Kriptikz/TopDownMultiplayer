// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TDMAIController.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNMULTIPLAYER_API ATDMAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	virtual void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;

};

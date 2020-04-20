// Fill out your copyright notice in the Description page of Project Settings.


#include "TDMAIController.h"

void ATDMAIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	Super::OnMoveCompleted(RequestID, Result);
	
}

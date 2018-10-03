// Fill out your copyright notice in the Description page of Project Settings.

#include "TDMActor.h"


// Sets default values
ATDMActor::ATDMActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATDMActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATDMActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

ETargetableType ATDMActor::GetTargetableType() const
{
	return TargetableType;
}


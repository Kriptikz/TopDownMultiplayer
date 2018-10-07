// Fill out your copyright notice in the Description page of Project Settings.

#include "TDMCharacter.h"


// Sets default values
ATDMCharacter::ATDMCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATDMCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATDMCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATDMCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


// Fill out your copyright notice in the Description page of Project Settings.

#include "TDMPlayerCameraPawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"


// Sets default values
ATDMPlayerCameraPawn::ATDMPlayerCameraPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create the default scene component
	SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComp"));
	RootComponent = SceneComp;

	// Create the spring arm component
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComp->SetupAttachment(SceneComp);

	// Camera should never get obstructed by objects
	SpringArmComp->bDoCollisionTest = false;

	// Set spring arm to not rotate when the pawn rotates
	SpringArmComp->bInheritPitch = false;
	SpringArmComp->bInheritYaw = false;
	SpringArmComp->bInheritRoll = false;

	// Create the camera component
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(SpringArmComp);

	// Set locked screen to true as default
	bLockedScreen = true;
}

// Called when the game starts or when spawned
void ATDMPlayerCameraPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATDMPlayerCameraPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bLockedScreen)
	{
		if (GetController())
		{
			return;
		}
	}
}


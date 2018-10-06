// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TDMPlayerCameraPawn.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class TOPDOWNMULTIPLAYER_API ATDMPlayerCameraPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATDMPlayerCameraPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Our Scene Component, this is our root component */
	UPROPERTY(VisibleAnywhere, Category = "Components")
	USceneComponent* SceneComp;

	/** Controls camera angle and has useful settings for camera control */
	UPROPERTY(VisibleAnywhere, Category = "Components")
	USpringArmComponent* SpringArmComp;

	/** The main camera our player will be viewing the game through, will follow the currently controlled character by default but can be toggled. */
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UCameraComponent* CameraComp;

	/** The toggle for camera to auto follow currently controlled character */
	UPROPERTY(VisibleAnywhere, Category = "Camera")
	bool bLockedScreen;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};

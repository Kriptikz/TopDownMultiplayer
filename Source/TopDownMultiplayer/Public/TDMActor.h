// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TargetableInterface.h"
#include "TDMActor.generated.h"

UCLASS()
class TOPDOWNMULTIPLAYER_API ATDMActor : public AActor, public ITargetableInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATDMActor();

protected:

	// The targetable type of this actor
	UPROPERTY(EditDefaultsOnly, Category = "Target")
	ETargetableType TargetableType;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual ETargetableType GetTargetableType() const override;

};

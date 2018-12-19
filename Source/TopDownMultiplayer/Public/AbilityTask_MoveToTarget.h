// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "AbilityTask_MoveToTarget.generated.h"



DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMoveToTargetDelegate);

/**
 * 
 */
UCLASS()
class TOPDOWNMULTIPLAYER_API UAbilityTask_MoveToTarget : public UAbilityTask
{
	GENERATED_BODY()

	UPROPERTY(BlueprintAssignable)
	FMoveToTargetDelegate TargetRangeReached;

	/** Move to the specified location, using the vector curve (range 0 - 1) if specified, otherwise the float curve (range 0 - 1) or fallback to linear interpolation */
	UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
	static UAbilityTask_MoveToTarget* MoveToTarget(UGameplayAbility* OwningAbility, FName TaskInstanceName, float Range, FVector TargetLocation, AActor* TargetActor);

protected:

	UPROPERTY(Replicated)
	FVector TargetLocation;

	UPROPERTY(Replicated)
	AActor* TargetActor;

	UPROPERTY(Replicated)
	bool bUseDefaultRange;

	UPROPERTY(Replicated)
	float Range;
	
public:
	
	UAbilityTask_MoveToTarget(const FObjectInitializer& ObjectInitializer);
	
	
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty> & OutLifetimeProps) const override;


	virtual void TickTask(float DeltaTime) override;

};

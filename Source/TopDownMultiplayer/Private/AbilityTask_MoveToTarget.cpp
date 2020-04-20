// Fill out your copyright notice in the Description page of Project Settings.

#include "AbilityTask_MoveToTarget.h"
#include "TDMCharacter.h"
#include "Net/UnrealNetwork.h"


UAbilityTask_MoveToTarget::UAbilityTask_MoveToTarget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bTickingTask = true;
}

UAbilityTask_MoveToTarget* UAbilityTask_MoveToTarget::MoveToTarget(UGameplayAbility* OwningAbility, FName TaskInstanceName, float Range, FVector TargetLocation, AActor* TargetActor, ATDMCharacter* OwningCharacter)
{
	UAbilityTask_MoveToTarget* NewAbilityTaskObject = NewAbilityTask<UAbilityTask_MoveToTarget>(OwningAbility, TaskInstanceName);
	NewAbilityTaskObject->TargetLocation = TargetLocation;
	NewAbilityTaskObject->TargetActor = TargetActor;
	NewAbilityTaskObject->OwningCharacter = OwningCharacter;
	
	if (Range < 10.0f)
	{
		NewAbilityTaskObject->Range = 10.0f;
	}
	else
	{
		NewAbilityTaskObject->Range = Range;
	}

	return NewAbilityTaskObject;
}

void UAbilityTask_MoveToTarget::TickTask(float DeltaTime)
{
	Super::TickTask(DeltaTime);


	ATDMCharacter* MyCharacter = Cast<ATDMCharacter>(GetAvatarActor());
	if (MyCharacter)
	{
		//if (TargetActor)
		if (TargetActor && OwningCharacter->GetTargetActor())
		{
			FVector ZeroZTargetLocation = OwningCharacter->GetTargetActor()->GetActorLocation();
			ZeroZTargetLocation.Z = 0;

			FVector ZeroZCharacterLocation = MyCharacter->GetActorLocation();
			ZeroZCharacterLocation.Z = 0;

			FVector TargetDirection = ZeroZTargetLocation - ZeroZCharacterLocation;
	
			if (TargetDirection.Size() <= Range)
			{
				TargetRangeReached.Broadcast();
				EndTask();
			}
			else
			{
				MyCharacter->AddMovementInput(TargetDirection);
			}
		}
		else
		{
			FVector ZeroZTargetLocation = OwningCharacter->GetObjectiveLocation();
			ZeroZTargetLocation.Z = 0;

			FVector ZeroZCharacterLocation = MyCharacter->GetActorLocation();
			ZeroZCharacterLocation.Z = 0;

			FVector TargetDirection = ZeroZTargetLocation - ZeroZCharacterLocation;
	
			if (TargetDirection.Size() <= Range)
			{
				TargetRangeReached.Broadcast();
				EndTask();
			}
			else
			{
				MyCharacter->AddMovementInput(TargetDirection);
			}
		}

	}
}

void UAbilityTask_MoveToTarget::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty> & OutLifetimeProps) const
{
	DOREPLIFETIME(UAbilityTask_MoveToTarget, TargetLocation);
	DOREPLIFETIME(UAbilityTask_MoveToTarget, TargetActor);
	DOREPLIFETIME(UAbilityTask_MoveToTarget, Range);
	DOREPLIFETIME(UAbilityTask_MoveToTarget, OwningCharacter);
}


#include "GameplayAbilityTargetActor_CursorTargetData.h"
#include "TDMPlayerController.h"
#include "TDMCharacter.h"
#include "GameplayAbility.h"
#include "TDMAbilityTargetTypes.h"

void AGameplayAbilityTargetActor_CursorTargetData::StartTargeting(UGameplayAbility* Ability)
{
	Super::StartTargeting(Ability);
	SourceActor = Ability->GetCurrentActorInfo()->AvatarActor.Get();
	PlayerController = Cast<ATDMPlayerController>(Cast<ATDMCharacter>(Ability->GetAvatarActorFromActorInfo())->GetController());
}

void AGameplayAbilityTargetActor_CursorTargetData::ConfirmTargetingAndContinue()
{
	check(ShouldProduceTargetData());
	if (SourceActor)
	{
		FVector NewTargetLocation = PlayerController->GetCursorAimLocation();
		AActor* NewTargetActor = PlayerController->GetHoveredActor();
		TArray<TWeakObjectPtr<AActor> > NewTargetActorArray;
		if (NewTargetActor)
		{
			NewTargetActorArray.Push(NewTargetActor);
		}

		FGameplayAbilityTargetData_CursorTargetData* ReturnData = new FGameplayAbilityTargetData_CursorTargetData();
		
		ReturnData->TargetLocation = NewTargetLocation;
		ReturnData->SetActors(NewTargetActorArray);

		FGameplayAbilityTargetDataHandle Handle(ReturnData);
		TargetDataReadyDelegate.Broadcast(Handle);
	}
}


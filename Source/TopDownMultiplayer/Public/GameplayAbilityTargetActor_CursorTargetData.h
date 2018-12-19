#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTargetActor.h"
#include "GameplayAbilityTargetActor_CursorTargetData.generated.h"

class ATDMPlayerController;

/**
 * 
 */
UCLASS(Blueprintable)
class TOPDOWNMULTIPLAYER_API AGameplayAbilityTargetActor_CursorTargetData : public AGameplayAbilityTargetActor
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "References")
	ATDMPlayerController* PlayerController;
	
	
public:
	virtual void StartTargeting(UGameplayAbility* Ability) override;


	virtual void ConfirmTargetingAndContinue() override;

};

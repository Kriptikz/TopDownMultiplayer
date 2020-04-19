// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "TargetableInterface.h"
#include "TDMCharacter.generated.h"

class UAbilitySystemComponent;


UCLASS()
class TOPDOWNMULTIPLAYER_API ATDMCharacter : public ACharacter, public IAbilitySystemInterface, public ITargetableInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATDMCharacter();

protected:

	/** Our Ability System Component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Abilities", meta = (AllowPrivateAccess = "true"))
	UAbilitySystemComponent* AbilitySystem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Abilities)
	TArray<TSubclassOf<class UGameplayAbility>> GameplayAbilities;

	UPROPERTY(BlueprintReadWrite, Replicated, Category = "Target")
	AActor* TargetActor;

	UPROPERTY(BlueprintReadWrite, Category = "Target")
	FVector ObjectiveLocation;

	UPROPERTY()
	int32 bAbilitiesInitialized;

	// The targetable type of this actor
	UPROPERTY(EditDefaultsOnly, Category = "Target")
	ETargetableType TargetableType;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	
	virtual void PossessedBy(AController* NewController) override;


	virtual ETargetableType GetTargetableType() const override;


	virtual bool IsAttackable() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(BlueprintPure)
	AActor* GetTargetActor();

	UFUNCTION(BlueprintPure)
	FVector GetObjectiveLocation();

	
	
private:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

};

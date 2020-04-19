// Fill out your copyright notice in the Description page of Project Settings.

#include "TDMCharacter.h"
#include "AbilitySystemComponent.h"


// Sets default values
ATDMCharacter::ATDMCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AbilitySystem = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystem"));
	AbilitySystem->SetIsReplicated(true);

	TargetableType = ETargetableType::TT_Attackable;
	bAbilitiesInitialized = false;
}

void ATDMCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

void ATDMCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	AbilitySystem->RefreshAbilityActorInfo();
}

ETargetableType ATDMCharacter::GetTargetableType() const
{
	return TargetableType;
}

bool ATDMCharacter::IsAttackable()
{
	return true;
}

// Called when the game starts or when spawned
void ATDMCharacter::BeginPlay()
{
	Super::BeginPlay();
	

	if (AbilitySystem)
	{
		if (HasAuthority())
		{
			for (TSubclassOf<class UGameplayAbility>& StartupAbility : GameplayAbilities)
			{
				if (StartupAbility)
				{
					AbilitySystem->GiveAbility(FGameplayAbilitySpec(StartupAbility, 1, 0));
				}
			}

			bAbilitiesInitialized = true;
		}

		AbilitySystem->InitAbilityActorInfo(this,  this);
	}
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

UAbilitySystemComponent* ATDMCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystem;
}

FVector ATDMCharacter::GetObjectiveLocation()
{
	return ObjectiveLocation;
}

AActor* ATDMCharacter::GetTargetActor()
{
	return TargetActor;
}


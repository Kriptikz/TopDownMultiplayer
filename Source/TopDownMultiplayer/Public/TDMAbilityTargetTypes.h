#pragma once

#include "CoreMinimal.h"
#include "GameplayAbilityTargetTypes.h"
#include "TDMAbilityTargetTypes.generated.h"

USTRUCT(BlueprintType)
struct FGameplayAbilityTargetData_CursorTargetData: public FGameplayAbilityTargetData
{
	GENERATED_USTRUCT_BODY()

	/** Simple target location vector */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Targeting")
	FVector TargetLocation;

	/** Simple array storing our target actors */
	UPROPERTY(EditAnywhere, Category = "Targeting")
	TArray<TWeakObjectPtr<AActor> > TargetActorArray;

	virtual UScriptStruct* GetScriptStruct() const override
	{
		return FGameplayAbilityTargetData_CursorTargetData::StaticStruct();
	}

	virtual FString ToString() const override
	{
		return TEXT("FGameplayAbilityTargetData_CursorTargetData");
	}

	bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess);


	virtual TArray<TWeakObjectPtr<AActor>> GetActors() const override;

	virtual bool SetActors(TArray<TWeakObjectPtr<AActor>> NewActorArray) override;


	virtual bool HasEndPoint() const override;


	virtual FVector GetEndPoint() const override;

};

template<>
struct TStructOpsTypeTraits<FGameplayAbilityTargetData_CursorTargetData> : public TStructOpsTypeTraitsBase2<FGameplayAbilityTargetData_CursorTargetData>
{
	enum
	{
		WithNetSerializer = true	// For now this is REQUIRED for FGameplayAbilityTargetDataHandle net serialization to work
	};
};
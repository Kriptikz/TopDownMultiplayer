#include "TDMAbilityTargetTypes.h"

bool FGameplayAbilityTargetData_CursorTargetData::NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess)
{
	TargetLocation.NetSerialize(Ar, Map, bOutSuccess);
	SafeNetSerializeTArray_Default<31>(Ar, TargetActorArray);

	bOutSuccess = true;
	return true;
}

TArray<TWeakObjectPtr<AActor>> FGameplayAbilityTargetData_CursorTargetData::GetActors() const
{
	return TargetActorArray;
}

bool FGameplayAbilityTargetData_CursorTargetData::SetActors(TArray<TWeakObjectPtr<AActor>> NewActorArray)
{
	TargetActorArray = NewActorArray;
	return true;
}

bool FGameplayAbilityTargetData_CursorTargetData::HasEndPoint() const
{
	return true;
}

FVector FGameplayAbilityTargetData_CursorTargetData::GetEndPoint() const
{
	return TargetLocation;
}

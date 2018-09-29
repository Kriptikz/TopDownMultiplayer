#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "TargetableInterface.generated.h"

/**
 * Each Targetable actor will have the type of targetable it is chosen from this UENUM. If one is not chosen it will default to TT_NULL.
 */
UENUM(BlueprintType)
enum class ETargetableType : uint8
{
	TT_NULL UMETA(DisplayName = "NULL"),
	TT_Floor UMETA(DisplayName = "Floor"),
	TT_Attackable UMETA(DisplayName = "Attackable"),
	TT_Usable UMETA(DisplayName = "Usable")
};

// This class does not need to be modified.
UINTERFACE(MinimalAPI, meta=(CannotImplementInterfaceInBlueprint))
class UTargetableInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * This is an interface that will be implemented by targetable actors like the floor and characters. The function that must be implemented
 * is GetTargetableType() which will return the type of targetable this class is using the UENUM ETargetableType
 */
class TOPDOWNMULTIPLAYER_API ITargetableInterface
{
	GENERATED_BODY()

public:
	
	/**
	 * Get the targetable type of this actor.
	 * 
	 * @return ETargetableType		The targetable type of this actor
	 */
	UFUNCTION(BlueprintCallable, Category = "TargetType")
	virtual ETargetableType GetTargetableType() const = 0;

	/**
	 * Check if the Targetable type of this actor has been set. If not make sure you override GetTargetableType.
	 *
	 * @return True if this actors Targetable Type hasn't been chosen and is NULL
	 */
	UFUNCTION(BlueprintCallable, Category = "TargetType")
	virtual bool IsNULL();

	/**
	 * Check if this actor is Targetable type Floor
	 *
	 * @return True if this actor is TT_Floor
	 */
	UFUNCTION(BlueprintCallable, Category = "TargetType")
	virtual bool IsFloor();

	/**
	* Check if this actor is Targetable type Attackable
	*
	* @return True if this actor is TT_Attackable
	*/
	UFUNCTION(BlueprintCallable, Category = "TargetType")
	virtual bool IsAttackable();

	/**
	* Check if this actor is Targetable type Usable
	*
	* @return True if this actor is TT_Usable
	*/
	UFUNCTION(BlueprintCallable, Category = "TargetType")
	virtual bool IsUsable();
};

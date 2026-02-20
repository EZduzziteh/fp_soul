#pragma once

#include "CoreMinimal.h"
#include "PickupItemInfo.generated.h"

USTRUCT(BlueprintType)
struct ANIMATION_API FPickupItemInfo
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ItemID; 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Quantity;
};

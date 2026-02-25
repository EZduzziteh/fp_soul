#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "PickupItemInfo.generated.h"

USTRUCT(BlueprintType)
struct ANIMATION_API FPickupItemInfo : public FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ItemID; 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Quantity;
};

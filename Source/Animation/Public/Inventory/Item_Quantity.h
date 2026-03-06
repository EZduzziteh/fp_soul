#pragma once

#include "CoreMinimal.h"
#include "InventoryItem.h"
#include "Inventory/DA_Item_Base.h"
#include "Engine/DataTable.h"
#include "Item_Quantity.generated.h"

USTRUCT(BlueprintType)
struct ANIMATION_API FItem_Quantity : public FTableRowBase
{
    GENERATED_BODY()

public:

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UDA_Item_Base* Item;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Quantity = 0;
};
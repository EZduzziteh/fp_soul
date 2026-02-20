#pragma once
#include "InventoryItem.h"
#include "Item_Quantity.generated.h"
struct ANIMATION_API FItem_Quantity

	{
		GENERATED_BODY()

	public:

		UPROPERTY(EditAnywhere, BlueprintReadWrite)	
		FInventoryItem Item;
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int Quantity;
}
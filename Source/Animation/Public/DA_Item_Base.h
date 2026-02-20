// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include <InventoryItem.h>
#include "DA_Item_Base.generated.h"

/**
 * 
 */
UCLASS()
class ANIMATION_API UDA_Item_Base : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	FInventoryItem Item;
};

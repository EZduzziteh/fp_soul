// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Inventory/DA_Item_Base.h"
#include "Equipment/EquipmentInfo.h"
#include "DA_Item_Equipment.generated.h"

/**
 *
 */
UCLASS()
class ANIMATION_API UDA_Item_Equipment : public UDA_Item_Base
{
	GENERATED_BODY()

public:	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	FEquipmentInfo equipmentInfo;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Equipment/ArmourInfo.h"
#include "DA_Item_Equipment_Armour.generated.h"

/**
 *
 */
UCLASS()
class ANIMATION_API UDA_Item_Equipment_Armour : public UDA_Item_Equipment
{
	GENERATED_BODY()

public:
	FArmourInfo armourInfo;
};

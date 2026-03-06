// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Inventory/DA_Item_Base.h"
#include "Equipment/WeaponInfo.h"
#include "DA_Item_Equipment_MeleeWeapon.generated.h"

/**
 *
 */
UCLASS()
class ANIMATION_API UDA_Item_Equipment_MeleeWeapon : public UDA_Item_Equipment
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	FWeaponInfo weaponInfo;
};

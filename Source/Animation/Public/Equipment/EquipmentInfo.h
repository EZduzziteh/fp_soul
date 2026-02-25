#pragma once

#include "CoreMinimal.h"
#include "EquipmentClass.h"
#include "EquipmentInfo.generated.h"

USTRUCT(BlueprintType)
struct ANIMATION_API FEquipmentInfo
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EEquipmentClass equipmentType = EEquipmentClass::Armor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Name;

};

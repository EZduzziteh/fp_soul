
#pragma once

#include "CoreMinimal.h"
#include "EquipmentClass.generated.h"  

UENUM(BlueprintType)
enum class EEquipmentSlotType : uint8
{
    Head       UMETA(DisplayName = "Head"), 
    Chest      UMETA(DisplayName = "Chest"),
    Legs      UMETA(DisplayName = "Legs"),
    Feet      UMETA(DisplayName = "Feet"),
    Primary       UMETA(DisplayName = "Primary"),
    Secondary       UMETA(DisplayName = "Secondary"),
};


#pragma once

#include "CoreMinimal.h"
#include "WeaponClass.generated.h"  

/**
 * 
 */
UENUM(BlueprintType)
enum class EWeaponClass : uint8
{
    None       UMETA(DisplayName = "None"),
    Sword      UMETA(DisplayName = "Sword"),
    Greatsword       UMETA(DisplayName = "Greatsword"),
    Axe     UMETA(DisplayName = "Axe"),
    Greataxe     UMETA(DisplayName = "Greataxe"),
    Spear     UMETA(DisplayName = "Spear"),
    Staff     UMETA(DisplayName = "Staff"),
    Shield     UMETA(DisplayName = "Shield"),
    Greatshield     UMETA(DisplayName = "Greatshield")
};

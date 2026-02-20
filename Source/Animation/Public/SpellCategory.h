
#pragma once

#include "CoreMinimal.h"
#include "SpellCategory.generated.h"  

UENUM(BlueprintType)
enum class ESpellCategory : uint8
{
    Buff       UMETA(DisplayName = "Buff"),
    Damage       UMETA(DisplayName = "Damage"),
    Heal       UMETA(DisplayName = "Heal"),
};

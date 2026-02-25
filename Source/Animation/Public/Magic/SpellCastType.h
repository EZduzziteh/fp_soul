
#pragma once

#include "CoreMinimal.h"
#include "SpellCastType.generated.h"  

UENUM(BlueprintType)
enum class ESpellCastType : uint8
{
    Instant       UMETA(DisplayName = "Instant"),
    Charge    UMETA(DisplayName = "Charge"),
};

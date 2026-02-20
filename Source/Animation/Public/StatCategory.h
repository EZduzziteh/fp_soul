
#pragma once

#include "CoreMinimal.h"
#include "StatCategory.generated.h"  

UENUM(BlueprintType)
enum class EStatCategory : uint8
{
    Vital       UMETA(DisplayName = "Vital"),
    Attribute       UMETA(DisplayName = "Attribute"),
};

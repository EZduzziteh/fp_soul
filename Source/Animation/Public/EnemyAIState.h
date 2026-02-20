#pragma once

#include "CoreMinimal.h"  // optional but recommended

UENUM(BlueprintType)
enum class EEnemyAIState : uint8
{
    Waiting     UMETA(DisplayName = "Waiting"),
    Wander      UMETA(DisplayName = "Wander"),
    Patrol      UMETA(DisplayName = "Patrol"),
    Combat      UMETA(DisplayName = "Combat")
};

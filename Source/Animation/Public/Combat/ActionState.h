#pragma once


#include "CoreMinimal.h"
#include "ActionState.generated.h"


UENUM(BlueprintType)
enum class EActionState : uint8
{
    None            UMETA(DisplayName = "None"),
    StartAttack     UMETA(DisplayName = "StartAttack"),
    HoldAttack      UMETA(DisplayName = "HoldAttack"),
    ReleaseAttack   UMETA(DisplayName = "ReleaseAttack"),
    ReleaseCast     UMETA(DisplayName = "ReleaseCast"),
    StartCast       UMETA(DisplayName = "StartCast")
};
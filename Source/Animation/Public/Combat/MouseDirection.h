#pragma once
#include "CoreMinimal.h"
#include "MouseDirection.generated.h"


UENUM(BlueprintType)
enum class EMouseDirection : uint8
{
    None        UMETA(DisplayName = "None"),
    Up          UMETA(DisplayName = "Up"),
    Down        UMETA(DisplayName = "Down"),
    Left        UMETA(DisplayName = "Left"),
    Right       UMETA(DisplayName = "Right"),
    UpRight     UMETA(DisplayName = "Up Right"),
    UpLeft      UMETA(DisplayName = "Up Left"),
    DownRight   UMETA(DisplayName = "Down Right"),
    DownLeft    UMETA(DisplayName = "Down Left")
};
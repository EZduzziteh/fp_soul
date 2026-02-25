#pragma once

#include "CoreMinimal.h"
#include "DamageClass.generated.h"

UENUM(BlueprintType)
enum class  EDamageClass : uint8
{
	Piercing	UMETA(DisplayName = "Piercing"),
	Bashing		UMETA(DisplayName = "Bashing"),
	Slashing	UMETA(DisplayName = "Slashing"),
	Burning		UMETA(DisplayName = "Burning"),
	Freezing	UMETA(DisplayName = "Freezing")
};
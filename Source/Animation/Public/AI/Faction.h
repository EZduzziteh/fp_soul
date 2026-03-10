#pragma once

#include "CoreMinimal.h"
#include "Faction.generated.h"

UENUM(BlueprintType)
enum class  EFaction : uint8
{
	Player	UMETA(DisplayName = "Player"),
	Townsfolk		UMETA(DisplayName = "Townsfolk"),
	Goblinfolk	UMETA(DisplayName = "Goblinfolk"),
	Undead		UMETA(DisplayName = "Undead"),
	Bandit	UMETA(DisplayName = "Bandit")
};
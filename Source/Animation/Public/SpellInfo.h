#pragma once

#include "CoreMinimal.h"
#include "SpellInfo.generated.h"

USTRUCT(BlueprintType)
struct ANIMATION_API FSpellInfo
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Name;
};

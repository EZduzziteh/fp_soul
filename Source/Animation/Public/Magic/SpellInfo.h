#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "SpellInfo.generated.h"

USTRUCT(BlueprintType)
struct ANIMATION_API FSpellInfo: public  FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Name;
};

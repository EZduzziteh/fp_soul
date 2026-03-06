#pragma once

#include "CoreMinimal.h"
#include "ArmourInfo.generated.h"

USTRUCT(BlueprintType)
struct ANIMATION_API FArmourInfo : public FTableRowBase
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "_Damage Reduction")
	int damageReduction;

};

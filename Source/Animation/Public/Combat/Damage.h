#pragma once

#include "CoreMinimal.h"
#include "DamageClass.h"
#include "Damage.generated.h"

USTRUCT(BlueprintType)
struct ANIMATION_API FDamage
{

	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EDamageClass DamageType = EDamageClass::Piercing;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Damage = 10.0f;
};
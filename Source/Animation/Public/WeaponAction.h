#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimMontage.h"
#include "DamageClass.h"
#include "Damage.h"
#include "WeaponAction.generated.h"

USTRUCT(BlueprintType)
struct ANIMATION_API FWeaponAction
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimMontage* Montage = nullptr;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FDamage damage;
};

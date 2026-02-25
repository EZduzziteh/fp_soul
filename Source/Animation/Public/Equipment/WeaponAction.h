#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimMontage.h"
#include "Combat/DamageClass.h"
#include "Combat/Damage.h"
#include "Engine/DataTable.h"
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

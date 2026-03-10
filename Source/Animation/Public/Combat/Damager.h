#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Combat/Damage.h"
#include "Damager.generated.h"

UINTERFACE(MinimalAPI)
class UDamager : public UInterface
{
    GENERATED_BODY()
};

class ANIMATION_API IDamager
{
    GENERATED_BODY()

public:

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
    FDamage GetDamage();
};
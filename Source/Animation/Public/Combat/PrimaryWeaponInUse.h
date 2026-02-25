#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "Characters/CombatCharacter.h"
#include "PrimaryWeaponInUse.generated.h"

/**
 * Toggles PrimaryAvailable on the owning character when the animation state begins/ends
 */
UCLASS()
class ANIMATION_API UPrimaryWeaponInUse : public UAnimNotifyState
{
    GENERATED_BODY()

public:

    virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override
    {
        if (!MeshComp) return;

        if (ACombatCharacter* Char = Cast<ACombatCharacter>(MeshComp->GetOwner()))
        {
            Char->PrimaryAvailable = false;
            UE_LOG(LogTemp, Log, TEXT("Primary weapon disabled"));
        }
    }

    virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override
    {
        if (!MeshComp) return;

        if (ACombatCharacter* Char = Cast<ACombatCharacter>(MeshComp->GetOwner()))
        {
            Char->PrimaryAvailable = true;
            UE_LOG(LogTemp, Log, TEXT("Primary weapon enabled"));
        }
    }
};

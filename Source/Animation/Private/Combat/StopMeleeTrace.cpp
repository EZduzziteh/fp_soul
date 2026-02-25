// Fill out your copyright notice in the Description page of Project Settings.


#include "Combat/StopMeleeTrace.h"

#include "Characters/CombatCharacter.h"

void UStopMeleeTrace::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
    if (ACombatCharacter* Character = Cast<ACombatCharacter>(MeshComp->GetOwner()))
    {
        Character->StopMeleeTrace();
    }
}

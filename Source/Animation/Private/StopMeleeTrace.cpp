// Fill out your copyright notice in the Description page of Project Settings.


#include "StopMeleeTrace.h"

#include "CombatCharacter.h"

void UStopMeleeTrace::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
    if (ACombatCharacter* Character = Cast<ACombatCharacter>(MeshComp->GetOwner()))
    {
        Character->StopMeleeTrace();
    }
}

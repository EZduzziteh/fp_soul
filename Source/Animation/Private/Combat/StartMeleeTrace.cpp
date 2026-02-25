// Fill out your copyright notice in the Description page of Project Settings.


#include "Combat/StartMeleeTrace.h"
#include "Characters/CombatCharacter.h"

void UStartMeleeTrace::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
    UE_LOG(LogTemp, Log, TEXT("notify"));
    UE_LOG(LogTemp, Warning, TEXT("AnimNotify triggered! Owner: %s"), *GetNameSafe(MeshComp->GetOwner()));
    if (ACombatCharacter* Character = Cast<ACombatCharacter>(MeshComp->GetOwner()))
    {
        UE_LOG(LogTemp, Warning, TEXT("Owner is CombatCharacter: %s"), *Character->GetName());
        if (!Character->GetMeleeTraceComponent())
        {
            UE_LOG(LogTemp, Error, TEXT("MeleeTraceComponent is NULL"));
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("MeleeTraceComponent is VALID: %s"), *Character->GetMeleeTraceComponent()->GetName());
            Character->StartMeleeTrace();
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Owner is not a CombatCharacter!"));
    }
}

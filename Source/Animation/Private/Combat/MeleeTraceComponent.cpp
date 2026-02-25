#include "Combat/MeleeTraceComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Combat/Damageable.h"
#include <Characters/CombatCharacter.h>

UMeleeTraceComponent::UMeleeTraceComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void UMeleeTraceComponent::BeginPlay()
{
    Super::BeginPlay();
}

void UMeleeTraceComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (bTracing)
    {
        PerformTrace();
    }
}

void UMeleeTraceComponent::StartTracing(const TArray<FTraceSource>& Sources)
{
    GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, "start tracing, source count "+Sources.Num());
    bTracing = true;
    AlreadyHit.Reset();
    TraceSources = Sources;

    // Initialize previous socket positions
    for (FTraceSource& Source : TraceSources)
    {
        if (!Source.Mesh) continue;

        Source.PreviousLocations.Reset();
        for (const FName& Socket : Source.Sockets)
        {
            Source.PreviousLocations.Add(Socket, Source.Mesh->GetSocketLocation(Socket));
        }
    }
}

void UMeleeTraceComponent::StopTracing()
{
    bTracing = false;
    TraceSources.Reset();
    AlreadyHit.Reset();
}

void UMeleeTraceComponent::PerformTrace()
{
    for (FTraceSource& Source : TraceSources)
    {
        if (!Source.Mesh) continue;

        for (const FName& Socket : Source.Sockets)
        {
            FVector Current = Source.Mesh->GetSocketLocation(Socket);
            FVector Previous = Source.PreviousLocations.FindRef(Socket);

            FHitResult Hit;
            FCollisionQueryParams Params;
            Params.AddIgnoredActor(GetOwner());

            bool bHit = GetWorld()->SweepSingleByChannel(
                Hit,
                Previous,
                Current,
                FQuat::Identity,
                ECC_Pawn, // Change or add channels as needed
                FCollisionShape::MakeSphere(TraceRadius),
                Params
            );

            // Debug visuals
            if (bDrawDebug)
            {
                DrawDebugLine(GetWorld(), Previous, Current, FColor::Red, false, 1.f);
                DrawDebugSphere(GetWorld(), Current, TraceRadius, 8, FColor::Green, false, 1.f);
            }
            if (bHit && Hit.GetActor())
            {
                UPrimitiveComponent* HitComp = Hit.GetComponent();

                // Check if hit component blocks attacks
                bool bBlocksAttack = HitComp && BlockingTags.ContainsByPredicate([HitComp](const FName& Tag) { return HitComp->ComponentHasTag(Tag); });


                if (bBlocksAttack)
                {
                    if (ACombatCharacter* OwnerChar = Cast<ACombatCharacter>(GetOwner()))
                    {
                        OwnerChar->InterruptPrimaryAttack(); // You’ll implement this in your character
                    }

                    StopTracing(); // Stop tracing immediately
                    return;
                }

                bool bDamageable = HitComp && DamageableTags.ContainsByPredicate(
                    [HitComp](const FName& Tag) { return HitComp->ComponentHasTag(Tag); });

                if (bDamageable)
                {
                    AActor* HitActor = Hit.GetActor();

                    if (!AlreadyHit.Contains(HitActor))
                    {
                        AlreadyHit.Add(HitActor);

                        if (HitActor->Implements<UDamageable>())
                        {
                            IDamageable::Execute_ReceiveDamage(HitActor, GetOwner(), Hit);
                        }
                    }
                }

            }



            // Update socket location for next frame
            Source.PreviousLocations[Socket] = Current;
        }
    }
}

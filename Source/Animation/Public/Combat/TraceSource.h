#pragma once


#include "CoreMinimal.h"
#include "TraceSource.generated.h"

USTRUCT()
struct FTraceSource
{
    GENERATED_BODY()

    UPROPERTY()
    USkeletalMeshComponent* Mesh = nullptr;

    UPROPERTY()
    TArray<FName> Sockets;

    // Socket name → previous world location
    TMap<FName, FVector> PreviousLocations;
};
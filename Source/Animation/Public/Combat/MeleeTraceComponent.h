#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TraceSource.h"
#include "MeleeTraceComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ANIMATION_API UMeleeTraceComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug")
      bool bDrawDebug = false;
    UMeleeTraceComponent();

    // Start tracing from multiple trace sources
    void StartTracing(const TArray<FTraceSource>& Sources);

    // Stop tracing and clear stored hits
    void StopTracing();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trace")
    TArray<FName> DamageableTags = { "Damageable" };

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trace")
    TArray<FName> BlockingTags = { "BlockAttack" };



protected:
    virtual void BeginPlay() override;
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
    void PerformTrace();

    // Active tracing flag
    bool bTracing = false;

    // Actors already hit during the current trace session
    UPROPERTY()
    TSet<AActor*> AlreadyHit;

    // List of currently active trace sources
    UPROPERTY()
    TArray<FTraceSource> TraceSources;

    // Sphere radius for trace
    UPROPERTY(EditDefaultsOnly, Category = "Trace")
    float TraceRadius = 8.f;



};

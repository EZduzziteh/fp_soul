#pragma once

#include "CoreMinimal.h"
#include "NPCDialogue.generated.h"

USTRUCT(BlueprintType)
struct FNPCDialogue
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
    FName NPCName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
    FString DialogueText;
};

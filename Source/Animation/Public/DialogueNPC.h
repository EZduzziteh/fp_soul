#pragma once

#include "CoreMinimal.h"
#include "DialogueTopic.h"
#include "DialogueNPC.generated.h"

USTRUCT(BlueprintType)
struct FDialogueNPC : public FTableRowBase
{
    GENERATED_BODY()

   
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
    TArray<FDialogueTopic> Topics;
};

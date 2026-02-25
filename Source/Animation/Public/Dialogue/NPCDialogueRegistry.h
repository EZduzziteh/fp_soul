#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "NPCDialogueRegistry.generated.h"

USTRUCT(BlueprintType)
struct ANIMATION_API FNPCDialogueRegistryRow : public FTableRowBase
{
    GENERATED_BODY()

public:

    // The per-NPC dialogue table
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UDataTable* NPCTopicTable;



};
#pragma once

#include "CoreMinimal.h"
#include "Inventory/Item_Quantity.h"
#include "Engine/DataTable.h"
#include "DialogueActions.generated.h"

USTRUCT(BlueprintType)
struct ANIMATION_API FDialogueActionGive : public FTableRowBase
{
    GENERATED_BODY()

public:

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FItem_Quantity ItemQuantity;
};

USTRUCT(BlueprintType)
struct ANIMATION_API FDialogueActionUnlock : public FTableRowBase
{
    GENERATED_BODY()

public:

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FName> TopicNames;
};

USTRUCT(BlueprintType)
struct ANIMATION_API FDialogueActionTake : public FTableRowBase
{
    GENERATED_BODY()

public:

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FItem_Quantity ItemQuantity;
};

USTRUCT(BlueprintType)
struct ANIMATION_API FDialogueActionEnd : public FTableRowBase
{
    GENERATED_BODY()

public:

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bEnd = false;
};
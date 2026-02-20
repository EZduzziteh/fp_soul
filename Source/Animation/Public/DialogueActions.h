#pragma once

#include "CoreMinimal.h"
#include "DialogueActions.generated.h"

USTRUCT(BlueprintType)
struct ANIMATION_API FDialogueAGive
{
    GENERATED_BODY()
};

USTRUCT(BlueprintType)
struct ANIMATION_API FDialogueAUnlock
{
    GENERATED_BODY()
};

USTRUCT(BlueprintType)
struct ANIMATION_API FDialogueTake
{
    GENERATED_BODY()
};

USTRUCT(BlueprintType)
struct ANIMATION_API FDialogueEnd
{
    GENERATED_BODY()

public:

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bEnd = false;
};

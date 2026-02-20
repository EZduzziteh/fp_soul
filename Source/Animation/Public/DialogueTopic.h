#pragma once

#include "CoreMinimal.h"
#include "DialogueLines.h"
#include "DialogueTopic.generated.h"

USTRUCT(BlueprintType)
struct ANIMATION_API FDialogueTopic
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FDialogueLine> Lines;
};
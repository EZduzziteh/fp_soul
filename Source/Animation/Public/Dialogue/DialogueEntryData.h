#pragma once

#include "CoreMinimal.h"
#include "DialogueEntryData.generated.h"

USTRUCT(BlueprintType)
struct ANIMATION_API FDialogueEntryData {
	GENERATED_BODY()

	FText speakerName;
	FText speakerText;

};
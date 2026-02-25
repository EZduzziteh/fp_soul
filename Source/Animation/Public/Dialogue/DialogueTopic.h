#pragma once

#include "CoreMinimal.h"
#include "Dialogue.h"
#include "Engine/DataTable.h"
#include "DialogueTopic.generated.h"

USTRUCT(BlueprintType)
struct ANIMATION_API FDialogueTopic : public FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FDialogue Line;
};
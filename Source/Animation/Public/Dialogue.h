// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"	
#include "Engine/DataTable.h"
#include "Sound/SoundBase.h"
#include"Dialogue.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct ANIMATION_API FDialogue : public FTableRowBase
{

	GENERATED_BODY()
	public:



	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Text;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundBase* Audio;
};

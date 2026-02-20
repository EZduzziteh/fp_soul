// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"	
#include "Sound/SoundBase.h"
#include"DialogueLines.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct ANIMATION_API FDialogueLine
{

	GENERATED_BODY()
	public:



	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Text;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundBase* Audio;
};

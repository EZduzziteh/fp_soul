// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_Hud.generated.h"

/**
 * 
 */
UCLASS()
class ANIMATION_API UWidget_Hud : public UUserWidget
{
	GENERATED_BODY()

public:
    UPROPERTY(meta = (BindWidget))
    class UTextBlock* MyText;

    void SetText(const FString& NewText);
};


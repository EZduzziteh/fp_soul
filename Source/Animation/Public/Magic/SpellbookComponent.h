// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SpellbookComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ANIMATION_API USpellbookComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USpellbookComponent();

protected:

public:	
	// Dynamic list of known spell names
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Spells")
	TArray<FString> KnownSpells;	
	// Example function to add a new spell
	UFUNCTION(BlueprintCallable, Category = "Spells")
	void LearnSpell(const FString& SpellName);
		
};

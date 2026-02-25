// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ANIMATION_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

protected:

public:

	// Dynamic list of known spell names
	UPROPERTY(BlueprintReadOnly,  Category = "Spells")
	TArray<FString> itemIDs;

	// Dynamic list of known spell names
	UPROPERTY(BlueprintReadOnly,  Category = "Spells")
	TArray<int> itemCounts;
	// Example function to add a new spell

	UFUNCTION(BlueprintCallable, Category = "_Inventory")
	void AddItem(const FString& itemID, int itemQuantity);

	UFUNCTION(BlueprintCallable, Category = "_Inventory")
	void RemoveItem(const FString& itemID, int itemQuantity);

		
};

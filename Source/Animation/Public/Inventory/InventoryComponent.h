// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Inventory/DA_Item_Base.h"
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
	UPROPERTY(BlueprintReadOnly)
	TArray<const UDA_Item_Base*> Items;

	// Dynamic list of known spell names
	UPROPERTY(BlueprintReadOnly)
	TArray<int> ItemCounts;
	// Example function to add a new spell

	UFUNCTION(BlueprintCallable, Category = "_Inventory")
	void AddItem(UDA_Item_Base* item, int itemQuantity);

	UFUNCTION(BlueprintCallable, Category = "_Inventory")
	void RemoveItem(UDA_Item_Base* item, int itemQuantity);

		
};

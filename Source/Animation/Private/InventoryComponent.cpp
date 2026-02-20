// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UInventoryComponent::AddItem(const FString& itemID, int itemQuantity)
{

	if (itemIDs.Contains(itemID)) {
		//increment if we already have this item
		int index = itemIDs.IndexOfByKey(itemID);
		itemCounts[index] = itemCounts[index] + itemQuantity;
	}
	else {
		//Add new if we dont already have this item
		itemIDs.AddUnique(itemID);
		itemCounts.Add(itemQuantity);

	}

}

void UInventoryComponent::RemoveItem(const FString& itemID, int itemQuantity)
{
	if (itemIDs.Contains(itemID)) {
		//increment if we already have this item
		int index = itemIDs.IndexOfByKey(itemID);
		itemCounts[index] = itemCounts[index] - itemQuantity;
		if (itemCounts[index] <= 0) {
			itemCounts.RemoveAt(index);
			itemIDs.RemoveAt(index);;
		}
	}
	else {

		//Item doesn't exist in inventory - dont do anything? 

	}
}







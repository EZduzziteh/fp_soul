// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/InventoryComponent.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UInventoryComponent::AddItem(UDA_Item_Base* item, int itemQuantity)
{

	if (Items.Contains(item)) {
		//increment if we already have this item
		int index = Items.IndexOfByKey(item);
		ItemCounts[index] = ItemCounts[index] + itemQuantity;
	}
	else {
		//Add new if we dont already have this item
		Items.AddUnique(item);
		ItemCounts.Add(itemQuantity);

	}

}

void UInventoryComponent::RemoveItem(UDA_Item_Base* item, int itemQuantity)
{
	if (Items.Contains(item)) {
		//increment if we already have this item
		int index = Items.IndexOfByKey(item);
		ItemCounts[index] = ItemCounts[index] - itemQuantity;
		if (ItemCounts[index] <= 0) {
			ItemCounts.RemoveAt(index);
			Items.RemoveAt(index);;
		}
	}
	else {

		//Item doesn't exist in inventory - dont do anything? 

	}
}







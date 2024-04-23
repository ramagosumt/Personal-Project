// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/MainInventoryComponent.h"
#include "Items/ItemBase.h"

// Sets default values for this component's properties
UMainInventoryComponent::UMainInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMainInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

UItemBase* UMainInventoryComponent::FindMatchingItem(UItemBase* ItemIn) const
{
	if (ItemIn)
	{
		if (Inventory.Contains(ItemIn))
		{
			return ItemIn;
		}
	}

	return nullptr;
}

FInventoryChangeResult UMainInventoryComponent::AddItem(UItemBase* ItemIn)
{
	if (GetOwner())
	{
		return HandleNonStackableItems(ItemIn);
	}

	check(false);
	return FInventoryChangeResult::AddedNone(FText::FromString("Hahan't."));
}

void UMainInventoryComponent::RemoveItem(UItemBase* ItemOut)
{
	Inventory.RemoveSingle(ItemOut);
	OnInventoryUpdated.Broadcast();
}

FInventoryChangeResult UMainInventoryComponent::HandleNonStackableItems(UItemBase* ItemIn)
{
	// Checks if adding one more item would overflow slot capacity
	if (Inventory.Num() + 1 > MaxInventorySlotAmount)
	{
		return FInventoryChangeResult::AddedNone(FText::Format(FText::FromString("Could not add {0} to the inventory. All inventory slots are full."), ItemIn->TextData.Name));
	}

	AddNewItem(ItemIn);
	return FInventoryChangeResult::AddedAll(1, FText::Format(FText::FromString("Successfully added {0} {1} to the inventory."), 1, ItemIn->TextData.Name));
}

void UMainInventoryComponent::AddNewItem(UItemBase* ItemIn)
{
	UItemBase* NewItem;
	if (ItemIn->bIsCopy || ItemIn->bIsObtainable)
	{
		// if the item is already a copy, or a world pickup
		NewItem = ItemIn;
		NewItem->ResetItemFlag();
	}
	else
	{
		// use when dragging or splitting to/from another inventory
		NewItem = ItemIn->CreateItemCopy();
	}

	NewItem->OwningInventory = this;
	NewItem->SetQuantity(1);

	Inventory.Add(NewItem);
	OnInventoryUpdated.Broadcast();
}

#include "Items/ItemBase.h"
#include "Components/MainInventoryComponent.h"

UItemBase::UItemBase() :
	OwningInventory(nullptr),
	ID(FName()), Quantity(0), 
	ItemTier(EItemTier::Tier_1), ItemType(),
	ItemStatistics(), TextData(), NumericData(), AssetData(),
	bIsCopy(false), bIsObtainable(false)
{}

void UItemBase::ResetItemFlag()
{
	bIsCopy = false;
	bIsObtainable = false;
}

UItemBase* UItemBase::CreateItemCopy() const
{
	// Creates a new UItemBase pointer to object then returns it
	UItemBase* ItemCopy = NewObject<UItemBase>(StaticClass());

	ItemCopy->ID = this->ID;
	ItemCopy->Quantity = this->Quantity;
	ItemCopy->ItemTier = this->ItemTier;
	ItemCopy->ItemType = this->ItemType;
	ItemCopy->ItemStatistics = this->ItemStatistics;
	ItemCopy->TextData = this->TextData;
	ItemCopy->NumericData = this->NumericData;
	ItemCopy->AssetData = this->AssetData;
	
	ItemCopy->bIsCopy = true;

	return ItemCopy;
}

void UItemBase::SetQuantity(const int32 NewQuantity)
{
	// Set the max stack size of an item to an already set number if the item is stackable, else set to 1
	if (NewQuantity != Quantity) Quantity = FMath::Clamp(NewQuantity, 0, NumericData.bIsStackable ? NumericData.MaxStackSize : 1);
	if (OwningInventory) if (Quantity <= 0) OwningInventory->RemoveItem(this); // If the quantity is 0 or less, remove item in the owning inventory
}

void UItemBase::Use(AMainCharacter* Character)
{
	
}

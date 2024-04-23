/** Creates instances for InventoryDataStructs.h
 *	Can duplicate an item in ItemData
 *	Can calculate the weight of multiple items in ItemData
 *	Can count the max stack size of any item in ItemData
 *	Can count the current quantity size of any item in ItemData
 *	Knows how an item in ItemData can be used
 *	Can compare two FNames
 */

#pragma once

#include "CoreMinimal.h"
#include "Data/InventoryDataStructs.h"
#include "Player/MainCharacter.h"
#include "ItemBase.generated.h"

class UMainInventoryComponent;

/**
 * 
 */
UCLASS()
class ACAADV4_API UItemBase : public UObject
{
	GENERATED_BODY()

public:
	
	/**
	 * PROPERTIES AND VARIABLES
	 **/
	
	UPROPERTY()
	UMainInventoryComponent* OwningInventory; // A reference to the inventory that owns this item

	UPROPERTY(VisibleAnywhere, Category= "Item")
	FName ID;
	
	UPROPERTY(VisibleAnywhere, Category= "Item")
	int32 Quantity; // The actual quantity of this item

	UPROPERTY(VisibleAnywhere, Category= "Item")
	EItemTier ItemTier;

	UPROPERTY(VisibleAnywhere, Category= "Item")
	EItemType ItemType;

	UPROPERTY(VisibleAnywhere, Category= "Item")
	FItemStatistics ItemStatistics;

	UPROPERTY(VisibleAnywhere, Category= "Item")
	FItemTextData TextData;

	UPROPERTY(VisibleAnywhere, Category= "Item")
	FItemNumericData NumericData;

	UPROPERTY(VisibleAnywhere, Category= "Item")
	FItemAssetData AssetData;

	UPROPERTY(VisibleAnywhere, Category= "Item")
	TArray<FText> DialogueMessages;

	bool bIsCopy;
	bool bIsObtainable;

	/**
	 * FUNCTIONS
	 **/
	
	UItemBase();
	
	void ResetItemFlag(); // Manipulate the boolean attributes of this item

	UFUNCTION(Category= "Item")
	UItemBase* CreateItemCopy() const;

	UFUNCTION(Category= "Item")
	FORCEINLINE float GetItemStackWeight() const { return Quantity * NumericData.Weight; };

	UFUNCTION(Category= "Item")
	FORCEINLINE float GetItemSingleWeight() const { return NumericData.Weight; };

	UFUNCTION(Category= "Item")
	FORCEINLINE bool IsFullItemStack() const { return Quantity == NumericData.MaxStackSize; };

	UFUNCTION(Category= "Item")
	void SetQuantity(const int32 NewQuantity);

	UFUNCTION(Category= "Item")
	virtual void Use(AMainCharacter* Character);

protected:

	bool operator==(const FName& OtherID) const
	{
		return this->ID == OtherID;
	}
};

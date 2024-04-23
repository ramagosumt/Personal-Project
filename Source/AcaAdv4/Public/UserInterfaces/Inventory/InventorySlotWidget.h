// Inventory Slot User-Interface

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventorySlotWidget.generated.h"

class UItemBase;
class UTextBlock;
class UBorder;

/**
 * 
 */
UCLASS()
class ACAADV4_API UInventorySlotWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	
	FORCEINLINE void SetItemReference(UItemBase* ItemIn) { ItemReference = ItemIn; }
	FORCEINLINE UItemBase* GetItemReference() const { return ItemReference; }

	FORCEINLINE UBorder* GetItemBorder() const { return ItemBorder; }

protected:

	// A reference to whatever item is in the slot
	UPROPERTY(VisibleAnywhere, Category= "InventorySlot")
	UItemBase* ItemReference;

	// Displays item borders
	UPROPERTY(VisibleAnywhere, Category= "InventorySlot", meta=(BindWidget))
	UBorder* ItemBorder;

	// Displays items for players
	UPROPERTY(VisibleAnywhere, Category= "InventorySlot", meta=(BindWidget))
	UTextBlock* ItemName;

	// BeginPlay()
	virtual void NativeOnInitialized() override;

	// Constructor
	virtual void NativeConstruct() override;
};

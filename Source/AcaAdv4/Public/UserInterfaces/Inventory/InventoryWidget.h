// Inventory User-Interface

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryWidget.generated.h"

class AMainCharacter;
class UMainInventoryComponent;
class UVerticalBox;
class UInventorySlotWidget;
class UBorder;

/**
 * 
 */
UCLASS()
class ACAADV4_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	
	// A reference to the main character
	UPROPERTY()
	AMainCharacter* MainCharacter;

	// A reference to the main inventory
	UPROPERTY()
	UMainInventoryComponent* MainInventory;

	// A wrap box that acts as the real inventory array
	UPROPERTY(meta=(BindWidget))
	UVerticalBox* InventoryUI;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UInventorySlotWidget> DesiredInventorySlotUI;
	
	UPROPERTY()
	UInventorySlotWidget* CurrentInventorySlot;

	// Refreshes the UI
	UFUNCTION()
	void RefreshInventory();

	// Toggles UInventorySlotWidget::ItemBorder
	void ToggleSlotBorder(const int8 Index);
	
protected:
	
	virtual void NativeOnInitialized() override;
	
};

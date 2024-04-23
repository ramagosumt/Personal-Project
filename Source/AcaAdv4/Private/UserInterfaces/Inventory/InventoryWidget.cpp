#include "UserInterfaces/Inventory/InventoryWidget.h"
#include "Components/Border.h"
#include "Player/MainCharacter.h"
#include "UserInterfaces/Inventory/InventorySlotWidget.h"
#include "Components/VerticalBox.h"

void UInventoryWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	MainCharacter = Cast<AMainCharacter>(GetOwningPlayerPawn());
	if (MainCharacter)
	{
		MainInventory = MainCharacter->GetInventory();
		if (MainInventory)
		{
			MainInventory->OnInventoryUpdated.AddUObject(this, &UInventoryWidget::RefreshInventory);
		}
	}
}

void UInventoryWidget::RefreshInventory()
{
	if (MainInventory && DesiredInventorySlotUI)
	{
		InventoryUI->ClearChildren();
		for (UItemBase* const& InventoryItem : MainInventory->GetInventory())
		{
			UInventorySlotWidget* InventorySlot = CreateWidget<UInventorySlotWidget>(this, DesiredInventorySlotUI);
			InventorySlot->SetItemReference(InventoryItem);
			InventoryUI->AddChildToVerticalBox(InventorySlot);
		}
	}
}

void UInventoryWidget::ToggleSlotBorder(const int8 Index)
{
	if (CurrentInventorySlot)
	{
		UBorder* CurrentItemBorder = Cast<UBorder>(CurrentInventorySlot->GetItemBorder());
		if (CurrentItemBorder)
		{
			CurrentItemBorder->SetIsEnabled(false);
		}
	}
	
	CurrentInventorySlot = Cast<UInventorySlotWidget>(InventoryUI->GetChildAt(Index));
	if (CurrentInventorySlot)
	{
		UBorder* CurrentItemBorder = Cast<UBorder>(CurrentInventorySlot->GetItemBorder());
		if (CurrentItemBorder)
		{
			CurrentItemBorder->SetIsEnabled(true);
		}
	}
}

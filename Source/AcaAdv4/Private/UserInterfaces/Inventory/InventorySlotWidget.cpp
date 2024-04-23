#include "UserInterfaces/Inventory/InventorySlotWidget.h"
#include "Components/Border.h"
#include "Components/TextBlock.h"
#include "Items/ItemBase.h"

void UInventorySlotWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UInventorySlotWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (ItemReference)
	{
		ItemBorder->SetIsEnabled(false);
		
		ItemName->SetText(ItemReference->TextData.Name);
		ItemName->SetJustification(ETextJustify::Center);
	}
}

#include "World/ItemToObtain.h"
#include "Items/ItemBase.h"
#include "UserInterfaces/MainHUD.h"

AItemToObtain::AItemToObtain():
	InventoryTable(nullptr),
	ItemQuantity(0), ItemReference(nullptr)
{
	// Tag for obtaining
	MainMesh->ComponentTags.Add(TEXT("EligibleForObtaining"));
}

void AItemToObtain::BeginPlay()
{
	Super::BeginPlay();

	InitializePickup(UItemBase::StaticClass(), ItemQuantity);
}

void AItemToObtain::Interact(AMainCharacter* MainCharacter)
{
	if (MainCharacter)
	{
		if (InventoryTable && !DesiredInventoryID.IsNone()) OpenDialogue(MainCharacter);
			else ObtainedBy(MainCharacter);
	}
}

void AItemToObtain::InitializePickup(const TSubclassOf<UItemBase> BaseClass, const int32 Quantity)
{
	if (InventoryTable && !DesiredInventoryID.IsNone())
	{
		const FInventoryData* InventoryData = InventoryTable->FindRow<FInventoryData>(DesiredInventoryID, DesiredInventoryID.ToString());

		ItemReference = NewObject<UItemBase>(this, BaseClass);

		ItemReference->ID = InventoryData->ID;
		ItemReference->ItemTier = InventoryData->ItemTier;
		ItemReference->ItemType = InventoryData->ItemType;
		ItemReference->ItemStatistics = InventoryData->ItemStatistics;
		ItemReference->AssetData = InventoryData->AssetData;
		ItemReference->TextData = InventoryData->TextData;
		ItemReference->NumericData = InventoryData->NumericData;
		ItemReference->DialogueMessages = InventoryData->TextData.DialogueMessages;

		Quantity <= 0 ? ItemReference->SetQuantity(1) : ItemReference->SetQuantity(Quantity);

		MainMesh->SetStaticMesh(InventoryData->AssetData.Mesh);

		UpdateInteractableData();
	}
}

void AItemToObtain::InitializeDrop(UItemBase* ItemToDrop, const int32 Quantity)
{
	ItemReference = ItemToDrop;

	Quantity <= 0 ? ItemReference->SetQuantity(1) : ItemReference->SetQuantity(Quantity);
	
	ItemReference->NumericData.Weight = ItemToDrop->GetItemSingleWeight();
	
	MainMesh->SetStaticMesh(ItemToDrop->AssetData.Mesh);

	UpdateInteractableData();
}

void AItemToObtain::OpenDialogue(const AMainCharacter* Taker)
{
	if (!IsPendingKillPending())
	{
		Taker->UpdateDialogueWidget();
		Taker->GetHUD()->OnDialogueEndOneParam.AddUObject(this, &AItemToObtain::ObtainedBy);
	}
}

void AItemToObtain::ObtainedBy(AMainCharacter* Taker)
{
	if (!IsPendingKillPending())
	{
		if (ItemReference)
		{
			if (UMainInventoryComponent* MainInventory = Taker->GetInventory())
			{
				const FInventoryChangeResult InventoryChangeResult = MainInventory->AddItem(ItemReference);

				switch (InventoryChangeResult.OperationResult)
				{
				case EInventoryChangeResult::IAR_NoItemAdded:
					break;
				case EInventoryChangeResult::IAR_AllItemAdded:
					Destroy();
					break;
				default:
					;
				}

				UE_LOG(LogTemp, Warning, TEXT("%s"), *InventoryChangeResult.ResultMessage.ToString());
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("PlayerInventoryComponent is null"));
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Pickup internal item reference was somehow null"));
		}
	}	
}

void AItemToObtain::UpdateInteractableData()
{
	InstanceInteractableData.ItemInteractionMode = EItemInteractionMode::ObtainableItem;
	InstanceInteractableData.Action = ItemReference->TextData.InteractionText;
	InstanceInteractableData.Name = ItemReference->TextData.Name;
	InstanceInteractableData.DialogueMessages = ItemReference->TextData.DialogueMessages;
	InstanceInteractableData.Quantity = ItemReference->Quantity;
	
	InteractableData = InstanceInteractableData;
}

#if WITH_EDITOR
void AItemToObtain::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	const FName ChangedPropertyName = PropertyChangedEvent.Property ? PropertyChangedEvent.Property->GetFName() : NAME_None;

	if (ChangedPropertyName == GET_MEMBER_NAME_CHECKED(AItemToObtain, DesiredInventoryID))
	{
		if (InventoryTable)
		{
			if (const FInventoryData* InventoryData = InventoryTable->FindRow<FInventoryData>(DesiredInventoryID, DesiredInventoryID.ToString()))
			{
				MainMesh->SetStaticMesh(InventoryData->AssetData.Mesh);
			}
		}
	}
}
#endif
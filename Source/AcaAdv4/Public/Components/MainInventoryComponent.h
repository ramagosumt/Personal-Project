// The Main Inventory actor component

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MainInventoryComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnInventoryUpdated)

class UItemBase;

// Enum representing the current state of changing within the inventory
UENUM(BlueprintType)
enum class EInventoryChangeResult : uint8
{
	IAR_NoItemAdded UMETA(DisplayName= "No Item Added"),
	IAR_AllItemAdded UMETA(DisplayName= "All Item Added")
};

// Struct representing the data about the current state of changing within the inventory
USTRUCT(BlueprintType)
struct FInventoryChangeResult
{
	GENERATED_BODY()

	FInventoryChangeResult() :
	ActualAmountAdded(0),
	OperationResult(EInventoryChangeResult::IAR_NoItemAdded),
	ResultMessage(FText::GetEmpty())
	{};

	// Actual amount of item that was added to the inventory
	UPROPERTY(BlueprintReadOnly, Category= "Item Add Result")
	int32 ActualAmountAdded;

	// Enum representing the end state of an inventory changing operation
	UPROPERTY(BlueprintReadOnly, Category= "Item Add Result")
	EInventoryChangeResult OperationResult;

	// Informational message that can be passed with result
	UPROPERTY(BlueprintReadOnly, Category= "Item Add Result")
	FText ResultMessage;

	// When no item added to the inventory
	static FInventoryChangeResult AddedNone(const FText& ErrorText)
	{
		FInventoryChangeResult AddedNoneResult;
		
		AddedNoneResult.ActualAmountAdded = 0;
		AddedNoneResult.OperationResult = EInventoryChangeResult::IAR_NoItemAdded;
		AddedNoneResult.ResultMessage = ErrorText;

		return AddedNoneResult;
	};

	// When the total amount of item added to the inventory
	static FInventoryChangeResult AddedAll(const int32 AmountAdded, const FText& Message)
	{
		FInventoryChangeResult AddedAllResult;
		
		AddedAllResult.ActualAmountAdded = AmountAdded;
		AddedAllResult.OperationResult = EInventoryChangeResult::IAR_AllItemAdded;
		AddedAllResult.ResultMessage = Message;

		return AddedAllResult;
	};
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACAADV4_API UMainInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	/**
	 * PROPERTIES AND VARIABLES
	 **/

	// An instance for delegation command
	FOnInventoryUpdated OnInventoryUpdated;

	/**
	 * FUNCTIONS
	 **/
	
	// Sets default values for this component's properties
	UMainInventoryComponent();

	// Finds if an item is already on the inventory
	UFUNCTION(Category= "Inventory")
	UItemBase* FindMatchingItem(UItemBase* ItemIn) const;

	// Adds a new item into the inventory
	UFUNCTION(Category= "Inventory")
	FInventoryChangeResult AddItem(UItemBase* InputItem);

	// Remove an item out of the inventory
	UFUNCTION(Category= "Inventory")
	void RemoveItem(UItemBase* ItemOut);

	// Gets the inventory itself
	UFUNCTION(Category= "Inventory")
	FORCEINLINE TArray<UItemBase*> GetInventory() { return Inventory; }

	// Gets the current wielding inventory item
	UFUNCTION(Category= "Inventory")
	FORCEINLINE int8 GetInventoryIndex() const { return InventoryIndex; }

	// Gets the maximum slot amount of an inventory
	UFUNCTION(Category= "Inventory")
	FORCEINLINE int32 GetMaxSlotAmount() const { return MaxInventorySlotAmount; }

	// Sets the current wielding inventory item
	FORCEINLINE void SetInventoryIndex(const int8 NewInventoryIndex) { InventoryIndex = NewInventoryIndex; }

	// Sets the maximum slot amount of an inventory
	FORCEINLINE void SetMaxSlotAmount(const int32 NewMaxSlotAmount) { MaxInventorySlotAmount = NewMaxSlotAmount; }

protected:
	
	/**
	 * PROPERTIES AND VARIABLES
	 **/

	// The total amount of item slot that an inventory can hold
	UPROPERTY(EditInstanceOnly, Category= "Inventory")
	int32 MaxInventorySlotAmount;

	// The actual inventory itself
	UPROPERTY(VisibleAnywhere, Category= "Inventory")
	TArray<UItemBase*> Inventory;

	// The current wielding inventory item index
	UPROPERTY(VisibleAnywhere, Category= "Inventory")
	int8 InventoryIndex;

	/**
	 * FUNCTIONS
	 **/
	
	// Called when the game starts
	virtual void BeginPlay() override;

	// Handles adding item into the inventory
	FInventoryChangeResult HandleNonStackableItems(UItemBase* ItemIn);

	// The actual function to add item into the inventory
	void AddNewItem(UItemBase* Item);
};

/** The interact-able Item Actor in the game
 *	Can be focused and outlined
 *	Can be interacted
 *	Can be obtained
 */

#pragma once

#include "CoreMinimal.h"
#include "World/ItemToInteract.h"
#include "ItemToObtain.generated.h"

class UItemBase;
class UDataTable;

/**
 * 
 */
UCLASS()
class ACAADV4_API AItemToObtain : public AItemToInteract
{
	GENERATED_BODY()

public:

	/**
	 * FUNCTIONS
	 **/
	
	AItemToObtain();
	
	void InitializePickup(const TSubclassOf<UItemBase> BaseClass, const int32 Quantity); // Initialize item instance if currently presenting in the actual level
	void InitializeDrop(UItemBase* ItemToDrop, const int32 Quantity); // Initialize item instance after being drop by the player
	
	FORCEINLINE UItemBase* GetItemData() const { return ItemReference; } // Return a reference to the actual item instance
	FORCEINLINE UStaticMeshComponent* GetMainMeshComponent() const { return MainMesh; } // Get the item main mesh component

protected:

	/**
	 * PROPERTIES AND VARIABLES
	 **/
	
	UPROPERTY(EditInstanceOnly, Category= "Item | Initialization")
	UDataTable* InventoryTable; // The data table of the actual item instance
	
	UPROPERTY(EditInstanceOnly, Category= "Item | Initialization")
	FName DesiredInventoryID; // The ID of an actual item instance

	UPROPERTY(EditInstanceOnly, Category= "Item | Initialization")
	int32 ItemQuantity; // The quantity of this item
	
	UPROPERTY(VisibleAnywhere, Category= "Item | Reference")
	UItemBase* ItemReference; // A reference to the actual item instance
	
	UPROPERTY(VisibleInstanceOnly, Category= "Item | Interaction")
	FInteractableData InstanceInteractableData; // A copy of the interact-able data of an item instance

	/**
	 * FUNCTIONS
	 **/
	
	virtual void BeginPlay() override; // Called when the game starts or when spawned
	
	virtual void Interact(AMainCharacter* MainCharacter) override; // Called when the main character interact with this actor
	
	void UpdateInteractableData(); // Update the FInteract-ableData from IInteractionInterface with attributes from ItemReference
	
	void OpenDialogue(const AMainCharacter* Taker); // Create the dialogue widget
	void ObtainedBy(AMainCharacter* Taker); // By which main character does this actor obtained

	// To help the engine understand that when I'm changing an actor in the editor, that actor will also changed immediately in the viewport
	#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	#endif
};

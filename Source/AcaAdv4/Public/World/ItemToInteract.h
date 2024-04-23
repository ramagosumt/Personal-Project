/** The interact-able Item Actor in the game
 *	Can be focused and outlined
 *	Can be interacted
 */

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/InteractionInterface.h"
#include "World/ItemNotToInteract.h"
#include "ItemToInteract.generated.h"

#define ECC_Interactable ECC_GameTraceChannel2 // User-defined collision channel in Project Setting

class UDataTable;
class AMainCharacter;
struct FDialogueData;

/**
 * 
 */
UCLASS()
class ACAADV4_API AItemToInteract : public AItemNotToInteract, public IInteractionInterface
{
	GENERATED_BODY()

public:

	/**
	 * PROPERTIES AND VARIABLES
	 **/

	/** Dialogues */
	
	UPROPERTY(EditAnywhere, Category= "Item | Initialization")
	UDataTable* DialogueTable; // The data table for dialogues

	UPROPERTY(EditAnywhere, Category= "Item | Dialogues")
	FName DesiredDialogueID; // The ID for dialogues
	
	FDialogueData* DialogueData; // A copy of the dialogue data for dialogues

	/**
	 * FUNCTIONS
	 **/
	
	AItemToInteract();

protected:

	/**
	 * FUNCTIONS
	 **/
	
	virtual void BeginPlay() override; // Called when the game starts or when spawned

	virtual void BeginFocus() override; // Starts line tracing
	virtual void EndFocus() override; // Ends line tracing
	virtual void Interact(AMainCharacter* MainCharacter) override; // Called when the main character interact with this actor
};

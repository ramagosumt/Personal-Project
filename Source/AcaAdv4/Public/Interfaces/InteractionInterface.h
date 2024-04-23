/** Creates an interface for the main character and an item in ItemData
 *	Stores variables that would be displayed when the main character look at an item
 *	Stores virtual functions
 *		What an item would act when the main character turn their focus to it
 *		What an item would act when the main character interact with it
 */

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractionInterface.generated.h"

class AMainCharacter;

// The interaction mode of an item
UENUM()
enum class EItemInteractionMode : uint8
{
	ObtainableItem UMETA(DisplayName= "ObtainableItem"),
	NPC UMETA(DisplayName= "NPC"),
	Device UMETA(DisplayName= "Device"),
	Toggle UMETA(DisplayName= "Toggle"),
	Container UMETA(DisplayName= "Container")
};

// The interactable data of an item
USTRUCT()
struct FInteractableData
{
	GENERATED_BODY()

	FInteractableData() :
	ItemInteractionMode(EItemInteractionMode::ObtainableItem),
	Name(FText::GetEmpty()),
	Action(FText::GetEmpty()),
	Quantity(0),
	ItemInteractionDuration(0.0f)
	{
		
	};

	UPROPERTY(EditInstanceOnly)
	EItemInteractionMode ItemInteractionMode;

	UPROPERTY(EditInstanceOnly)
	FText Name;

	UPROPERTY(EditInstanceOnly)
	FText Action;

	UPROPERTY(EditInstanceOnly)
	TArray<FText> DialogueMessages;

	// Used for obtainable items
	UPROPERTY(EditInstanceOnly)
	uint8 Quantity;

	// Used for devices and toggles 
	UPROPERTY(EditInstanceOnly)
	float ItemInteractionDuration;
};

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInteractionInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ACAADV4_API IInteractionInterface
{
	GENERATED_BODY()

public:

	/** Template Functions without implementations */
	virtual void BeginFocus();
	virtual void EndFocus();
	virtual void BeginInteract();
	virtual void EndInteract();
	virtual void Interact(AMainCharacter* PlayerCharacter);

	FInteractableData InteractableData;
};

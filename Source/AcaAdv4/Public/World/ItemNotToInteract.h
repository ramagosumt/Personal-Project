/** The base Item Actor in the game
 *	
 */

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemNotToInteract.generated.h"

#define ECC_NonInteractable ECC_GameTraceChannel1 // User-defined collision channel in Project Setting

UCLASS()
class ACAADV4_API AItemNotToInteract : public AActor
{
	GENERATED_BODY()
	
public:

	/**
	 * FUNCTIONS
	 **/
	
	AItemNotToInteract();

protected:

	/**
	 * PROPERTIES AND VARIABLES
	 **/
	
	UPROPERTY(VisibleAnywhere, Category= "Item | Components")
	UStaticMeshComponent* MainMesh; // The main mesh for an item

};

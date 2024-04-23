// This file creates a locker that is an item to interact that also acts like a door

#pragma once

#include "CoreMinimal.h"
#include "World/ItemToInteract.h"
#include "Locker.generated.h"

class UTimelineComponent;

/**
 * 
 */
UCLASS()
class ACAADV4_API ALocker : public AItemToInteract
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* DoorMesh;

public:

	/**
	 * PROPERTIES AND VARIABLES
	 **/
	
	UPROPERTY(EditAnywhere, Category= " Timeline Actor | Curves ")
	UCurveFloat* DoorMovement;

	/**
	 * FUNCTIONS
	 **/

	ALocker();

protected:

	/**
	 * PROPERTIES AND VARIABLES
	 **/

	UPROPERTY(VisibleAnywhere)
	UTimelineComponent* OpenDoorTimeline;

	FRotator ComponentInitialRotation;
	FRotator ComponentTargetRotation;
	
	UPROPERTY(VisibleInstanceOnly)
	bool bIsOpeningDoor = false;

	/**
	 * FUNCTIONS
	 **/

	virtual void BeginPlay() override;
	
	virtual void Interact(AMainCharacter* PlayerCharacter) override;
	virtual void BeginFocus() override;
	virtual void EndFocus() override;

	// Calculate OpenDoor timeline each frame
	UFUNCTION()
	void OpenDoorStart(float Value);

	// Ends OpenDoor timeline
	UFUNCTION()
	void OpenDoorEnd();

	// Outlines door when opening the locker, otherwise doesn't outline it
	void ChangeDoorCollision();
	
};

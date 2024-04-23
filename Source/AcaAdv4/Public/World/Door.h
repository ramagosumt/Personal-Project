// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "World/ItemToInteract.h"
#include "Door.generated.h"

class UWidgetComponent;
class AMainCharacter;

/**
 * 
 */
UCLASS()
class ACAADV4_API ADoor : public AItemToInteract
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* LockMesh;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* LockClamp;
	
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* KeyOneMesh;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* KeyTwoMesh;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* KeyThreeMesh;

public:

	ADoor();

protected:
	
	bool IsDialogueEnd = false;
	bool IsPuzzleCompleted = false;

	// Called when the main character interact with this actor
	virtual void Interact(AMainCharacter* MainCharacter) override;
	
	void EndDialogue();

	UFUNCTION()
	void RemoveCombinationLock();

	void DestroyLock();
	
	void UpdateDialogue();
	
};

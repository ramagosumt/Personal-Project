// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "World/ItemToInteract.h"
#include "BookWithJigsawPuzzle.generated.h"

class UMainInventoryComponent;

/**
 * 
 */
UCLASS()
class ACAADV4_API ABookWithJigsawPuzzle : public AItemToInteract
{
	GENERATED_BODY()

protected:

	int AmountOfPiecesLeft = 3;

	UPROPERTY(VisibleAnywhere)
	AMainCharacter* InteractingCharacter;

	UPROPERTY(VisibleAnywhere)
	UMainInventoryComponent* MainInventory;

	UPROPERTY(VisibleAnywhere)
	bool IsDialogueEnd;

	UPROPERTY(VisibleAnywhere)
	bool IsPuzzleCompleted;

	int8 MissingJigsawPieceAmount = 3;

	virtual void BeginPlay() override;

	// Called when the main character focus on this actor
	virtual void BeginFocus() override;
	
	// Called when the main character interact with this actor
	virtual void Interact(AMainCharacter* MainCharacter) override;

	void OpenPuzzle();
	void LockPuzzle();
};

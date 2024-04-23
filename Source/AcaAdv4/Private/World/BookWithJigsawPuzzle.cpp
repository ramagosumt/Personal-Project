// Fill out your copyright notice in the Description page of Project Settings.


#include "World/BookWithJigsawPuzzle.h"
#include "Components/MainInventoryComponent.h"
#include "Data/DialogueDataStructs.h"
#include "Items/ItemBase.h"
#include "Player/MainCharacter.h"
#include "UserInterfaces/MainHUD.h"
#include "UserInterfaces/Interaction/DialogueWidget.h"
#include "UserInterfaces/Jigsaw/JigsawPuzzleWidget.h"

void ABookWithJigsawPuzzle::BeginPlay()
{
	Super::BeginPlay();
	
	if (DialogueData)
	{
		DialogueData->DialogueMessages.Messages[DialogueData->DialogueMessages.Messages.Num()-1] = FText::Format(FText::FromString("Seems like there are {0} missing pieces left."), AmountOfPiecesLeft);
	}
}

void ABookWithJigsawPuzzle::BeginFocus()
{
	if (!IsPuzzleCompleted)
	{
		Super::BeginFocus();
	}
}

void ABookWithJigsawPuzzle::Interact(AMainCharacter* MainCharacter)
{
	if (!IsPuzzleCompleted)
	{
		Super::Interact(MainCharacter);
	
		if (MainCharacter)
		{
			InteractingCharacter = MainCharacter;
			MainInventory = MainCharacter->GetInventory();
			
			MainCharacter->GetHUD()->GetDialogueWidget()->OnDialogueEnd.AddUObject(this, &ABookWithJigsawPuzzle::OpenPuzzle);
			
			if (AmountOfPiecesLeft == 0 && IsDialogueEnd && MainCharacter->InteractionData.CurrentInteractable == this)
			{
				MainCharacter->GetHUD()->ShowJigsawPuzzle();
				MainCharacter->GetHUD()->GetJigsawPuzzleWidget()->OnPuzzleCompleted.AddUObject(this, &ABookWithJigsawPuzzle::LockPuzzle);
			}
			else if (MainInventory && MainInventory->GetInventory().Num() > 0)
			{
				UItemBase* WieldingItem = MainInventory->GetInventory()[MainInventory->GetInventoryIndex()];
				if (WieldingItem->ItemType == EItemType::JigsawPuzzlePiece && IsDialogueEnd && MainCharacter->InteractionData.CurrentInteractable == this)
				{
					MainCharacter->WieldingItemComponent->SetStaticMesh(nullptr);
					MainInventory->RemoveItem(WieldingItem);

					AmountOfPiecesLeft--;

					if (AmountOfPiecesLeft == 0)
					{
						DialogueData->DialogueMessages.Messages.RemoveAt(DialogueData->DialogueMessages.Messages.Num()-1);
					}
					else
					{
						DialogueData->DialogueMessages.Messages[DialogueData->DialogueMessages.Messages.Num()-1] = FText::Format(FText::FromString("Seems like there are {0} missing pieces left."), AmountOfPiecesLeft);
					}
				}
			}

			IsDialogueEnd = false;
		}
	}
}

void ABookWithJigsawPuzzle::OpenPuzzle()
{
	if (InteractingCharacter)
	{
		if (this == InteractingCharacter->InteractionData.CurrentInteractable)
		{
			IsDialogueEnd = true;
		}
		else
		{
			InteractingCharacter = nullptr;
		}
	}
 }

void ABookWithJigsawPuzzle::LockPuzzle()
{
	IsPuzzleCompleted = true;
	InteractingCharacter->bIsJigsawPuzzleCompleted = IsPuzzleCompleted;
	
	EndFocus();
}

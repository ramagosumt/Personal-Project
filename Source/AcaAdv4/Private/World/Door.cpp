#include "World/Door.h"

#include "Components/WidgetComponent.h"
#include "Data/DialogueDataStructs.h"
#include "Player/MainCharacter.h"
#include "UserInterfaces/MainHUD.h"
#include "UserInterfaces/Gameplay/CombinationLockWidget.h"
#include "UserInterfaces/Interaction/DialogueWidget.h"

ADoor::ADoor()
{
	LockMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LockMesh"));
	LockMesh->SetupAttachment(MainMesh);
	
	LockClamp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LockClamp"));
	LockClamp->SetupAttachment(LockMesh);
	
	KeyOneMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("KeyOneMesh"));
	KeyOneMesh->SetupAttachment(LockMesh);
	
	KeyTwoMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("KeyTwoMesh"));
	KeyTwoMesh->SetupAttachment(LockMesh);
	
	KeyThreeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("KeyThreeMesh"));
	KeyThreeMesh->SetupAttachment(LockMesh);
	
}

void ADoor::Interact(AMainCharacter* MainCharacter)
{
	if (!IsPuzzleCompleted)
	{
		Super::Interact(MainCharacter);
        
        if (MainCharacter)
        {
        	MainCharacter->GetHUD()->GetDialogueWidget()->OnDialogueEnd.AddUObject(this, &ADoor::EndDialogue);
        	MainCharacter->GetHUD()->GetCombinationLockWidget()->OnCombinationLockPuzzleCompleted.AddUniqueDynamic(this, &ADoor::RemoveCombinationLock);
        	
        	if (IsDialogueEnd)
        	{
        		MainCharacter->GetHUD()->ShowCombinationLock();
        		MainCharacter->CharacterPuzzleMode = ECharacterPuzzleMode::EGM_DoorGameMode;
        	}
        }
    
        IsDialogueEnd = false;
	}
	else
	{
		Super::Interact(MainCharacter);

		if (IsDialogueEnd)
		{
			MainCharacter->GetHUD()->ShowEnding();
		}
	}
}

void ADoor::EndDialogue()
{
	IsDialogueEnd = true;
}

void ADoor::RemoveCombinationLock()
{
	IsPuzzleCompleted = true;
	
	DestroyLock();
	UpdateDialogue();
}

void ADoor::DestroyLock()
{
	LockMesh->DestroyComponent();
	LockClamp->DestroyComponent();
	KeyOneMesh->DestroyComponent();
	KeyTwoMesh->DestroyComponent();
	KeyThreeMesh->DestroyComponent();
}

void ADoor::UpdateDialogue()
{
	if (DialogueData->DialogueMessages.Messages.Num() > 0)
	{
		DialogueData->DialogueMessages.Messages[1] = FText::FromString("It is not locked anymore.");
		DialogueData->DialogueMessages.Messages.RemoveAt(DialogueData->DialogueMessages.Messages.Num()-1);
	}
}

#include "UserInterfaces/MainHUD.h"
#include "UserInterfaces/Menu/MainMenuWidget.h"
#include "UserInterfaces/Crosshair/CrosshairWidget.h"
#include "UserInterfaces/Interaction/InteractionWidget.h"
#include "UserInterfaces/Inventory/InventoryWidget.h"
#include "UserInterfaces/Interaction/DialogueWidget.h"
#include "UserInterfaces/Jigsaw/JigsawPuzzleWidget.h"
#include "UserInterfaces/Gameplay/CombinationLockWidget.h"

#include "Player/MainCharacter.h"

#include "Engine/DataTable.h"

#include "Data/InventoryDataStructs.h"
#include "UserInterfaces/Gameplay/EndingWidget.h"

AMainHUD::AMainHUD()
{
	bIsDialogueVisible = false;
}

void AMainHUD::BeginPlay()
{
	Super::BeginPlay();

	/** Setup the connection with the main character and controller */
	PlayerCharacter = Cast<AMainCharacter>(GetOwningPawn());
	if (PlayerCharacter)
	{
		PlayerController = Cast<APlayerController>(PlayerCharacter->GetController());
	}

	/** Main Menu */
	if (DesiredMainMenu)
	{
		MainMenu = CreateWidget<UMainMenuWidget>(GetWorld(), DesiredMainMenu);

		const FInputModeUIOnly InputMode;
		PlayerController->SetInputMode(InputMode);
		PlayerController->SetShowMouseCursor(true);
		
		MainMenu->AddToViewport(6);
		MainMenu->SetVisibility(ESlateVisibility::Visible);

		MainMenu->OnGameStart.AddUniqueDynamic(this, &AMainHUD::ShowIntroDialogue);
	}

	/** Cross-hair */
	if (DesiredCrosshair)
	{
		CrosshairWidget = CreateWidget<UCrosshairWidget>(GetWorld(), DesiredCrosshair);
		CrosshairWidget->AddToViewport();
		CrosshairWidget->SetVisibility(ESlateVisibility::Visible);
	}

	/** Interaction Widget */
	if (DesiredInteractionWidget)
	{
		InteractionWidget = CreateWidget<UInteractionWidget>(GetWorld(), DesiredInteractionWidget);
		InteractionWidget->AddToViewport(-1);
		InteractionWidget->SetVisibility(ESlateVisibility::Collapsed);
	}

	/** Inventory Widget */
	if (DesiredInventoryWidget)
	{
		InventoryWidget = CreateWidget<UInventoryWidget>(GetWorld(), DesiredInventoryWidget);
		InventoryWidget->AddToViewport();
		InventoryWidget->SetVisibility(ESlateVisibility::Visible);
	}

	/** Dialogue Widget */
	if (DesiredDialogueWidget)
	{
		DialogueWidget = CreateWidget<UDialogueWidget>(GetWorld(), DesiredDialogueWidget);
		DialogueWidget->AddToViewport(-1);
		DialogueWidget->SetVisibility(ESlateVisibility::Collapsed);

		DialogueWidget->OnDialogueEnd.AddUObject(this, &AMainHUD::ToggleDialogue);
	}

	/** Jigsaw Puzzle Widget */
	if (DesiredJigsawPuzzleWidget)
	{
		JigsawPuzzleWidget = CreateWidget<UJigsawPuzzleWidget>(GetWorld(), DesiredJigsawPuzzleWidget);
		JigsawPuzzleWidget->AddToViewport();
		JigsawPuzzleWidget->SetVisibility(ESlateVisibility::Collapsed);
	}

	/** Combination Lock Widget */
	if (DesiredCombinationLockWidget)
	{
		CombinationLockWidget = CreateWidget<UCombinationLockWidget>(GetWorld(), DesiredCombinationLockWidget);
		CombinationLockWidget->AddToViewport();
		CombinationLockWidget->SetVisibility(ESlateVisibility::Collapsed);
	}

	/** Ending Game Widget */
	if (DesiredEndingGameWidget)
	{
		EndingWidget = CreateWidget<UEndingWidget>(GetWorld(), DesiredEndingGameWidget);
		EndingWidget->AddToViewport();
		EndingWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void AMainHUD::ShowCrosshairWidget() const
{
	if (CrosshairWidget)
	{
		CrosshairWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

void AMainHUD::HideCrosshairWidget() const
{
	if (CrosshairWidget)
	{
		CrosshairWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void AMainHUD::ShowInteractionWidget() const
{
	if (InteractionWidget)
	{
		InteractionWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

void AMainHUD::HideInteractionWidget() const
{
	if (InteractionWidget)
	{
		InteractionWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void AMainHUD::UpdateInteractionWidget(const FInteractableData* InteractableData) const
{
	if (InteractionWidget)
	{
		if (InteractionWidget->GetVisibility() == ESlateVisibility::Collapsed)
		{
			InteractionWidget->SetVisibility(ESlateVisibility::Visible);
		}

		InteractionWidget->UpdateWidget(InteractableData);
	}
}

void AMainHUD::ShowIntroDialogue()
{
	if (IntroDialogue && !DesiredDialogueID.IsNone())
	{
		DialogueData = IntroDialogue->FindRow<FInventoryData>(DesiredDialogueID, DesiredDialogueID.ToString());
		
		UpdateDialogueWidget(DialogueData->TextData.DialogueMessages);
	}
}

void AMainHUD::ShowDialogue() const
{
	DialogueWidget->SetVisibility(ESlateVisibility::Visible);
	
	if (PlayerController)
	{
		PlayerController->SetCinematicMode(true, true, true);
	}
}

void AMainHUD::HideDialogue() const
{
	DialogueWidget->SetVisibility(ESlateVisibility::Collapsed);

	if (PlayerCharacter)
	{
		OnDialogueEndOneParam.Broadcast(PlayerCharacter);
		PlayerController->SetCinematicMode(false, true, true);
	}
}

void AMainHUD::ToggleDialogue()
{
	if (bIsDialogueVisible)
	{
		HideDialogue();
	}
	else
	{
		ShowDialogue();
	}

	bIsDialogueVisible = !bIsDialogueVisible;
}

void AMainHUD::UpdateDialogueWidget(const FInteractableData* InteractableData)
{
	if (DialogueWidget)
	{
		if (!bIsDialogueVisible)
		{
			ToggleDialogue();
		}
 		
		DialogueWidget->UpdateWidget(InteractableData);
	}
}

void AMainHUD::UpdateDialogueWidget(const TArray<FText> Messages)
{
	if (DialogueWidget)
	{
		if (!bIsDialogueVisible)
		{
			ToggleDialogue();
		}
 		
		DialogueWidget->UpdateWidget(Messages);
	}
}

void AMainHUD::UpdateDialogueWidget(const FDialogueData* DesiredDialogueData)
{
	if (DialogueWidget)
	{
		if (!bIsDialogueVisible)
		{
			ToggleDialogue();
		}

		DialogueWidget->UpdateWidget(DesiredDialogueData);
	}
}

void AMainHUD::ShowJigsawPuzzle()
{
	if (JigsawPuzzleWidget)
	{
		bIsJigsawPuzzleVisible = true;
		JigsawPuzzleWidget->OnPuzzleCompleted.AddUObject(this, &AMainHUD::HideJigsawPuzzle);
		
		JigsawPuzzleWidget->SetVisibility(ESlateVisibility::Visible);

		const FInputModeGameAndUI InputMode;
		GetOwningPlayerController()->SetInputMode(InputMode);
		GetOwningPlayerController()->SetShowMouseCursor(true);

		if (PlayerController)
		{
			PlayerController->SetCinematicMode(true, true, true);
		}
	}
}

void AMainHUD::HideJigsawPuzzle()
{
	if (JigsawPuzzleWidget)
	{
		bIsJigsawPuzzleVisible = false;
		
		JigsawPuzzleWidget->SetVisibility(ESlateVisibility::Collapsed);

		const FInputModeGameOnly InputMode;
		GetOwningPlayerController()->SetInputMode(InputMode);
		GetOwningPlayerController()->SetShowMouseCursor(false);

		if (PlayerController)
		{
			PlayerController->SetCinematicMode(false, true, true);
		}
	}
}

void AMainHUD::ShowCombinationLock()
{
	if (CombinationLockWidget)
	{
		CombinationLockWidget->OnCombinationLockPuzzleCompleted.AddUniqueDynamic(this, &AMainHUD::HideCombinationLock);
		
		CombinationLockWidget->SetVisibility(ESlateVisibility::Visible);
		HideCrosshairWidget();

		const FInputModeGameAndUI InputMode;
		GetOwningPlayerController()->SetInputMode(InputMode);
		GetOwningPlayerController()->SetShowMouseCursor(true);

		if (PlayerController)
		{
			PlayerController->SetCinematicMode(true, true, true);
		}
	}
}

void AMainHUD::HideCombinationLock()
{
	if (CombinationLockWidget)
	{
		CombinationLockWidget->SetVisibility(ESlateVisibility::Collapsed);
		ShowCrosshairWidget();

		const FInputModeGameOnly InputMode;
		GetOwningPlayerController()->SetInputMode(InputMode);
		GetOwningPlayerController()->SetShowMouseCursor(false);

		if (PlayerController)
		{
			PlayerController->SetCinematicMode(false, true, true);
		}
	}
}

void AMainHUD::ShowEnding()
{
	if (EndingWidget)
	{
		EndingWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

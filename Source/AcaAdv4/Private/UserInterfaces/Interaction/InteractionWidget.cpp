#include "UserInterfaces/Interaction/InteractionWidget.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "Interfaces/InteractionInterface.h"

void UInteractionWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	// Bind the percent of the progress bar with UpdateInteractionProgress
	InteractionProgressBar->PercentDelegate.BindUFunction(this, "UpdateInteractionProgress");
}

void UInteractionWidget::NativeConstruct()
{
	Super::NativeConstruct();

	KeyPressText->SetText(FText::FromString("Press"));
	CurrentInteractionDuration = 0.f;
}

void UInteractionWidget::UpdateWidget(const FInteractableData* InteractableData) const
{
	switch (InteractableData->ItemInteractionMode)
	{
	case (EItemInteractionMode::ObtainableItem):
		KeyPressText->SetText(FText::FromString("Press"));
		InteractionProgressBar->SetVisibility(ESlateVisibility::Collapsed);

		if (InteractableData->Quantity < 2)
		{
			QuantityText->SetVisibility(ESlateVisibility::Collapsed);
		}
		else
		{
			QuantityText->SetText(FText::Format(FText::FromString("x{0}"), InteractableData->Quantity));	
			QuantityText->SetVisibility(ESlateVisibility::Visible);
		}
		
		break;
		
	case (EItemInteractionMode::NPC):
		break;
	case (EItemInteractionMode::Device):
		break;
	case (EItemInteractionMode::Toggle):
		break;
	case (EItemInteractionMode::Container):
		break;
	default:
		;
	}

	ActionText->SetText(InteractableData->Action);
	NameText->SetText(InteractableData->Name);
}

float UInteractionWidget::UpdateInteractionProgress()
{
	return 0.f;
}

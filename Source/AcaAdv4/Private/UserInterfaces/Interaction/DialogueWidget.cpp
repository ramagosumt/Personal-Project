#include "UserInterfaces/Interaction/DialogueWidget.h"
#include "Components/TextBlock.h"
#include "Interfaces/InteractionInterface.h"
#include "Data/DialogueDataStructs.h"

void UDialogueWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	DialogueAnimatingState = EDialogueAnimatingState::NoDialogue;
	DelayTimeBetweenAnimatingLetters = 0.035f;
}

void UDialogueWidget::AnimatingDialogueMessageSingleCharacter()	
{
	// Clears the timer from the last character animating
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);

	// Adds the next character to display
	OutputDialogueMessage.AppendChar(InitialDialogueMessage[SingleDialogueMessageCharacter]);

	// Displays the new set of characters
	DialogueMessage->SetText(FText::FromString(OutputDialogueMessage));

	// If there are more characters in the full dialogue message that haven't been displayed yet
	if (SingleDialogueMessageCharacter + 1 < InitialDialogueMessage.Len())
	{
		// Take the next character
		SingleDialogueMessageCharacter = SingleDialogueMessageCharacter + 1;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UDialogueWidget::AnimatingDialogueMessageSingleCharacter, DelayTimeBetweenAnimatingLetters, false);
	}
	else // If there are no more character, complete this dialogue message
	{
		DialogueAnimatingState = EDialogueAnimatingState::FinishAnimatingDialogue;
	}
}

void UDialogueWidget::AnimateDialogueMessage(const FString& Text)
{
	// Current state: Animating
	DialogueAnimatingState = EDialogueAnimatingState::AnimatingDialogue;

	// The full version of a dialogue message that needs to be display
	InitialDialogueMessage = Text;

	// The actual dialogue message that will be used to display
	OutputDialogueMessage = "";

	// At the start of the animating phase, i = 0
	SingleDialogueMessageCharacter = 0;

	// No character at first
	DialogueMessage->SetText(FText::FromString(""));

	// Sets timer to display each character of a dialogue message
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UDialogueWidget::AnimatingDialogueMessageSingleCharacter, DelayTimeBetweenAnimatingLetters, false);
}

void UDialogueWidget::UpdateWidget(const FInteractableData* InteractableData)
{
	// If this is the first dialogue message
	if (DialogueAnimatingState == EDialogueAnimatingState::NoDialogue)
	{
		AnimateDialogueMessage(InteractableData->DialogueMessages[DialogueMessageIndex].ToString());
	}
	// If the player interact when a dialogue message is being animated, skip animating that dialogue message
	else if (DialogueAnimatingState == EDialogueAnimatingState::AnimatingDialogue) 
	{
		// Clears the timer from the last character animating
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle);

		// Skips the dialogue message
		DialogueMessage->SetText(FText::FromString(InitialDialogueMessage));

		// Dialogue message completed
		DialogueAnimatingState = EDialogueAnimatingState::FinishAnimatingDialogue;
	}
	else if (DialogueAnimatingState == EDialogueAnimatingState::FinishAnimatingDialogue) // If the dialogue is being completed
	{
		
		if ((DialogueMessageIndex + 1) < InteractableData->DialogueMessages.Num())
		{
			// Gets the next dialogue message
			DialogueMessageIndex += 1;

			// Starts animating the next dialogue message
			AnimateDialogueMessage(InteractableData->DialogueMessages[DialogueMessageIndex].ToString());
		}
		else // If current dialogue message is the last one
		{
			DialogueMessageIndex = 0;
			DialogueMessage->SetText(FText::FromString(""));
			DialogueAnimatingState = EDialogueAnimatingState::NoDialogue;
			
			OnDialogueEnd.Broadcast();
		}
	}
}

void UDialogueWidget::UpdateWidget(const TArray<FText> Messages)
{
	// If this is the first dialogue message
	if (DialogueAnimatingState == EDialogueAnimatingState::NoDialogue)
	{
		AnimateDialogueMessage(Messages[DialogueMessageIndex].ToString());
	}
	// If the player interact when a dialogue message is being animated, skip animating that dialogue message
	else if (DialogueAnimatingState == EDialogueAnimatingState::AnimatingDialogue) 
	{
		// Clears the timer from the last character animating
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle);

		// Skips the dialogue message
		DialogueMessage->SetText(FText::FromString(InitialDialogueMessage));

		// Dialogue message completed
		DialogueAnimatingState = EDialogueAnimatingState::FinishAnimatingDialogue;
	}
	else if (DialogueAnimatingState == EDialogueAnimatingState::FinishAnimatingDialogue) // If the dialogue is being completed
	{
		if ((DialogueMessageIndex + 1) < Messages.Num())
		{
			// Gets the next dialogue message
			DialogueMessageIndex += 1;

			// Starts animating the next dialogue message
			AnimateDialogueMessage(Messages[DialogueMessageIndex].ToString());
		}
		else // If current dialogue message is the last one
		{
			DialogueMessageIndex = 0;
			DialogueMessage->SetText(FText::FromString(""));
			DialogueAnimatingState = EDialogueAnimatingState::NoDialogue;
			
			OnDialogueEnd.Broadcast();
		}
	}
}

void UDialogueWidget::UpdateWidget(const FDialogueData* DialogueData)
{
	// If this is the first dialogue message
	if (DialogueAnimatingState == EDialogueAnimatingState::NoDialogue)
	{
		AnimateDialogueMessage(DialogueData->DialogueMessages.Messages[DialogueMessageIndex].ToString());
	}
	// If the player interact when a dialogue message is being animated, skip animating that dialogue message
	else if (DialogueAnimatingState == EDialogueAnimatingState::AnimatingDialogue) 
	{
		// Clears the timer from the last character animating
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle);

		// Skips the dialogue message
		DialogueMessage->SetText(FText::FromString(InitialDialogueMessage));

		// Dialogue message completed
		DialogueAnimatingState = EDialogueAnimatingState::FinishAnimatingDialogue;
	}
	else if (DialogueAnimatingState == EDialogueAnimatingState::FinishAnimatingDialogue) // If the dialogue is being completed
	{
		if ((DialogueMessageIndex + 1) < DialogueData->DialogueMessages.Messages.Num())
		{
			// Gets the next dialogue message
			DialogueMessageIndex += 1;

			// Starts animating the next dialogue message
			AnimateDialogueMessage(DialogueData->DialogueMessages.Messages[DialogueMessageIndex].ToString());
		}
		else // If current dialogue message is the last one
		{
			DialogueMessageIndex = 0;
			DialogueMessage->SetText(FText::FromString(""));
			DialogueAnimatingState = EDialogueAnimatingState::NoDialogue;
			
			OnDialogueEnd.Broadcast();
		}
	}
}

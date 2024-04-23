// This file creates the UI for Dialogue

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DialogueWidget.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnDialogueEnd)

// This enum resembles the state of dialogue animating
UENUM()
enum class EDialogueAnimatingState : uint8
{
	NoDialogue UMETA(DisplayName = "NoDialogue"),
	AnimatingDialogue UMETA(DisplayName = "AnimatingDialogue"),
	FinishAnimatingDialogue UMETA(DisplayName = "FinishAnimatingDialogue")
};

class UTextBlock;
class AMainCharacter;

struct FInteractableData;
struct FDialogueData;

/**
 * 
 */
UCLASS()
class ACAADV4_API UDialogueWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	// A simple multicast delegate to end Dialogues
	FOnDialogueEnd OnDialogueEnd;

	// A reference to the text block that would display the Dialogue messages
	UPROPERTY(meta=(BindWidget))
	UTextBlock* DialogueMessage;

	// A reference to the state of Dialogue animating
	UPROPERTY(VisibleAnywhere)
	EDialogueAnimatingState DialogueAnimatingState;

	// Updates itself
	void UpdateWidget(const FInteractableData* MessageData);
	void UpdateWidget(const TArray<FText> Messages);
	void UpdateWidget(const FDialogueData* DialogueData);

	// Animate the Dialogue
	void AnimateDialogueMessage(const FString& Text);

protected:

	FTimerHandle TimerHandle;
	
	UPROPERTY(EditAnywhere, Category= "Setup")
	float DelayTimeBetweenAnimatingLetters;

	FString InitialDialogueMessage;
	FString OutputDialogueMessage;
	
	int32 DialogueMessageIndex;
	int32 SingleDialogueMessageCharacter;

	UFUNCTION()
	void AnimatingDialogueMessageSingleCharacter();

	virtual void NativeOnInitialized() override;
};

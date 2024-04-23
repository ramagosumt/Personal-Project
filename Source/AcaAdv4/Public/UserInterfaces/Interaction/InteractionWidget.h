/** Creates an interaction widget that appears on the main character's screen
 * Can update itself
 * Can update the progress bar residing in it
 */

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InteractionWidget.generated.h"

class UProgressBar;
class UTextBlock;
class AMainCharacter;
struct FInteractableData;

/**
 * 
 */
UCLASS()
class ACAADV4_API UInteractionWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	// A reference to the main character 
	UPROPERTY(VisibleAnywhere, Category= "Interaction Widget | PLayer Reference")
	AMainCharacter* PlayerCharacter;

	// Updates itself
	void UpdateWidget(const FInteractableData* InteractableData) const;

protected:

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category= "Interaction Widget | Interactable Data")
	UTextBlock* NameText;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category= "Interaction Widget | Interactable Data")
	UTextBlock* ActionText;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category= "Interaction Widget | Interactable Data")
	UTextBlock* QuantityText;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category= "Interaction Widget | Interactable Data")
	UTextBlock* KeyPressText;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category= "Interaction Widget | Interactable Data")
	UProgressBar* InteractionProgressBar;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category= "Interaction Widget | Interactable Data")
	float CurrentInteractionDuration;

	UFUNCTION(Category= "Interaction Widget | Interactable Data")
	float UpdateInteractionProgress();
	
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
	
};

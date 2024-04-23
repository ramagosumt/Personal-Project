// The MainHUD to store the user-interfaces

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MainHUD.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnDialogueEndOneParam, class AMainCharacter*)

class UMainMenuWidget;
class UCrosshairWidget;
class UInteractionWidget;
class UInventoryWidget;
class UDialogueWidget;
class UJigsawPuzzleWidget;
class UDataTable;
class UCombinationLockWidget;
class UEndingWidget;

struct FInventoryData;
struct FInteractableData;
struct FDialogueData;

/**
 * 
 */
UCLASS()
class ACAADV4_API AMainHUD : public AHUD
{
	GENERATED_BODY()

public:
	
	/**
	 * PROPERTIES AND VARIABLES
	 **/

	FOnDialogueEndOneParam OnDialogueEndOneParam;

	/** Main Menu */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Widgets")
	TSubclassOf<UMainMenuWidget> DesiredMainMenu; // To choose the desired Main Menu Widget Blueprint in the UE4 Editor
	
	/** Cross-hair */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Widgets")
	TSubclassOf<UCrosshairWidget> DesiredCrosshair; // To choose the desired Cross-hair Widget Blueprint in the UE4 Editor

	/** Interaction Widget */
	UPROPERTY(EditDefaultsOnly, Category= "Widgets")
	TSubclassOf<UInteractionWidget> DesiredInteractionWidget;

	bool bIsMenuVisible;

	/** Inventory Widget */
	UPROPERTY(EditDefaultsOnly, Category= "Widgets")
	TSubclassOf<UInventoryWidget> DesiredInventoryWidget;

	/** Dialogue Widget */
	UPROPERTY(EditDefaultsOnly, Category= "Widgets")
	TSubclassOf<UDialogueWidget> DesiredDialogueWidget;

	bool bIsDialogueVisible;
	
	// Intro Dialogue
	UPROPERTY(EditDefaultsOnly, Category= "Character | ItemInitialization")
	UDataTable* IntroDialogue;

	UPROPERTY(EditDefaultsOnly, Category= "Character | ItemInitialization")
	FName DesiredDialogueID;

	const FInventoryData* DialogueData;

	/** Jigsaw Puzzle Widget */
	UPROPERTY(EditDefaultsOnly, Category= "Widgets")
	TSubclassOf<UJigsawPuzzleWidget> DesiredJigsawPuzzleWidget;

	bool bIsJigsawPuzzleVisible;

	/** Combination Lock Widget */
	UPROPERTY(EditDefaultsOnly, Category= "Widgets")
	TSubclassOf<UCombinationLockWidget> DesiredCombinationLockWidget;

	/** Ending Game Widget */
	UPROPERTY(EditDefaultsOnly, Category= "Widgets")
	TSubclassOf<UEndingWidget> DesiredEndingGameWidget;
	
	/**
	 * FUNCTIONS
	 **/
	
	AMainHUD();

	/** Cross-hair */
	void ShowCrosshairWidget() const;
	void HideCrosshairWidget() const;

	/** Interaction Widget */
	void ShowInteractionWidget() const;
	void HideInteractionWidget() const;
	void UpdateInteractionWidget(const FInteractableData* InteractableData) const;

	/** Inventory Widget */
	FORCEINLINE UInventoryWidget* GetInventoryWidget() const { return InventoryWidget; }
	FORCEINLINE UDialogueWidget* GetDialogueWidget() const { return DialogueWidget; }
	FORCEINLINE UJigsawPuzzleWidget* GetJigsawPuzzleWidget() const { return JigsawPuzzleWidget; }
	FORCEINLINE UCombinationLockWidget* GetCombinationLockWidget() const { return CombinationLockWidget; }
	FORCEINLINE UEndingWidget* GetEndingWidget() const { return EndingWidget; }

	/** Dialogue Widget */
	void ShowDialogue() const;
	void HideDialogue() const;
	void ToggleDialogue();
	void UpdateDialogueWidget(const FInteractableData* InteractableData);
	void UpdateDialogueWidget(const TArray<FText> Messages);
	void UpdateDialogueWidget(const FDialogueData* DesiredDialogueData);

	/** Jigsaw Puzzle Widget */
	void ShowJigsawPuzzle();
	void HideJigsawPuzzle();

	/** Combination Lock Widget */
	void ShowCombinationLock();

	UFUNCTION()
	void HideCombinationLock();

	/** Ending Game Widget */
	void ShowEnding();
	
protected:
	
	/**
	 * PROPERTIES AND VARIABLES
	 **/

	// A reference to the Main Character
	UPROPERTY(VisibleAnywhere)
	AMainCharacter* PlayerCharacter;

	// A reference to the Main Controller
	UPROPERTY(VisibleAnywhere)
	APlayerController* PlayerController;

	/** Main Menu */
	UPROPERTY(VisibleAnywhere, Category= "Widgets")
	UMainMenuWidget* MainMenu; // Reference to the real Main Menu Widget Blueprint
	
	/** Cross-hair */
	UPROPERTY(VisibleAnywhere, Category= "Widgets")
	UUserWidget* CrosshairWidget; // Reference to the real Cross-hair Widget Blueprint

	/** Interaction Widget */
	UPROPERTY(VisibleAnywhere, Category= "Widgets")
	UInteractionWidget* InteractionWidget; // Reference to the real Interaction Widget Blueprint

	/** Inventory Widget */
	UPROPERTY(VisibleAnywhere, Category= "Widgets")
	UInventoryWidget* InventoryWidget; // Reference to the real Inventory Widget Blueprint

	/** Dialogue Widget */
	UPROPERTY()
	UDialogueWidget* DialogueWidget; // Reference to the real Dialogue Widget Blueprint

	/** Jigsaw Puzzle Widget */
	UPROPERTY()
	UJigsawPuzzleWidget* JigsawPuzzleWidget; // Reference to the real Jigsaw Puzzle Widget Blueprint

	/** Combination Lock Widget */
	UPROPERTY()
	UCombinationLockWidget* CombinationLockWidget; // Reference to the real Combination Lock Widget Blueprint

	/** Ending Game Widget */
	UPROPERTY()
	UEndingWidget* EndingWidget; // Reference to the real Ending Game Widget Blueprint
	
	/**
	 * FUNCTIONS
	 **/

	virtual void BeginPlay() override;

	UFUNCTION()
	void ShowIntroDialogue();
};

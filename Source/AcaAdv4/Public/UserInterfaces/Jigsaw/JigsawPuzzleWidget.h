// This file creates the whole Jigsaw Puzzle widget

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "JigsawPuzzleWidget.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnPuzzleCompleted);

class UJigsawPieceWidget;
class UJigsawSlotWidget;
class UCanvasPanel;
class UUniformGridPanel;
class UButton;

/**
 * 
 */
UCLASS()
class ACAADV4_API UJigsawPuzzleWidget : public UUserWidget
{
	GENERATED_BODY()

	/** Jigsaw Piece */
	UPROPERTY(EditDefaultsOnly, Category= "Widgets")
	TSubclassOf<UJigsawPieceWidget> DesiredJigsawPieceWidget;

	UPROPERTY()
	UJigsawPieceWidget* JigsawPieceWidget;

	/** Jigsaw Slot */
	UPROPERTY(EditDefaultsOnly, Category= "Widgets")
	TSubclassOf<UJigsawSlotWidget> DesiredJigsawSlotWidget;

	UPROPERTY()
	UJigsawSlotWidget* JigsawSlotWidget;

public:

	FOnPuzzleCompleted OnPuzzleCompleted;

protected:

	// The amount of puzzle pieces, default is 16 
	int32 AmountOfPieces = 16;
	int32 AmountOfPiecesCompleted = 0;

	// The canvas panel that would be used to store the puzzle pieces
	UPROPERTY(meta=(BindWidget))
	UCanvasPanel* PuzzlePiecesTray;

	// The slot grid that puzzle pieces should be placed on
	UPROPERTY(meta=(BindWidget))
	UUniformGridPanel* PuzzleSlotGrid;

	// The button used to reset the puzzle
	UPROPERTY(meta=(BindWidget))
	UButton* PuzzleResetButton;

	// The texture that would be used as an image for the whole puzzle
	UPROPERTY(EditDefaultsOnly, Category= "Jigsaw | Initialization")
	UTexture2D* JigsawPuzzleImage;

	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;

	// Spawn the puzzle pieces randomly
	void SpawnPieces();

	// Spawn the slot grid 
	void SpawnSlots();

	// Keep track of how many pieces have been placed
	void PlacePieces();

	// Reset the puzzle back to original form
	UFUNCTION()
	void ResetPuzzle();
};

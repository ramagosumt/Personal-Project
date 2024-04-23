// This file calculates the operation of drag and drop for the jigsaw puzzle

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "JigsawPuzzleDragDropOperation.generated.h"

class UJigsawPieceWidget;

/**
 * 
 */
UCLASS()
class ACAADV4_API UJigsawPuzzleDragDropOperation : public UDragDropOperation
{
	GENERATED_BODY()

public:

	// The coordinate to slice the default material
	UPROPERTY()
	FVector2D JigsawPieceCoordinate;

	// A reference to the piece being dragged
	UPROPERTY()
	UJigsawPieceWidget* DraggingPiece;

	// What happened when cancelling drop
	virtual void DragCancelled_Implementation(const FPointerEvent& PointerEvent) override;
};

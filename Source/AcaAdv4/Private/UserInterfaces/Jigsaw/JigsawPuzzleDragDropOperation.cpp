#include "UserInterfaces/Jigsaw/JigsawPuzzleDragDropOperation.h"
#include "UserInterfaces/Jigsaw/JigsawPieceWidget.h"

void UJigsawPuzzleDragDropOperation::DragCancelled_Implementation(const FPointerEvent& PointerEvent)
{
	Super::DragCancelled_Implementation(PointerEvent);

	DraggingPiece->SetVisibility(ESlateVisibility::Visible);
}

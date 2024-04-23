#include "UserInterfaces/Jigsaw/JigsawPieceWidget.h"
#include "UserInterfaces/Jigsaw/JigsawPieceDragVisualWidget.h"
#include "UserInterfaces/Jigsaw/JigsawPuzzleDragDropOperation.h"
#include "Components/Image.h"
#include "Kismet/KismetMaterialLibrary.h"

void UJigsawPieceWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (DesiredJigsawPuzzleMaterial)
	{
		JigsawPuzzleMaterialInstance = UKismetMaterialLibrary::CreateDynamicMaterialInstance(GetWorld(), DesiredJigsawPuzzleMaterial);
		JigsawPuzzleMaterialInstance->SetScalarParameterValue(TEXT("AmountOfPieces"), AmountOfPieces);
		JigsawPuzzleMaterialInstance->SetVectorParameterValue(TEXT("JigsawPuzzle"), FLinearColor(JigsawPieceCoordinate.X, JigsawPieceCoordinate.Y, 0.f, 0.f));
		JigsawPuzzleMaterialInstance->SetTextureParameterValue(TEXT("JigsawPuzzleImage"), JigsawPuzzleImage);

		JigsawPieceImage->SetBrushFromMaterial(JigsawPuzzleMaterialInstance);
	}
}

void UJigsawPieceWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (DesiredJigsawPuzzleMaterial)
	{
		JigsawPuzzleMaterialInstance = UKismetMaterialLibrary::CreateDynamicMaterialInstance(GetWorld(), DesiredJigsawPuzzleMaterial);
		JigsawPuzzleMaterialInstance->SetScalarParameterValue(TEXT("AmountOfPieces"), AmountOfPieces);
		JigsawPuzzleMaterialInstance->SetVectorParameterValue(TEXT("JigsawPuzzle"), FLinearColor(JigsawPieceCoordinate.X, JigsawPieceCoordinate.Y, 0.f, 0.f));
		JigsawPuzzleMaterialInstance->SetTextureParameterValue(TEXT("JigsawPuzzleImage"), JigsawPuzzleImage);

		JigsawPieceImage->SetBrushFromMaterial(JigsawPuzzleMaterialInstance);
	}
}

FReply UJigsawPieceWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply Reply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
	
	if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
	{
		return Reply.Handled().DetectDrag(TakeWidget(), EKeys::LeftMouseButton);
	}

	return Reply.Unhandled();
}

void UJigsawPieceWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);
	
	if (DesiredJigsawPieceDragVisualWidget)
	{
		// Create a drag visual widget
		UJigsawPieceDragVisualWidget* JigsawPieceDragVisual = CreateWidget<UJigsawPieceDragVisualWidget>(this, DesiredJigsawPieceDragVisualWidget);

		JigsawPieceDragVisual->SetAmountOfPieces(AmountOfPieces);
		JigsawPieceDragVisual->SetCoordinate(JigsawPieceCoordinate);
		JigsawPieceDragVisual->SetImage(JigsawPuzzleImage);

		// Create a drag drop operation
		UJigsawPuzzleDragDropOperation* DragJigsawPieceOperation = NewObject<UJigsawPuzzleDragDropOperation>();
		DragJigsawPieceOperation->JigsawPieceCoordinate = JigsawPieceCoordinate;
		DragJigsawPieceOperation->DraggingPiece = this;
		DragJigsawPieceOperation->DefaultDragVisual = Cast<UWidget>(JigsawPieceDragVisual);
		DragJigsawPieceOperation->Pivot = EDragPivot::CenterCenter;

		// Hide the puzzle piece when dragging
		this->SetVisibility(ESlateVisibility::Hidden);
		
		OutOperation = DragJigsawPieceOperation;
	}
}

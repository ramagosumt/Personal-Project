#include "UserInterfaces/Jigsaw/JigsawSlotWidget.h"
#include "UserInterfaces/Jigsaw/JigsawPieceWidget.h"
#include "UserInterfaces/Jigsaw/JigsawPuzzleDragDropOperation.h"
#include "Components/Image.h"
#include "Components/SizeBoxSlot.h"
#include "Kismet/KismetMaterialLibrary.h"

bool UJigsawSlotWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	const UJigsawPuzzleDragDropOperation* JigsawPuzzleDragDropOperation = Cast<UJigsawPuzzleDragDropOperation>(InOperation);
	
	if (JigsawPuzzleDragDropOperation->JigsawPieceCoordinate == JigsawSlotCoordinate)
	{
		UE_LOG(LogTemp, Warning, TEXT("Duh."))
		if (DesiredJigsawPuzzleMaterial)
		{
			JigsawPuzzleMaterialInstance = UKismetMaterialLibrary::CreateDynamicMaterialInstance(GetWorld(), DesiredJigsawPuzzleMaterial);
			JigsawPuzzleMaterialInstance->SetScalarParameterValue(TEXT("AmountOfPieces"), AmountOfSlots);
			JigsawPuzzleMaterialInstance->SetVectorParameterValue(TEXT("JigsawPuzzle"), FLinearColor(JigsawSlotCoordinate.X, JigsawSlotCoordinate.Y, 0.f, 0.f));
			JigsawPuzzleMaterialInstance->SetTextureParameterValue(TEXT("JigsawPuzzleImage"), JigsawPuzzleImage);

			JigsawSlotImage->SetBrushFromMaterial(JigsawPuzzleMaterialInstance);
			
			USizeBoxSlot* SizeBoxSlot = Cast<USizeBoxSlot>(JigsawSlotImage->Slot);
			SizeBoxSlot->SetPadding(0.f);

			JigsawSlotImage->SetColorAndOpacity(FLinearColor::White);

			JigsawPuzzleDragDropOperation->DraggingPiece->RemoveFromParent();

			OnJigsawPieceCorrectlyPlaced.Broadcast();
		}
	}
	
	return Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
}

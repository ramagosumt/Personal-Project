#include "UserInterfaces/Jigsaw/JigsawPieceDragVisualWidget.h"
#include "Kismet/KismetMaterialLibrary.h"
#include "Components/Image.h"

void UJigsawPieceDragVisualWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (DesiredJigsawPuzzleMaterial)
	{
		JigsawPuzzleMaterialInstance = UKismetMaterialLibrary::CreateDynamicMaterialInstance(GetWorld(), DesiredJigsawPuzzleMaterial);
		JigsawPuzzleMaterialInstance->SetScalarParameterValue(TEXT("AmountOfPieces"), AmountOfPieces);
		JigsawPuzzleMaterialInstance->SetVectorParameterValue(TEXT("JigsawPuzzle"), FLinearColor(JigsawPieceCoordinate.X, JigsawPieceCoordinate.Y, 0.f, 0.f));
		JigsawPuzzleMaterialInstance->SetTextureParameterValue(TEXT("JigsawPuzzleImage"), JigsawPuzzleImage);

		JigsawPieceDragImage->SetBrushFromMaterial(JigsawPuzzleMaterialInstance);
	}
}

// This file creates a jigsaw puzzle slot widget to store the jigsaw puzzle piece widget.
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "JigsawSlotWidget.generated.h"

class UImage;

DECLARE_MULTICAST_DELEGATE(FOnJigsawPieceCorrectlyPlaced)

/**
 * 
 */
UCLASS()
class ACAADV4_API UJigsawSlotWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	FOnJigsawPieceCorrectlyPlaced OnJigsawPieceCorrectlyPlaced;
	
	void SetAmountOfPieces(const int32 Amount) { AmountOfSlots = Amount; }
	void SetCoordinate(const FVector2D Coordinate) { JigsawSlotCoordinate = Coordinate; }
	void SetImage(UTexture2D* Image) { JigsawPuzzleImage = Image; }

protected:

	// The amount of puzzle pieces, default is 16 
	int32 AmountOfSlots = 16;

	// The actual slot image, would later be replaced by the piece image
	UPROPERTY(meta=(BindWidget))
	UImage* JigsawSlotImage;

	// The material used to create this widget
	UPROPERTY(EditDefaultsOnly, Category= "Jigsaw | MaterialInstance")
	UMaterialInstance* DesiredJigsawPuzzleMaterial;

	// The instance of the material used to create this widget
	UPROPERTY(VisibleDefaultsOnly, Category= "Jigsaw | MaterialInstance")
	UMaterialInstanceDynamic* JigsawPuzzleMaterialInstance;

	// The coordinate to copy from the sliced default material
	UPROPERTY(VisibleDefaultsOnly, Category= "Jigsaw | Initialization")
	FVector2D JigsawSlotCoordinate;

	// The texture that would be used as an image for the whole puzzle
	UPROPERTY(VisibleDefaultsOnly, Category= "Jigsaw | Initialization")
	UTexture2D* JigsawPuzzleImage;

	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
};

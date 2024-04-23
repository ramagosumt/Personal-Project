// This files resembles a visual reference for a dragging jigsaw piece

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "JigsawPieceDragVisualWidget.generated.h"

class UImage;

/**
 * 
 */
UCLASS()
class ACAADV4_API UJigsawPieceDragVisualWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	void SetAmountOfPieces(const int32 Amount) { AmountOfPieces = Amount; }
	void SetCoordinate(const FVector2D Coordinate) { JigsawPieceCoordinate = Coordinate; }
	void SetImage(UTexture2D* Image) { JigsawPuzzleImage = Image; }

protected:

	/**
	 * PROPERTIES AND VARIABLES
	 **/

	// The amount of puzzle pieces, default is 16 
	int32 AmountOfPieces = 16;

	// A reference to the drag image UI
	UPROPERTY(meta=(BindWidget))
	UImage* JigsawPieceDragImage;

	// The material used to create this widget
	UPROPERTY(EditDefaultsOnly, Category= "Jigsaw | MaterialInstance")
	UMaterialInstance* DesiredJigsawPuzzleMaterial;

	// The instance of the material used to create this widget
	UPROPERTY(VisibleDefaultsOnly, Category= "Jigsaw | MaterialInstance")
	UMaterialInstanceDynamic* JigsawPuzzleMaterialInstance;

	// The coordinate to slice the default material
	UPROPERTY(VisibleDefaultsOnly, Category= "Jigsaw | Initialization")
	FVector2D JigsawPieceCoordinate;

	// The sliced texture that would later be use for the image
	UPROPERTY(EditDefaultsOnly, Category= "Jigsaw | Initialization")
	UTexture2D* JigsawPuzzleImage;

	/**
	 * FUNCTIONS
	 **/
	
	virtual void NativeConstruct() override;
};

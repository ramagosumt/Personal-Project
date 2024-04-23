// This file creates a jigsaw puzzle piece widget from an user-defined material.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "JigsawPieceWidget.generated.h"

class UImage;
class UJigsawPieceDragVisualWidget;

/**
 * 
 */
UCLASS()
class ACAADV4_API UJigsawPieceWidget : public UUserWidget
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

	// The actual image that would later be shown on screen 
	UPROPERTY(meta=(BindWidget))
	UImage* JigsawPieceImage;

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

	// 
	UPROPERTY(EditDefaultsOnly, Category= "Jigsaw | Initialization")
	TSubclassOf<UJigsawPieceDragVisualWidget> DesiredJigsawPieceDragVisualWidget;

	/**
	 * FUNCTIONS
	 **/
	
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
	
};

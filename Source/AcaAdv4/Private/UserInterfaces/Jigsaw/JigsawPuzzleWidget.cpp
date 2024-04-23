// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterfaces/Jigsaw/JigsawPuzzleWidget.h"
#include "UserInterfaces/Jigsaw/JigsawPieceWidget.h"
#include "UserInterfaces/Jigsaw/JigsawSlotWidget.h"

#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/Button.h"
#include "Components/UniformGridPanel.h"

#include "Blueprint/WidgetLayoutLibrary.h"

void UJigsawPuzzleWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	SpawnSlots();
}

void UJigsawPuzzleWidget::NativeConstruct()
{
	Super::NativeConstruct();

	SpawnPieces();
	
	PuzzleResetButton->OnClicked.AddDynamic(this, &UJigsawPuzzleWidget::ResetPuzzle);
}

void UJigsawPuzzleWidget::SpawnPieces()
{
	if (DesiredJigsawPieceWidget)
	{
		// Creates 16 puzzle pieces from different sliced coordinates
		for (int i = 0; i < AmountOfPieces; i++)
		{
			JigsawPieceWidget = CreateWidget<UJigsawPieceWidget>(this, DesiredJigsawPieceWidget);

			const int32 Coordinate = FMath::TruncToInt(FMath::Sqrt(static_cast<float>(AmountOfPieces)));
			const float CoordinateX = i % Coordinate;
			const float CoordinateY = i / Coordinate;

			if (JigsawPieceWidget)
			{
				JigsawPieceWidget->SetAmountOfPieces(AmountOfPieces);
				JigsawPieceWidget->SetCoordinate(FVector2D(CoordinateX, CoordinateY));
				JigsawPieceWidget->SetImage(JigsawPuzzleImage);

				if (PuzzlePiecesTray && JigsawPuzzleImage)
				{
					UCanvasPanelSlot* CanvasPanelSlot = PuzzlePiecesTray->AddChildToCanvas(JigsawPieceWidget);
					CanvasPanelSlot->SetAutoSize(true);

					const FVector2D ViewportSize = UWidgetLayoutLibrary::GetViewportSize(GetWorld()) / UWidgetLayoutLibrary::GetViewportScale(GetWorld());
					const float ViewportSizeX = ViewportSize.X * 0.38 - 128.f;
					const float ViewportSizeY = ViewportSize.Y - 280.f;

					// Randomly place each created puzzle pieces
					CanvasPanelSlot->SetPosition(FVector2D(FMath::RandRange(280.f, ViewportSizeX), FMath::RandRange(128.f, ViewportSizeY)));
				}
			}
		}
	}
}

void UJigsawPuzzleWidget::SpawnSlots()
{
	if (DesiredJigsawSlotWidget)
	{
		for (int i = 0; i < AmountOfPieces; i++)
		{
			JigsawSlotWidget = CreateWidget<UJigsawSlotWidget>(this, DesiredJigsawSlotWidget);

			const int32 Coordinate = FMath::TruncToInt(FMath::Sqrt(static_cast<float>(AmountOfPieces)));
			const float CoordinateX = i % Coordinate;
			const float CoordinateY = i / Coordinate;

			if (JigsawSlotWidget && PuzzleSlotGrid)
			{
				JigsawSlotWidget->SetAmountOfPieces(AmountOfPieces);
				JigsawSlotWidget->SetCoordinate(FVector2D(CoordinateX, CoordinateY));
				JigsawSlotWidget->SetImage(JigsawPuzzleImage);
				
				PuzzleSlotGrid->AddChildToUniformGrid(JigsawSlotWidget, CoordinateY, CoordinateX);
				JigsawSlotWidget->OnJigsawPieceCorrectlyPlaced.AddUObject(this, &UJigsawPuzzleWidget::PlacePieces);
			}
		}
	}
}

void UJigsawPuzzleWidget::PlacePieces()
{
	AmountOfPiecesCompleted++;
	
	if (AmountOfPiecesCompleted >= AmountOfPieces)
	{
		OnPuzzleCompleted.Broadcast();
	}
}

void UJigsawPuzzleWidget::ResetPuzzle()
{
	PuzzlePiecesTray->ClearChildren();
	PuzzleSlotGrid->ClearChildren();

	AmountOfPiecesCompleted = 0;

	SpawnPieces();
	SpawnSlots();
}

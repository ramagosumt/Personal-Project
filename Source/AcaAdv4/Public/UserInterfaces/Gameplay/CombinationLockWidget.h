// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CombinationLockWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCombinationLockPuzzleCompleted); 

class UButton;
class UTextBlock;

/**
 * 
 */
UCLASS()
class ACAADV4_API UCombinationLockWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	FOnCombinationLockPuzzleCompleted OnCombinationLockPuzzleCompleted;

protected:

	UPROPERTY(meta=(BindWidget))
	UButton* FirstKeyButton;

	UPROPERTY(meta=(BindWidget))
	UButton* SecondKeyButton;

	UPROPERTY(meta=(BindWidget))
	UButton* ThirdKeyButton;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* FirstKey;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* SecondKey;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* ThirdKey;

	int8 First = 0;
	int8 Second = 0;
	int8 Third = 0;

	virtual void NativeOnInitialized() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UFUNCTION()
	void SetFirstKey();

	UFUNCTION()
	void SetSecondKey();
	
	UFUNCTION()
	void SetThirdKey();
};

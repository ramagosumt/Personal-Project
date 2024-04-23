// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CreditsMenuWidget.generated.h"

class UMainMenuWidget;
class UButton;

/**
 * 
 */
UCLASS()
class ACAADV4_API UCreditsMenuWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	/** Main Menu Widget */
	UPROPERTY(EditDefaultsOnly, Category= "Widgets")
	TSubclassOf<UMainMenuWidget> DesiredMainMenuWidget;

	UPROPERTY(meta=(BindWidget))
	UButton* BackButton;

	virtual void NativeConstruct() override;

	UFUNCTION()
	void CloseThisMenu();
	
};

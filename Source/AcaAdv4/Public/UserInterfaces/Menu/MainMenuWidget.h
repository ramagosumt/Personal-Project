// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameStart);

class UCreditsMenuWidget;
class UButton;

/**
 * 
 */
UCLASS()
class ACAADV4_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	FOnGameStart OnGameStart;

protected:

	/** Main Menu Widget */
	UPROPERTY(EditDefaultsOnly, Category= "Widgets")
	TSubclassOf<UCreditsMenuWidget> DesiredCreditsMenuWidget;

	UPROPERTY(meta=(BindWidget))
	UButton* StartButton;

	UPROPERTY(meta=(BindWidget))
	UButton* OptionsButton;

	UPROPERTY(meta=(BindWidget))
	UButton* CreditsButton;

	UPROPERTY(meta=(BindWidget))
	UButton* QuitButton;

	virtual void NativeConstruct() override;

	UFUNCTION()
	void OpenLevel();

	UFUNCTION()
	void OpenCreditsMenu();

	UFUNCTION()
	void QuitGame();
};

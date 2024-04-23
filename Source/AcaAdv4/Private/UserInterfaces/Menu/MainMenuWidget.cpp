// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterfaces/Menu/MainMenuWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "UserInterfaces/Menu/CreditsMenuWidget.h"

void UMainMenuWidget::NativeConstruct()
{
	StartButton->OnClicked.AddUniqueDynamic(this, &UMainMenuWidget::OpenLevel);
	OptionsButton->SetIsEnabled(false);
	CreditsButton->OnClicked.AddUniqueDynamic(this, &UMainMenuWidget::OpenCreditsMenu);
	QuitButton->OnClicked.AddUniqueDynamic(this, &UMainMenuWidget::QuitGame);
}

void UMainMenuWidget::OpenLevel()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	const FInputModeGameOnly InputMode;
	PlayerController->SetInputMode(InputMode);
	PlayerController->SetShowMouseCursor(false);
	
	this->RemoveFromParent();
	OnGameStart.Broadcast();
}

void UMainMenuWidget::OpenCreditsMenu()
{
	UCreditsMenuWidget* CreditsMenuWidget = CreateWidget<UCreditsMenuWidget>(this, DesiredCreditsMenuWidget);
	CreditsMenuWidget->AddToViewport();
	this->RemoveFromParent();
}

void UMainMenuWidget::QuitGame()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, false);
}

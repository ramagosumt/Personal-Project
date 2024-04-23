// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterfaces/Menu/CreditsMenuWidget.h"
#include "Components/Button.h"
#include "UserInterfaces/Menu/MainMenuWidget.h"

void UCreditsMenuWidget::NativeConstruct()
{
	BackButton->OnClicked.AddUniqueDynamic(this, &UCreditsMenuWidget::CloseThisMenu);
}

void UCreditsMenuWidget::CloseThisMenu()
{
	UMainMenuWidget* MainMenuWidget = CreateWidget<UMainMenuWidget>(this, DesiredMainMenuWidget);
	MainMenuWidget->AddToViewport();
	this->RemoveFromParent();
}

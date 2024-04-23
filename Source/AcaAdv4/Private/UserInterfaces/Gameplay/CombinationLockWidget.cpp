#include "UserInterfaces/Gameplay/CombinationLockWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

void UCombinationLockWidget::NativeOnInitialized()
{
	Super::NativeConstruct();

	FirstKeyButton->OnClicked.AddUniqueDynamic(this, &UCombinationLockWidget::SetFirstKey);
	FirstKeyButton->IsFocusable = false;
	
	SecondKeyButton->OnClicked.AddUniqueDynamic(this, &UCombinationLockWidget::SetSecondKey);
	SecondKeyButton->IsFocusable = false;

	ThirdKeyButton->OnClicked.AddUniqueDynamic(this, &UCombinationLockWidget::SetThirdKey);
	ThirdKeyButton->IsFocusable = false;
	
}

void UCombinationLockWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (First == 7 && Second == 8 && Third == 4)
	{
		OnCombinationLockPuzzleCompleted.Broadcast();
	}
}

void UCombinationLockWidget::SetFirstKey()
{
	First++;
	if (First > 9)
	{
		First = 0;
	}
	
	FirstKey->SetText(FText::Format(FText::FromString("{0}"), First));
}

void UCombinationLockWidget::SetSecondKey()
{
	Second++;
	if (Second > 9)
	{
		Second = 0;
	}
	
	SecondKey->SetText(FText::Format(FText::FromString("{0}"), Second));
}

void UCombinationLockWidget::SetThirdKey()
{
	Third++;
	if (Third > 9)
	{
		Third = 0;
	}
	
	ThirdKey->SetText(FText::Format(FText::FromString("{0}"), Third));
}

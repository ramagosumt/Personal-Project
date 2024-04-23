#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "DialogueDataStructs.generated.h"

USTRUCT()
struct FDialogueOptions
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FText Answer;

	UPROPERTY(EditAnywhere)
	int32 AnswerIndex;
	
};

USTRUCT()
struct FDialogueMessages
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TArray<FText> Messages;

	UPROPERTY(EditAnywhere)
	TArray<FDialogueOptions> MessagesOptions;
	
};

USTRUCT()
struct FDialogueData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category= "DialogueData")
	FName ID;

	UPROPERTY(EditAnywhere, Category= "DialogueData")
	FDialogueMessages DialogueMessages;
};

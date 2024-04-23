#include "World/ItemToInteract.h"
#include "Engine/DataTable.h"
#include "Data/DialogueDataStructs.h"
#include "Player/MainCharacter.h"
#include "UserInterfaces/MainHUD.h"

AItemToInteract::AItemToInteract()
{
	// Tag for outlining
	MainMesh->ComponentTags.Add(TEXT("EligibleForOutlining"));

	// Collision channel for outlining
	MainMesh->SetCollisionObjectType(ECollisionChannel::ECC_Interactable);
}

void AItemToInteract::BeginPlay()
{
	Super::BeginPlay();

	// Feed the Dialogue Data with data from the Dialogue Table
	if (DialogueTable && !DesiredDialogueID.IsNone()) DialogueData = DialogueTable->FindRow<FDialogueData>(DesiredDialogueID, DesiredDialogueID.ToString());
}

void AItemToInteract::BeginFocus()
{
	// Start outlining
	if (MainMesh) MainMesh->SetRenderCustomDepth(true);
}

void AItemToInteract::EndFocus()
{
	// End outlining
	if (MainMesh) MainMesh->SetRenderCustomDepth(false);
}

void AItemToInteract::Interact(AMainCharacter* MainCharacter)
{
	// Start interacting
	if (DialogueData) MainCharacter->GetHUD()->UpdateDialogueWidget(DialogueData);
}

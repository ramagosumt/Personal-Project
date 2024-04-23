#include "World/Chalkboard.h"
#include "Components/DecalComponent.h"
#include "Components/SphereComponent.h"
#include "Data/DialogueDataStructs.h"
#include "Kismet/KismetMaterialLibrary.h"
#include "Player/MainCharacter.h"
#include "UserInterfaces/MainHUD.h"
#include "UserInterfaces/Interaction/DialogueWidget.h"
#include "UserInterfaces/Jigsaw/JigsawPuzzleWidget.h"

AChalkboard::AChalkboard()
{
	ScanRadius = CreateDefaultSubobject<USphereComponent>(TEXT("ScanRadius"));
	ScanRadius->SetupAttachment(MainMesh);
	ScanRadius->SetRelativeLocation(FVector(0.f, 0.f, 190.f));
	ScanRadius->SetSphereRadius(150.f);
	ScanRadius->OnComponentBeginOverlap.AddDynamic(this, &AChalkboard::OnOverlapBegin);
	ScanRadius->OnComponentEndOverlap.AddDynamic(this, &AChalkboard::OnOverlapEnd);
	
	KeypadFirstNumber = CreateDefaultSubobject<UDecalComponent>(TEXT("KeypadFirstNumber"));
	KeypadFirstNumber->SetupAttachment(MainMesh);
	KeypadFirstNumber->SetRelativeLocation(FVector(0.f));
	KeypadFirstNumber->SetVisibility(false);
	
	KeypadSecondNumber = CreateDefaultSubobject<UDecalComponent>(TEXT("KeypadSecondNumber"));
	KeypadSecondNumber->SetupAttachment(MainMesh);
	KeypadSecondNumber->SetRelativeLocation(FVector(0.f));
	KeypadSecondNumber->SetVisibility(false);
	
	KeypadThirdNumber = CreateDefaultSubobject<UDecalComponent>(TEXT("KeypadThirdNumber"));
	KeypadThirdNumber->SetupAttachment(MainMesh);
	KeypadThirdNumber->SetRelativeLocation(FVector(0.f));
	KeypadThirdNumber->SetVisibility(false);
	
	KeypadFourthNumber = CreateDefaultSubobject<UDecalComponent>(TEXT("KeypadFourthNumber"));
	KeypadFourthNumber->SetupAttachment(MainMesh);
	KeypadFourthNumber->SetRelativeLocation(FVector(0.f));
	KeypadFourthNumber->SetVisibility(false);
	
}

void AChalkboard::BeginPlay()
{
	Super::BeginPlay();

	FVector MeshBounds = MainMesh->Bounds.GetBox().GetSize();
	MeshBounds.Z += 25.f;
	
	if (DesiredDecalFirstNumberMaterial)
	{
		DecalFirstNumberMaterialInstance = UKismetMaterialLibrary::CreateDynamicMaterialInstance(GetWorld(), DesiredDecalFirstNumberMaterial);
		
		KeypadFirstNumber->SetDecalMaterial(DecalFirstNumberMaterialInstance);
		KeypadFirstNumber->DecalSize = FVector(25.f, 25.f, 25.f);
		KeypadFirstNumber->SetRelativeLocation(FVector(-75.f, 0.f, MeshBounds.Z));
		KeypadFirstNumber->SetRelativeRotation(FRotator(180.f, 90.f, -90.f));
		//KeypadFirstNumber->SetVisibility(true);
	}

	if (DesiredDecalSecondNumberMaterial)
	{
		DecalSecondNumberMaterialInstance = UKismetMaterialLibrary::CreateDynamicMaterialInstance(GetWorld(), DesiredDecalSecondNumberMaterial);
		
		KeypadSecondNumber->SetDecalMaterial(DecalSecondNumberMaterialInstance);
		KeypadSecondNumber->DecalSize = FVector(25.f);
		KeypadSecondNumber->SetRelativeLocation(FVector(-25.f, 0.f, MeshBounds.Z));
		KeypadSecondNumber->SetRelativeRotation(FRotator(180.f, 90.f, -90.f));
		KeypadSecondNumber->SetVisibility(true);
	}

	if (DesiredDecalThirdNumberMaterial)
	{
		DecalThirdNumberMaterialInstance = UKismetMaterialLibrary::CreateDynamicMaterialInstance(GetWorld(), DesiredDecalThirdNumberMaterial);
		
		KeypadThirdNumber->SetDecalMaterial(DecalThirdNumberMaterialInstance);
		KeypadThirdNumber->DecalSize = FVector(25.f);
		KeypadThirdNumber->SetRelativeLocation(FVector(25.f, 0.f, MeshBounds.Z));
		KeypadThirdNumber->SetRelativeRotation(FRotator(180.f, 90.f, -90.f));
	}

	if (DesiredDecalFourthNumberMaterial)
	{
		DecalFourthNumberMaterialInstance = UKismetMaterialLibrary::CreateDynamicMaterialInstance(GetWorld(), DesiredDecalFourthNumberMaterial);
		
		KeypadFourthNumber->SetDecalMaterial(DecalFourthNumberMaterialInstance);
		KeypadFourthNumber->DecalSize = FVector(25.f);
		KeypadFourthNumber->SetRelativeLocation(FVector(75.f, 0.f, MeshBounds.Z));
		KeypadFourthNumber->SetRelativeRotation(FRotator(180.f, 90.f, -90.f));
	}
}

void AChalkboard::Interact(AMainCharacter* MainCharacter)
{
	Super::Interact(MainCharacter);

	if (InteractingCharacter)
	{
		if (InteractingCharacter->bIsJigsawPuzzleCompleted && IsDialogueEnd)
		{
			UpdateBoard();
		}
		else if (InteractingCharacter->bIsClockPuzzleCompleted && IsDialogueEnd)
		{
			UpdateBoard();
		}

		IsDialogueEnd = false;
	}
}

void AChalkboard::UpdateDialogueState()
{
	if (InteractingCharacter && this == InteractingCharacter->InteractionData.CurrentInteractable)
	{
		IsDialogueEnd = true;
	}
}

void AChalkboard::UpdateDialogueData()
{
	if (!DialogueData->DialogueMessages.Messages.Last().EqualTo(FText::FromString("Write number on board.")))
	{
		DialogueData->DialogueMessages.Messages.Add(FText::FromString("Write number on board."));
	}
}

void AChalkboard::UpdateBoard()
{
	if (InteractingCharacter)
	{
		if (InteractingCharacter->bIsJigsawPuzzleCompleted)
		{
			DialogueData->DialogueMessages.Messages.RemoveAt(DialogueData->DialogueMessages.Messages.Num()-1);
			KeypadThirdNumber->SetVisibility(true);
		}
		else if (InteractingCharacter->bIsClockPuzzleCompleted)
		{
			if (DialogueData->DialogueMessages.Messages.Last().EqualTo(FText::FromString("Write number on board.")))
			{
				DialogueData->DialogueMessages.Messages.RemoveAt(DialogueData->DialogueMessages.Messages.Num()-1);
			}
			
			KeypadFourthNumber->SetVisibility(true);
		}
		
	}
}

void AChalkboard::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		InteractingCharacter = Cast<AMainCharacter>(OtherActor);

		InteractingCharacter->GetHUD()->GetDialogueWidget()->OnDialogueEnd.AddUObject(this, &AChalkboard::UpdateDialogueState);
		InteractingCharacter->GetHUD()->GetJigsawPuzzleWidget()->OnPuzzleCompleted.AddUObject(this, &AChalkboard::UpdateDialogueData);
		InteractingCharacter->OnClockPuzzleCompleted.AddUObject(this, &AChalkboard::UpdateDialogueData);
	}
}

void AChalkboard::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (InteractingCharacter)
	{
		InteractingCharacter = nullptr;
	}
}

#include "World/ClockPuzzle.h"
#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"
#include "Player/MainCharacter.h"
#include "UserInterfaces/MainHUD.h"
#include "UserInterfaces/Interaction/DialogueWidget.h"

AClockPuzzle::AClockPuzzle()
{
	HourHand = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HourHand"));
	HourHand->SetupAttachment(MainMesh);

	MinuteHand = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MinuteHand"));
	MinuteHand->SetupAttachment(MainMesh);

	ScanRadius = CreateDefaultSubobject<USphereComponent>(TEXT("ScanRadius"));
	ScanRadius->SetupAttachment(MainMesh);
	ScanRadius->SetSphereRadius(50.f);
	ScanRadius->OnComponentBeginOverlap.AddDynamic(this, &AClockPuzzle::OnOverlapBegin);
	ScanRadius->OnComponentEndOverlap.AddDynamic(this, &AClockPuzzle::OnOverlapEnd);

	ClockView = CreateDefaultSubobject<UCameraComponent>(TEXT("ClockView"));
	ClockView->SetupAttachment(MainMesh);
	ClockView->SetRelativeLocation(FVector(0.f, -60.f, 0.f));
	ClockView->SetRelativeRotation(FRotator(0.f, 90.f, 0.f));

	ClockPuzzleGameMode = EClockPuzzleGameMode::ECP_ExitMode;

	HourRotation = HourHand->GetRelativeRotation();
	MinuteRotation = MinuteHand->GetRelativeRotation();
	
	RotateAngle = FRotator(30.f, 0.f, 0.f);
}

void AClockPuzzle::BeginPlay()
{
	Super::BeginPlay();
	
}

void AClockPuzzle::BeginFocus()
{
	if (!IsPuzzleComplete)
	{
		Super::BeginFocus();
	}
}

void AClockPuzzle::Interact(AMainCharacter* PlayerCharacter)
{
	if (!IsPuzzleComplete)
	{
		switch (ClockPuzzleGameMode)
		{
		case EClockPuzzleGameMode::ECP_ExitMode:
			Super::Interact(PlayerCharacter);
			if (PlayerCharacter)
			{
				if (IsDialogueEnd)
				{
					PlayerCharacter->GetHUD()->HideCrosshairWidget();
					PlayerCharacter->CharacterPuzzleMode = ECharacterPuzzleMode::EGM_ClockGameMode;
			
					APlayerController* PlayerController = Cast<APlayerController>(PlayerCharacter->GetController());
			
					PlayerController->SetViewTargetWithBlend(ClockView->GetOwner(), 0.4f);
					PlayerController->SetCinematicMode(true, true, true);

					MainMesh->SetRenderCustomDepth(false);
					HourHand->SetRenderCustomDepth(true);

					ClockPuzzleGameMode = EClockPuzzleGameMode::ECP_HourMode;
				}

				IsDialogueEnd = false;
			}
		
			break;
		default:
			;
		}
	}
}

void AClockPuzzle::OpenPuzzle()
{
	if (InteractingCharacter)
	{
		if (this == InteractingCharacter->InteractionData.CurrentInteractable)
		{
			IsDialogueEnd = true;
		}
		else
		{
			InteractingCharacter = nullptr;
		}
	}
}

void AClockPuzzle::ClosePuzzle()
{
	if (InteractingCharacter && ClockPuzzleGameMode != EClockPuzzleGameMode::ECP_ExitMode)
	{
		InteractingCharacter->GetHUD()->ShowCrosshairWidget();
		
		APlayerController* PlayerController = Cast<APlayerController>(InteractingCharacter->GetController());

		PlayerController->SetViewTargetWithBlend(InteractingCharacter->FPCamera->GetOwner(), 0.4f);
		PlayerController->SetCinematicMode(false, true, true);

		MainMesh->SetRenderCustomDepth(true);
		HourHand->SetRenderCustomDepth(false);
		MinuteHand->SetRenderCustomDepth(false);

		ClockPuzzleGameMode = EClockPuzzleGameMode::ECP_ExitMode;
	}
}

void AClockPuzzle::LockPuzzle()
{
	IsPuzzleComplete = true;
	InteractingCharacter->bIsClockPuzzleCompleted = IsPuzzleComplete;

	ClosePuzzle();
	EndFocus();

	InteractingCharacter->OnClockPuzzleCompleted.Broadcast();
}

void AClockPuzzle::SwitchToAnotherHand()
{
	switch (ClockPuzzleGameMode)
	{
	case EClockPuzzleGameMode::ECP_HourMode:
		{
			ClockPuzzleGameMode = EClockPuzzleGameMode::ECP_MinuteMode;

			HourHand->SetRenderCustomDepth(false);
			MinuteHand->SetRenderCustomDepth(true);
			break;
		}
	case EClockPuzzleGameMode::ECP_MinuteMode:
		{
			ClockPuzzleGameMode = EClockPuzzleGameMode::ECP_HourMode;

			HourHand->SetRenderCustomDepth(true);
			MinuteHand->SetRenderCustomDepth(false);
			break;
		}
	default:
		;
	}
}

void AClockPuzzle::RotateHandUp()
{
	switch (ClockPuzzleGameMode)
	{
	case EClockPuzzleGameMode::ECP_HourMode:
		{
			if (FMath::IsNearlyEqual(HourRotation.Pitch, 360.f, 0.1f))
			{
				HourRotation.Pitch = 0.f;
			}
			
			HourRotation.Pitch += RotateAngle.Pitch;
			HourHand->SetRelativeRotation(HourRotation);
		
			break;
		}
	case EClockPuzzleGameMode::ECP_MinuteMode:
		{
			if (FMath::IsNearlyEqual(MinuteRotation.Pitch, 360.f, 0.1f))
			{
				MinuteRotation.Pitch = 0.f;
			}
			
			MinuteRotation.Pitch += RotateAngle.Pitch;
			MinuteHand->SetRelativeRotation(MinuteRotation);
		
			break;
		}
	default:
		;
	}
}

void AClockPuzzle::RotateHandDown()
{
	switch (ClockPuzzleGameMode)
	{
	case EClockPuzzleGameMode::ECP_HourMode:
		{
			if (FMath::IsNearlyEqual(HourRotation.Pitch, 0.f, 0.1f))
			{
				HourRotation.Pitch = 360.f;
			}
			
			HourRotation.Pitch -= RotateAngle.Pitch;
			HourHand->SetRelativeRotation(HourRotation);
		
			break;
		}
	case EClockPuzzleGameMode::ECP_MinuteMode:
		{
			if (FMath::IsNearlyEqual(MinuteRotation.Pitch, 0.f, 0.1f))
			{
				MinuteRotation.Pitch = 360.f;
			}
			
			MinuteRotation.Pitch -= RotateAngle.Pitch;
			MinuteHand->SetRelativeRotation(MinuteRotation);
		
			break;
		}
	default:
		;
	}
}

void AClockPuzzle::CheckRotation()
{
	if (HourRotation.Pitch == 330.f && MinuteRotation.Pitch == 150.f)
	{
		LockPuzzle();
	}
}

void AClockPuzzle::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		InteractingCharacter = Cast<AMainCharacter>(OtherActor);

		InteractingCharacter->GetHUD()->GetDialogueWidget()->OnDialogueEnd.AddUObject(this, &AClockPuzzle::OpenPuzzle);
		InteractingCharacter->OnPuzzleClosed.AddUObject(this, &AClockPuzzle::ClosePuzzle);
		InteractingCharacter->OnSwitchToAnotherHand.AddUniqueDynamic(this, &AClockPuzzle::SwitchToAnotherHand);
		InteractingCharacter->OnRotateClockHandUp.AddUniqueDynamic(this, &AClockPuzzle::RotateHandUp);
		InteractingCharacter->OnRotateClockHandDown.AddUniqueDynamic(this, &AClockPuzzle::RotateHandDown);
		InteractingCharacter->OnCompleteClockPuzzle.AddUniqueDynamic(this, &AClockPuzzle::CheckRotation);
	}
}

void AClockPuzzle::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (InteractingCharacter)
	{
		InteractingCharacter = nullptr;
	}
}

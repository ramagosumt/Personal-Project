#include "World/Locker.h"
#include "Components/TimelineComponent.h"

ALocker::ALocker()
{
	// Door Mesh Component
	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
	DoorMesh->SetupAttachment(MainMesh);
	DoorMesh->SetRelativeLocation(FVector(-30.f, 20.f, 0.f));
	
	// Tag for outlining
	DoorMesh->ComponentTags.Add(TEXT("NotEligibleForOutlining"));
	
	// Collision channel for outlining
	DoorMesh->SetCollisionProfileName(TEXT("Custom"));
	DoorMesh->SetCollisionObjectType(ECollisionChannel::ECC_NonInteractable);

	// Timeline
	OpenDoorTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("OpenDoorTimeline"));
	
}

void ALocker::BeginPlay()
{
	Super::BeginPlay();
	
	FOnTimelineFloat DoorMovementValue;
	FOnTimelineEvent OpenDoorFinishedEvent;

	DoorMovementValue.BindUFunction(this, FName("OpenDoorStart"));
	OpenDoorFinishedEvent.BindUFunction(this, FName("OpenDoorEnd"));

	if (DoorMovement)
	{
		// Feed DoorMovement to DoorMovementValue to Value in OpenDoorTick
		OpenDoorTimeline->AddInterpFloat(DoorMovement, DoorMovementValue);
	}
	
	OpenDoorTimeline->SetTimelineFinishedFunc(OpenDoorFinishedEvent);

	ComponentInitialRotation = ComponentTargetRotation = DoorMesh->GetRelativeRotation();
	ComponentTargetRotation.Yaw += 102.f;
}

void ALocker::Interact(AMainCharacter* PlayerCharacter)
{
	if (DoorMesh->GetRelativeRotation().Yaw < 102.f && !bIsOpeningDoor)
	{
		OpenDoorTimeline->PlayFromStart();
		ChangeDoorCollision();
		bIsOpeningDoor = true;
	}
	else if (DoorMesh->GetRelativeRotation().Yaw >= 102.f)
	{
		OpenDoorTimeline->Reverse();
		bIsOpeningDoor = true;
	}
}

void ALocker::BeginFocus()
{
	Super::BeginFocus();
	
	if (DoorMesh->ComponentHasTag(TEXT("NotEligibleForOutlining")))
	{
		DoorMesh->SetRenderCustomDepth(false);
	}
	else
	{
		DoorMesh->SetRenderCustomDepth(true);
	}
}

void ALocker::EndFocus()
{
	Super::EndFocus();

	DoorMesh->SetRenderCustomDepth(false);
}

void ALocker::OpenDoorStart(float Value)
{
	// Lerp door from 0.f Yaw to 102.f Yaw
	const FRotator NewRotation = FMath::Lerp(ComponentInitialRotation, ComponentTargetRotation, Value);
	DoorMesh->SetRelativeRotation(NewRotation);
}

void ALocker::OpenDoorEnd()
{
	bIsOpeningDoor = false;

	if (OpenDoorTimeline->GetPlaybackPosition() == 0.f)
	{
		ChangeDoorCollision();
	}
}

void ALocker::ChangeDoorCollision()
{
	if (DoorMesh->ComponentHasTag(TEXT("NotEligibleForOutlining")))
	{
		DoorMesh->ComponentTags.Remove(TEXT("NotEligibleForOutlining"));
		DoorMesh->ComponentTags.Add(TEXT("EligibleForOutlining"));
		DoorMesh->SetCollisionObjectType(ECollisionChannel::ECC_Interactable);
		DoorMesh->SetRenderCustomDepth(true);
	}
	else
	{
		DoorMesh->ComponentTags.Remove(TEXT("EligibleForOutlining"));
		DoorMesh->ComponentTags.Add(TEXT("NotEligibleForOutlining"));
		DoorMesh->SetCollisionObjectType(ECollisionChannel::ECC_NonInteractable);
		DoorMesh->SetRenderCustomDepth(false);
	}
}

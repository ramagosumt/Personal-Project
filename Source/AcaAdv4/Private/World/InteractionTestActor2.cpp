#include "World/InteractionTestActor2.h"

// Sets default values
AInteractionTestActor2::AInteractionTestActor2()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Static Mesh Component
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(GetRootComponent());

	// Tag for outlining and obtaining
	StaticMeshComponent->ComponentTags.Add(TEXT("EligibleForOutlining"));
	StaticMeshComponent->ComponentTags.Add(TEXT("EligibleForObtaining"));
	
	// Collision channel for outlining
	StaticMeshComponent->SetCollisionProfileName(TEXT("Custom"));
	StaticMeshComponent->SetCollisionObjectType(ECollisionChannel::ECC_Interactable);
}

// Called when the game starts or when spawned
void AInteractionTestActor2::BeginPlay()
{
	Super::BeginPlay();

	InteractableData = InstanceInteractableData;
}

// Called every frame
void AInteractionTestActor2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInteractionTestActor2::BeginFocus()
{
	if (StaticMeshComponent)
	{
		StaticMeshComponent->SetRenderCustomDepth(true);
	}

	UE_LOG(LogTemp, Warning, TEXT("Calling BeginFocus override on interface actor"));
}

void AInteractionTestActor2::EndFocus()
{
	if (StaticMeshComponent)
	{
		StaticMeshComponent->SetRenderCustomDepth(false);
	}

	UE_LOG(LogTemp, Warning, TEXT("Calling EndFocus override on interface actor"));
}

void AInteractionTestActor2::BeginInteract()
{
	UE_LOG(LogTemp, Warning, TEXT("Calling BeginInteract override on interface actor"));
}

void AInteractionTestActor2::EndInteract()
{
	UE_LOG(LogTemp, Warning, TEXT("Calling EndInteract override on interface actor"));
}

void AInteractionTestActor2::Interact(AMainCharacter* MainCharacter)
{
	UE_LOG(LogTemp, Warning, TEXT("Calling Interact override on interface actor"));
}


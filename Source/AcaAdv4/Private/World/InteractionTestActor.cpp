// Fill out your copyright notice in the Description page of Project Settings.


#include "World/InteractionTestActor.h"

// Sets default values
AInteractionTestActor::AInteractionTestActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Static Mesh Component
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(GetRootComponent());

	// Tag for outlining
	StaticMeshComponent->ComponentTags.Add(TEXT("NotEligibleForOutlining"));
	
	// Collision channel for outlining
	StaticMeshComponent->SetCollisionProfileName(TEXT("Custom"));
	StaticMeshComponent->SetCollisionObjectType(ECollisionChannel::ECC_NonInteractable);
}

// Called when the game starts or when spawned
void AInteractionTestActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInteractionTestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInteractionTestActor::BeginFocus()
{
	if (StaticMeshComponent)
	{
		StaticMeshComponent->SetRenderCustomDepth(true);
	}

	UE_LOG(LogTemp, Warning, TEXT("Calling BeginFocus override on interface actor"));
}

void AInteractionTestActor::EndFocus()
{
	if (StaticMeshComponent)
	{
		StaticMeshComponent->SetRenderCustomDepth(false);
	}

	UE_LOG(LogTemp, Warning, TEXT("Calling EndFocus override on interface actor"));
}

void AInteractionTestActor::BeginInteract()
{
	UE_LOG(LogTemp, Warning, TEXT("Calling BeginInteract override on interface actor"));
}

void AInteractionTestActor::EndInteract()
{
	UE_LOG(LogTemp, Warning, TEXT("Calling EndInteract override on interface actor"));
}

void AInteractionTestActor::Interact(AMainCharacter* MainCharacter)
{
	UE_LOG(LogTemp, Warning, TEXT("Calling Interact override on interface actor"));
}


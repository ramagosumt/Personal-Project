#include "World/ItemNotToInteract.h"

// Sets default values
AItemNotToInteract::AItemNotToInteract()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Main Mesh Component
	MainMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));

	// Tag for outlining
	MainMesh->ComponentTags.Add(TEXT("NotEligibleForOutlining"));
	
	// Collision channel for outlining
	MainMesh->SetCollisionProfileName(TEXT("Custom"));
	MainMesh->SetCollisionObjectType(ECollisionChannel::ECC_NonInteractable);
}

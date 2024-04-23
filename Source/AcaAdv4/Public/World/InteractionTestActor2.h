// This file creates a test item to interact with

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/InteractionInterface.h"
#include "InteractionTestActor2.generated.h"

#define ECC_Interactable ECC_GameTraceChannel2 // User-defined collision channel in Project Setting

UCLASS()
class ACAADV4_API AInteractionTestActor2 : public AActor, public IInteractionInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractionTestActor2();

protected:
	UPROPERTY(EditAnywhere, Category= "TestActor")
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditInstanceOnly, Category= "TestActor")
	FInteractableData InstanceInteractableData;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void BeginFocus() override;
	virtual void EndFocus() override;
	virtual void BeginInteract() override;
	virtual void EndInteract() override;
	virtual void Interact(AMainCharacter* MainCharacter) override;

};

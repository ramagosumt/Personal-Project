// This file creates a test item to interact with

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/InteractionInterface.h"
#include "InteractionTestActor.generated.h"

#define ECC_NonInteractable ECC_GameTraceChannel1 // User-defined collision channel in Project Setting

UCLASS()
class ACAADV4_API AInteractionTestActor : public AActor, public IInteractionInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractionTestActor();

protected:
	UPROPERTY(EditAnywhere, Category= "TestActor")
	UStaticMeshComponent* StaticMeshComponent;
	
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

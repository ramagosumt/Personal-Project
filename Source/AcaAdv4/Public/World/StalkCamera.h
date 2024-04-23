// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "World/ItemNotToInteract.h"
#include "StalkCamera.generated.h"

class AMainCharacter;
class USphereComponent;

/**
 * 
 */
UCLASS()
class ACAADV4_API AStalkCamera : public AItemNotToInteract
{
	GENERATED_BODY()
	
	FTimerHandle InitialInteractionCheck;
	
	UPROPERTY(EditAnywhere, Category= "Setup")
	float InitialInteractionCheckDelayTime;

protected:

	UPROPERTY(VisibleAnywhere)
	AMainCharacter* InteractingCharacter;
	
	UPROPERTY(VisibleAnywhere)
	USphereComponent* ScanRadius;

	UPROPERTY()
	TArray<AActor*> InteractingActors;

	UPROPERTY(VisibleAnywhere, Category= "Components")
	UStaticMeshComponent* CameraPart;

	AStalkCamera();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
	virtual void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void InteractionCheck();
	
};

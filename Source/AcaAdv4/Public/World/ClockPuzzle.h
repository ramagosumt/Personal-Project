// This file creates a clock that is an item to interact 

#pragma once

#include "CoreMinimal.h"
#include "World/ItemToInteract.h"
#include "ClockPuzzle.generated.h"

class UCameraComponent;
class USphereComponent;

UENUM()
enum class EClockPuzzleGameMode : uint8
{
	ECP_ExitMode UMETA(DisplayName= "ExitMode"),
	ECP_HourMode UMETA(DisplayName= "HourMode"),
	ECP_MinuteMode UMETA(DisplayName= "MinuteMode")
};

/**
 * 
 */
UCLASS()
class ACAADV4_API AClockPuzzle : public AItemToInteract
{
	GENERATED_BODY()

	/**
	 * PROPERTIES AND VARIABLES
	 **/

	/* Mesh Components */
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* HourHand;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* MinuteHand;

	/* Collision Components */
	UPROPERTY(VisibleAnywhere)
	USphereComponent* ScanRadius;

	/* Camera Components */
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* ClockView;

public:

	/**
	 * PROPERTIES AND VARIABLES
	 **/

	UPROPERTY(VisibleAnywhere)
	AMainCharacter* InteractingCharacter;

	/**
	 * FUNCTIONS
	 **/

	AClockPuzzle();

protected:

	/**
	 * PROPERTIES AND VARIABLES
	 **/
	
	FRotator HourRotation;
	FRotator MinuteRotation;
	FRotator RotateAngle;

	bool IsDialogueEnd;
	bool IsPuzzleComplete;

	UPROPERTY(VisibleAnywhere)
	EClockPuzzleGameMode ClockPuzzleGameMode;
	
	/**
	 * FUNCTIONS
	 **/

	virtual void BeginPlay() override;

	virtual void BeginFocus() override;
	virtual void Interact(AMainCharacter* PlayerCharacter) override;

	void OpenPuzzle();
	void ClosePuzzle();
	void LockPuzzle();

	UFUNCTION()
	void SwitchToAnotherHand();

	UFUNCTION()
	void RotateHandUp();

	UFUNCTION()
	void RotateHandDown();

	UFUNCTION()
	void CheckRotation();

	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
	virtual void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
};

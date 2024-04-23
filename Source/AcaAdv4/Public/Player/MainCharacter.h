// The Main Character

/** Includes */
#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Character.h"

#include "Components/MainInventoryComponent.h"

#include "Interfaces/InteractionInterface.h"

#include "MainCharacter.generated.h"

/** Defines */
#define ECC_NonInteractable ECC_GameTraceChannel1 // User-defined collision channel for ItemNotToInteract
#define ECC_Interactable ECC_GameTraceChannel2 // User-defined collision channel for ItemToInteract

/** Delegations */
/* General Puzzle */
DECLARE_MULTICAST_DELEGATE(FOnPuzzleClosed) // Called when the player closes any puzzle
DECLARE_MULTICAST_DELEGATE(FOnClockPuzzleCompleted) // Called when the player complete the clock puzzle

/* Clock Puzzle */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSwitchToAnotherHand); // Called when the player changes the clock hand
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRotateClockHandUp); // Called when the player increases time
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRotateClockHandDown); // Called when the player decreases time
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCompleteClockPuzzle); // Called when the player finishes the puzzle

/** Class Pre-Declarations */
class UCameraComponent;
class USphereComponent;
class UMainInventoryComponent;

class AMainHUD;

/** Enumerations */
UENUM()
enum class ECharacterPuzzleMode : uint8
{
	EGM_NoPuzzleGameMode UMETA(DisplayName = "NoPuzzleGameMode"),
	EGM_JigsawGameMode UMETA(DisplayName= "JigsawGameMode"),
	EGM_ClockGameMode UMETA(DisplayName= "ClockGameMode"),
	EGM_DoorGameMode UMETA(DisplayName= "DoorGameMode")
};

/** Structures */
USTRUCT()
struct FMainCharacterInteractionData // Data of interaction
{
	GENERATED_BODY()

	FMainCharacterInteractionData() :
	CurrentInteractable(nullptr),
	LastInteractionCheckTime(0.0f)
	{
		
	};

	// A reference to the actor that the main character is currently interact with
	UPROPERTY()
	AActor* CurrentInteractable;

	// The last time the engine checks for a happened interaction
	UPROPERTY()
	float LastInteractionCheckTime;
};

UCLASS()
class ACAADV4_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	/**
	 * PROPERTIES AND VARIABLES
	 **/

	/** Interface Data */
	FMainCharacterInteractionData InteractionData;

	/** Delegations */
	FOnPuzzleClosed OnPuzzleClosed; // Close any puzzle
	FOnClockPuzzleCompleted OnClockPuzzleCompleted; // Complete Clock Puzzle
	FOnSwitchToAnotherHand OnSwitchToAnotherHand; // Change Clock hand
	FOnRotateClockHandUp OnRotateClockHandUp; // Increase Clock time
	FOnRotateClockHandDown OnRotateClockHandDown; // Decrease Clock time
	FOnCompleteClockPuzzle OnCompleteClockPuzzle; // Check Clock time
	
	/** Actor Components */
	/* Perspective */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "Components | Perspective")
	UCameraComponent* FPCamera;

	UPROPERTY(VisibleAnywhere, Category= "Character | Inventory")
	bool bIsInFocus;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "Components | Perspective")
	UStaticMeshComponent* WieldingItemComponent;

	UPROPERTY(VisibleAnywhere, Category= "Character | Puzzles")
	bool bIsJigsawPuzzleCompleted;

	UPROPERTY(VisibleAnywhere, Category= "Character | Puzzles")
	bool bIsClockPuzzleCompleted;

	/* Collision */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "Components | Collision")
	USphereComponent* CollisionSphere;

	/** Enums Configurations */
	/* Puzzle */
	UPROPERTY(VisibleAnywhere)
	ECharacterPuzzleMode CharacterPuzzleMode;
	
	/**
	 * FUNCTIONS
	 **/
	
	// Sets default values for this character's properties
	AMainCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** Movement Functions */
	void MoveVertical(float Value);

	void MoveHorizontal(float Value);

	/** Object Outlining Functions */
	FORCEINLINE bool IsInteracting() const { return GetWorld()->GetTimerManager().IsTimerActive(TimerHandle_Interaction); }

	/** Inventory Functions */
	FORCEINLINE UMainInventoryComponent* GetInventory() const { return MainInventoryComponent; }

	// Update the Interaction Widget
	void UpdateInteractionWidget() const;

	// Drop 
	void DropInventoryItem(UItemBase* ItemToDrop, const int32 Quantity);

	/** Interaction Functions */
	FORCEINLINE AMainHUD* GetHUD() const { return MainHUD; }

	// Update the Dialogue Widget
	void UpdateDialogueWidget() const;

protected:
	
	/**
	 * PROPERTIES AND VARIABLES
	 **/

	/** HUD */
	UPROPERTY()
	AMainHUD* MainHUD;
	
	/** Object Outlining Variables */
	// Interface for the Main Character
	UPROPERTY(VisibleAnywhere, Category= "Character | Interaction")
	TScriptInterface<IInteractionInterface> TargetInteractable;

	// Line Tracing period
	float InteractionCheckFrequency;

	// Line Tracing range
	float InteractionCheckDistance;

	// To handle the time before each interaction
	FTimerHandle TimerHandle_Interaction;

	/** Inventory Variables */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "Character | Inventory")
	UMainInventoryComponent* MainInventoryComponent;
	
	/**
	 * FUNCTIONS
	 **/
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
	virtual void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	/** Object Outlining Functions */

	// Start Tracing
	void PerformInteractionCheck();

	// Trace successful
	void FoundInteractable(AActor* NewInteractable);

	// Trace unsuccessful
	void NoInteractableFound();

	// Start timing for interaction
	void BeginInteract();

	// End timing for interaction
	void EndInteract();

	// Truly interact with the object
	void Interact();

	// Drop an item from the inventory
	void Drop();

	// Scrolling down the inventory
	void InventoryPlus();

	// Scrolling up the inventory
	void InventoryMinus();

	// Exit from any puzzle
	UFUNCTION()
	void ExitPuzzle();
	
	void RotateClockUp();

	void RotateClockDown();

	void ConfirmClockTime();

};

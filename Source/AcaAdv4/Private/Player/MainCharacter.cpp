/**
 * INCLUDE STATEMENTS
 */

#include "Player/MainCharacter.h"

// Actors
#include "World/ItemToObtain.h"

// Actor Components
#include "Camera/CameraComponent.h"
#include "Components/MainInventoryComponent.h"
#include "Components/SphereComponent.h"

// Engines
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"

// Miscellaneous
#include "Items/ItemBase.h"

// UserInterfaces
#include "UserInterfaces/MainHUD.h"
#include "UserInterfaces/Inventory/InventoryWidget.h"
#include "UserInterfaces/Gameplay/CombinationLockWidget.h"

/**
 * FUNCTIONS
 */

// Sets default values
AMainCharacter::AMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	/** Actor Components Setup */
	/* Component 1: First Person Camera Component */
	FPCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FPCamera"));
	FPCamera->SetupAttachment(GetRootComponent());
	FPCamera->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f)); // Position the camera
	FPCamera->SetRelativeRotation(FRotator(90.f, 0.f, -90.f));
	FPCamera->bUsePawnControlRotation = true;
	FPCamera->PostProcessSettings.AutoExposureMinBrightness = 1.f;
	FPCamera->PostProcessSettings.AutoExposureMaxBrightness = 1.f;
	
	WieldingItemComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMeshComponent"));
	WieldingItemComponent->SetupAttachment(FPCamera);
	WieldingItemComponent->SetRelativeLocation(FVector(34.f, 18.f, -12.f));
	WieldingItemComponent->SetRelativeRotation(FRotator(8.f, -84.f, -50.f));

	GetCharacterMovement()->MaxWalkSpeed = 170.f;
	
	/* Component 2: Inventory Component */
	MainInventoryComponent = CreateDefaultSubobject<UMainInventoryComponent>(TEXT("MainInventory"));
	MainInventoryComponent->SetMaxSlotAmount(8);

	/* Component 3: Sphere Collision Component */
	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	CollisionSphere->SetupAttachment(GetRootComponent());
	CollisionSphere->SetSphereRadius(50.f);
	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &AMainCharacter::OnOverlapBegin);
	CollisionSphere->OnComponentEndOverlap.AddDynamic(this, &AMainCharacter::OnOverlapEnd); 
	
	/** Variables and Flags Setup */
	/* Variables Group 1: Interaction Variables */
	InteractionCheckFrequency = 0.f; // The time period between each interaction check
	InteractionCheckDistance = 200.f; // The amount of space between the character and a trace-able item
	bIsInFocus = false; // Default not focusing on an item

	/* Variables Group 2: Puzzle Variables */
	CharacterPuzzleMode = ECharacterPuzzleMode::EGM_NoPuzzleGameMode;
}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Get the Main HUD for the Main Character
	MainHUD = Cast<AMainHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	MainHUD->GetCombinationLockWidget()->OnCombinationLockPuzzleCompleted.AddUniqueDynamic(this, &AMainCharacter::ExitPuzzle);
}

void AMainCharacter::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
}

void AMainCharacter::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	
}

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	/* Item Tracing */
	if (GetWorld()->TimeSince(InteractionData.LastInteractionCheckTime) > InteractionCheckFrequency) // Trace automatically after a short amount of time
	{
		PerformInteractionCheck();
	}
	
	/* Inventory Item Tracing */
	if (MainHUD)
	{
		if (MainInventoryComponent)
		{
			MainHUD->GetInventoryWidget()->ToggleSlotBorder(MainInventoryComponent->GetInventoryIndex());
		}
	}

	/* Item Wielding */
	if (WieldingItemComponent)
	{
		if (MainInventoryComponent)
		{
			if (MainInventoryComponent->GetInventory().Num() > 0)
			{
				if (MainInventoryComponent->GetInventoryIndex() >= MainInventoryComponent->GetInventory().Num())
				{
					MainInventoryComponent->SetInventoryIndex(MainInventoryComponent->GetInventoryIndex()-1);
				}
				
				WieldingItemComponent->SetStaticMesh(MainInventoryComponent->GetInventory()[MainInventoryComponent->GetInventoryIndex()]->AssetData.Mesh);
				if (MainInventoryComponent->GetInventory()[MainInventoryComponent->GetInventoryIndex()]->ItemType == EItemType::JigsawPuzzlePiece)
				{
					WieldingItemComponent->SetWorldScale3D(FVector(0.05f, 0.05f, 0.05f));
				}
				else
				{
					WieldingItemComponent->SetWorldScale3D(FVector(1.f, 1.f, 1.f));
				}
			}
		}
	}
}

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);

	/** Perspective Bindings */
	PlayerInputComponent->BindAxis("LookVertical", this, &AMainCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookHorizontal", this, &AMainCharacter::AddControllerYawInput);

	/** Locomotion Bindings */
	PlayerInputComponent->BindAxis("MoveVertical", this, &AMainCharacter::MoveVertical);
	PlayerInputComponent->BindAxis("MoveHorizontal", this, &AMainCharacter::MoveHorizontal);

	/** Interaction Bindings */
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AMainCharacter::BeginInteract);
	PlayerInputComponent->BindAction("Interact", IE_Released, this, &AMainCharacter::EndInteract);

	/** Inventory Bindings */
	PlayerInputComponent->BindAction("Drop", IE_Pressed, this, &AMainCharacter::Drop);
	PlayerInputComponent->BindAction("Inventory+", IE_Pressed, this, &AMainCharacter::InventoryPlus);
	PlayerInputComponent->BindAction("Inventory-", IE_Pressed, this, &AMainCharacter::InventoryMinus);

	/** Gameplay Bindings */
	PlayerInputComponent->BindAction("Exit", IE_Pressed, this, &AMainCharacter::ExitPuzzle);
	PlayerInputComponent->BindAction("ClockHand+", IE_Pressed, this, &AMainCharacter::RotateClockUp);
	PlayerInputComponent->BindAction("ClockHand-", IE_Pressed, this, &AMainCharacter::RotateClockDown);
	PlayerInputComponent->BindAction("Confirm", IE_Pressed, this, &AMainCharacter::ConfirmClockTime);
}

// Moves the character forward
void AMainCharacter::MoveVertical(float Value)
{
	if ((Controller!= nullptr) && (Value != 0.0f))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation = FRotator(0.f, Rotation.Yaw, 0.f); // Forward direction - Yaw

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X); // Get X of Local Yaw
		AddMovementInput(Direction, Value);
	}
}

// Moves the character sideways
void AMainCharacter::MoveHorizontal(float Value)
{
	if ((Controller!= nullptr) && (Value != 0.0f))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation = FRotator(0.f, Rotation.Yaw, 0.f); // Forward direction - Yaw

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y); // Get Y of Local Yaw
		AddMovementInput(Direction, Value);
	}
}

// Checks if the main character is currently focusing on an Interactable Object
void AMainCharacter::PerformInteractionCheck()
{
	// Records the current world seconds
	InteractionData.LastInteractionCheckTime = GetWorld()->GetTimeSeconds();

	const FVector TraceStart = FPCamera->GetComponentLocation();
	const FVector TraceEnd = TraceStart + FPCamera->GetForwardVector() * InteractionCheckDistance;

	// Adds Non-Interactable and Interactable Objects as Traced Objects
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypesArray;
	ObjectTypesArray.Add(UEngineTypes::ConvertToObjectType(ECC_NonInteractable)); // Convert the user-defined ECC_NonInteractable collision channel to EObjectTypeQuery
	ObjectTypesArray.Add(UEngineTypes::ConvertToObjectType(ECC_Interactable)); // Convert the user-defined ECC_Interactable collision channel to EObjectTypeQuery
	
	const TArray<AActor*, FDefaultAllocator> IgnoreActors;
	FHitResult TraceHit;

	// Starts line-tracing
	if (UKismetSystemLibrary::SphereTraceSingleForObjects(GetWorld(), TraceStart, TraceEnd, 0.f, ObjectTypesArray, false, IgnoreActors, EDrawDebugTrace::None, TraceHit, true))
	{
		if (TraceHit.GetActor()->GetClass()->ImplementsInterface(UInteractionInterface::StaticClass()))
		{
			if (TraceHit.GetActor() != InteractionData.CurrentInteractable)
			{
				FoundInteractable(TraceHit.GetActor());

				return;
			}
 
			if (TraceHit.GetActor() == InteractionData.CurrentInteractable)
			{
				return;
			}
		}
	}

	NoInteractableFound();
}

// If the main character is currently focusing on an Interactable Object, start line-tracing that object
void AMainCharacter::FoundInteractable(AActor* NewInteractable)
{
	if (IsInteracting())
	{
		EndInteract();
	}

	if (InteractionData.CurrentInteractable)
	{
		TargetInteractable = InteractionData.CurrentInteractable;

		if (bIsInFocus == true)
		{
			TargetInteractable->EndFocus();
			bIsInFocus = false;
		}
	}

	InteractionData.CurrentInteractable = NewInteractable;
	TargetInteractable = NewInteractable;

	TArray<UActorComponent*> FoundComponents = NewInteractable->GetComponentsByTag(UPrimitiveComponent::StaticClass(), TEXT("EligibleForOutlining")); // Search for all objects that are eligible for outlining in the map
	TArray<UActorComponent*> CheckComponents = NewInteractable->GetComponentsByTag(UPrimitiveComponent::StaticClass(), TEXT("EligibleForObtaining")); // Search for all objects that are eligible for obtaining in the map

	if (FoundComponents.Num() > 0 && FoundComponents[0] != nullptr)
	{
		if (CheckComponents.Num() > 0 && CheckComponents[0] != nullptr)
		{
			MainHUD->UpdateInteractionWidget(&TargetInteractable->InteractableData);
		}
		
		TargetInteractable->BeginFocus();
		bIsInFocus = true;
	}
}

void AMainCharacter::NoInteractableFound()
{
	if (IsInteracting())
	{
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle_Interaction);
	}

	if (InteractionData.CurrentInteractable)
	{
		if (IsValid(TargetInteractable.GetObject()))
		{
			if (bIsInFocus == true)
			{
				TargetInteractable->EndFocus();
				bIsInFocus = false;
			}
		}
	}

	MainHUD->HideInteractionWidget();

	InteractionData.CurrentInteractable = nullptr;
	TargetInteractable = nullptr;
}

void AMainCharacter::BeginInteract()
{
	if (CharacterPuzzleMode == ECharacterPuzzleMode::EGM_NoPuzzleGameMode)
	{
		// Verify nothing has changed with the interactable state since beginning interaction
		PerformInteractionCheck();
	
		if (InteractionData.CurrentInteractable)
		{
			if (IsValid(TargetInteractable.GetObject()) && bIsInFocus == true && !GetHUD()->bIsJigsawPuzzleVisible)
			{
				TargetInteractable->BeginInteract();

				if (FMath::IsNearlyZero(TargetInteractable->InteractableData.ItemInteractionDuration, 0.1f))
				{
					Interact();
				}
				else
				{
					GetWorldTimerManager().SetTimer(TimerHandle_Interaction, this, &AMainCharacter::Interact, TargetInteractable->InteractableData.ItemInteractionDuration, false);
				}
			}
		}
		else if (MainHUD->bIsDialogueVisible)
		{
			MainHUD->UpdateDialogueWidget(MainHUD->DialogueData->TextData.DialogueMessages);
		}
	}
	else if (CharacterPuzzleMode == ECharacterPuzzleMode::EGM_ClockGameMode)
	{
		OnSwitchToAnotherHand.Broadcast();
	}
}

void AMainCharacter::EndInteract()
{
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle_Interaction);

	if (IsValid(TargetInteractable.GetObject()))
	{
		TargetInteractable->EndInteract();
	}
}

void AMainCharacter::Interact()
{
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle_Interaction);

	if (IsValid(TargetInteractable.GetObject()))
	{
		TargetInteractable->Interact(this);
	}
}

void AMainCharacter::UpdateInteractionWidget() const
{
	if (IsValid(TargetInteractable.GetObject()))
	{
		MainHUD->UpdateInteractionWidget(&TargetInteractable->InteractableData);
	}
}

void AMainCharacter::UpdateDialogueWidget() const
{
	if (IsValid(TargetInteractable.GetObject()))
	{
		MainHUD->UpdateDialogueWidget(&TargetInteractable->InteractableData);
	}
}

void AMainCharacter::DropInventoryItem(UItemBase* ItemToDrop, const int32 Quantity)
{
	if (MainInventoryComponent->FindMatchingItem(ItemToDrop))
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.bNoFail = true;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		const FVector SpawnLocation = GetActorLocation() + (GetActorForwardVector() * 100.f);
		const FTransform SpawnTransform(GetActorRotation(), SpawnLocation);
		MainInventoryComponent->RemoveItem(ItemToDrop);

		AItemToObtain* DropItem = GetWorld()->SpawnActor<AItemToObtain>(AItemToObtain::StaticClass(), SpawnTransform, SpawnParams);

		DropItem->InitializeDrop(ItemToDrop, Quantity);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Item to drop was somehow null"));
	}
}

void AMainCharacter::Drop()
{	
	if (MainInventoryComponent->GetInventory().Num() > 0)
	{
		DropInventoryItem(MainInventoryComponent->GetInventory()[MainInventoryComponent->GetInventoryIndex()], 1);
		if (MainInventoryComponent->GetInventory().Num() > 0)
		{
			if (MainInventoryComponent->GetInventoryIndex() >= MainInventoryComponent->GetInventory().Num())
			{
				MainInventoryComponent->SetInventoryIndex(MainInventoryComponent->GetInventoryIndex() - 1);
			}
			
			WieldingItemComponent->SetStaticMesh(MainInventoryComponent->GetInventory()[MainInventoryComponent->GetInventoryIndex()]->AssetData.Mesh);
		}
		else
		{
			WieldingItemComponent->SetStaticMesh(nullptr);
		}
	}
}

void AMainCharacter::InventoryPlus()
{
	if (MainInventoryComponent->GetInventory().Num() > 1)
	{
		MainInventoryComponent->SetInventoryIndex(MainInventoryComponent->GetInventoryIndex() + 1);
	}
	
	if (MainInventoryComponent->GetInventoryIndex() >= 8 || MainInventoryComponent->GetInventoryIndex() > MainInventoryComponent->GetInventory().Num() - 1)
	{
		MainInventoryComponent->SetInventoryIndex(0);
	}

	if (MainInventoryComponent->GetInventoryIndex() < 0)
	{
		MainInventoryComponent->SetInventoryIndex(0);
	}
}

void AMainCharacter::InventoryMinus()
{
	if (MainInventoryComponent->GetInventoryIndex() != -1)
	{
		MainInventoryComponent->SetInventoryIndex(MainInventoryComponent->GetInventoryIndex() - 1);
	}
	
	if (MainInventoryComponent->GetInventoryIndex() < 0 && MainInventoryComponent->GetInventory().Num() > 0)
	{
		MainInventoryComponent->SetInventoryIndex(MainInventoryComponent->GetInventory().Num() - 1);
	}

	if (MainInventoryComponent->GetInventoryIndex() < 0)
	{
		MainInventoryComponent->SetInventoryIndex(0);
	}
}

void AMainCharacter::ExitPuzzle()
{
	if (GetHUD())
	{
		if (GetHUD()->bIsJigsawPuzzleVisible)
		{
			GetHUD()->HideJigsawPuzzle();
		}
	}

	if (CharacterPuzzleMode == ECharacterPuzzleMode::EGM_NoPuzzleGameMode)
	{
		
	}
	else if (CharacterPuzzleMode == ECharacterPuzzleMode::EGM_ClockGameMode)
	{
		OnPuzzleClosed.Broadcast();
		CharacterPuzzleMode = ECharacterPuzzleMode::EGM_NoPuzzleGameMode;
	}
	else if (CharacterPuzzleMode == ECharacterPuzzleMode::EGM_DoorGameMode)
	{
		GetHUD()->HideCombinationLock();
		CharacterPuzzleMode = ECharacterPuzzleMode::EGM_NoPuzzleGameMode;
	}
}

void AMainCharacter::RotateClockUp()
{
	OnRotateClockHandUp.Broadcast();
}

void AMainCharacter::RotateClockDown()
{
	OnRotateClockHandDown.Broadcast();
}

void AMainCharacter::ConfirmClockTime()
{
	if (CharacterPuzzleMode == ECharacterPuzzleMode::EGM_ClockGameMode)
	{
		OnCompleteClockPuzzle.Broadcast();
	}
}

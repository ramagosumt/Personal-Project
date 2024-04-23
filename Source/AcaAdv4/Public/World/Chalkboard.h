// This file creates a chalkboard that is an item to interact

#pragma once

#include "CoreMinimal.h"
#include "World/ItemToInteract.h"
#include "Chalkboard.generated.h"

class USphereComponent;
class UDecalComponent;

/**
 * 
 */
UCLASS()
class ACAADV4_API AChalkboard : public AItemToInteract
{
	GENERATED_BODY()

public:

	AChalkboard();

protected:

	/**
	 * PROPERTIES AND VARIABLES
	 **/

	UPROPERTY(VisibleAnywhere)
	AMainCharacter* InteractingCharacter;

	UPROPERTY(VisibleAnywhere)
	USphereComponent* ScanRadius;

	UPROPERTY(VisibleAnywhere)
	UDecalComponent* KeypadFirstNumber;

	UPROPERTY(VisibleAnywhere)
	UDecalComponent* KeypadSecondNumber;

	UPROPERTY(VisibleAnywhere)
	UDecalComponent* KeypadThirdNumber;

	UPROPERTY(VisibleAnywhere)
	UDecalComponent* KeypadFourthNumber;

	// The material used to create the first decal
	UPROPERTY(EditDefaultsOnly, Category= "Decal | MaterialInstance")
	UMaterialInstance* DesiredDecalFirstNumberMaterial;

	// The material used to create the second decal
	UPROPERTY(EditDefaultsOnly, Category= "Decal | MaterialInstance")
	UMaterialInstance* DesiredDecalSecondNumberMaterial;

	// The material used to create the third decal
	UPROPERTY(EditDefaultsOnly, Category= "Decal | MaterialInstance")
	UMaterialInstance* DesiredDecalThirdNumberMaterial;

	// The material used to create the fourth decal
	UPROPERTY(EditDefaultsOnly, Category= "Decal | MaterialInstance")
	UMaterialInstance* DesiredDecalFourthNumberMaterial;

	// The instance of the material used to create the first decal
	UPROPERTY(VisibleInstanceOnly, Category= "Decal | MaterialInstance")
	UMaterialInstanceDynamic* DecalFirstNumberMaterialInstance;

	// The instance of the material used to create the second decal
	UPROPERTY(VisibleInstanceOnly, Category= "Decal | MaterialInstance")
	UMaterialInstanceDynamic* DecalSecondNumberMaterialInstance;

	// The instance of the material used to create the third decal
	UPROPERTY(VisibleInstanceOnly, Category= "Decal | MaterialInstance")
	UMaterialInstanceDynamic* DecalThirdNumberMaterialInstance;

	// The instance of the material used to create the fourth decal
	UPROPERTY(VisibleInstanceOnly, Category= "Decal | MaterialInstance")
	UMaterialInstanceDynamic* DecalFourthNumberMaterialInstance;

	UPROPERTY(VisibleInstanceOnly)
	TArray<AActor*> OverlappingActors;

	UPROPERTY(VisibleAnywhere)
	bool IsDialogueEnd;

	/**
	 * FUNCTIONS
	 **/

	virtual void BeginPlay() override;
	
	virtual void Interact(AMainCharacter* MainCharacter) override;

	void UpdateDialogueState();
	void UpdateDialogueData();
	void UpdateBoard();

	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
	virtual void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
};

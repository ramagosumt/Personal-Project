/** Creates an user-defined data table for the inventory
 *	Uses enums for item classifications
 *	Uses structs for item variables
 *	Uses one last struct to group the enums and structs into one item
 */

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "InventoryDataStructs.generated.h"

/** Inventory Classifications */

// The tier of an item
// Used to classify items into rarity rating
// Similar to the "Common, Rare, Epic, Legendary" system
UENUM()
enum class EItemTier : uint8
{
	Tier_1 UMETA(DisplayName = "Tier 1"),
	Tier_2 UMETA(DisplayName = "Tier 2"),
	Tier_3 UMETA(DisplayName = "Tier 3"),
	Tier_4 UMETA(DisplayName = "Tier 4"),
	Tier_5 UMETA(DisplayName = "Tier 5")
};

// The type of an item
// Used to classify items into groups of items
UENUM()
enum class EItemType : uint8
{
	All UMETA(DisplayName = "All"),
	JigsawPuzzlePiece UMETA(DisplayName = "JigsawPuzzlePiece"),
	Quest UMETA(DisplayName = "Quest"),
	Armor UMETA(DisplayName = "Armor"),
	Weapon UMETA(DisplayName = "Weapon"),
	Shield UMETA(DisplayName = "Shield"),
	Spell UMETA(DisplayName = "Spell"),
	Consumable UMETA(DisplayName = "Consumable"),
	Mundane UMETA(DisplayName = "Mundane")
};

/** Inventory Variables */

// The statistical variables of an item
// Used to show on inventories
USTRUCT()
struct FItemStatistics
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	float ArmorRating;

	UPROPERTY(EditAnywhere)
	float DamageValue;

	UPROPERTY(EditAnywhere)
	float RestorationAmount;

	UPROPERTY(EditAnywhere)
	float SellValue;
};

// The text variables of an item
// Used to show on user-interfaces
USTRUCT()
struct FItemTextData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FText Name;
	
	UPROPERTY(EditAnywhere)
	FText Description;
	
	UPROPERTY(EditAnywhere)
	FText InteractionText;
	
	UPROPERTY(EditAnywhere)
	FText UsageText;

	UPROPERTY(EditAnywhere)
	TArray<FText> DialogueMessages;
};

// The numeric variables of an item
// Used to calculate the weight of items and inventories
USTRUCT()
struct FItemNumericData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	float Weight;

	UPROPERTY(EditAnywhere)
	int32 MaxStackSize;

	UPROPERTY(EditAnywhere)
	bool bIsStackable;
};

// The asset variables of an item
// Used to show on both inventories and user-interfaces
USTRUCT()
struct FItemAssetData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	UTexture2D* Icon;

	UPROPERTY(EditAnywhere)
	UStaticMesh* Mesh;
};

// The general structure of an item
// Used to manipulate an item
USTRUCT()
struct FInventoryData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category= "ItemData")
	FName ID;

	UPROPERTY(EditAnywhere, Category= "ItemData")
	EItemTier ItemTier;

	UPROPERTY(EditAnywhere, Category= "ItemData")
	EItemType ItemType;

	UPROPERTY(EditAnywhere, Category= "ItemData")
	FItemStatistics ItemStatistics;

	UPROPERTY(EditAnywhere, Category= "ItemData")
	FItemTextData TextData;

	UPROPERTY(EditAnywhere, Category= "ItemData")
	FItemNumericData NumericData;

	UPROPERTY(EditAnywhere, Category= "ItemData")
	FItemAssetData AssetData;
};

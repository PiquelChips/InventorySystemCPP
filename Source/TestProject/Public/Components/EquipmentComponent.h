// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryComponent.h"
#include "EquipmentComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TESTPROJECT_API UEquipmentComponent : public UInventoryComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEquipmentComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void InitInventory(int32 NumberSlots) override;

	virtual bool MoveInventoryItem(const uint8& FromInventorySlot, const uint8& ToInventorySlot) override;

	UFUNCTION()
	bool EquipItem(FSlotStructure& SlotStructure);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 NumberOfEquipmentSlots;
	
protected:
	
	
};
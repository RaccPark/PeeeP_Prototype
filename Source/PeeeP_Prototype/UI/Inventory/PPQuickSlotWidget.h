// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PPCustomWidget.h"
#include "PPSlot.h"
#include "../../Inventory/ESlotType.h"
#include "Components/TextBlock.h"
#include "PPQuickSlotWidget.generated.h"


UCLASS()
class PEEEP_PROTOTYPE_API UPPQuickSlotWidget : public UPPCustomWidget
{
	GENERATED_BODY()
	
	virtual void NativeConstruct	() override;

public:
	// ������ �ʱ�ȭ �Լ�
	void Init();

	// ������ ������Ʈ �Լ�
	void UpdateQuickSlot();

	UFUNCTION()
	void SetQuickSlotWidget	(UPPQuickSlotWidget* source);

	void SetEquipmentTextVisible(ESlateVisibility VisibleMode);

	TArray<TObjectPtr<class UPPSlot>> GetSlots();

private:
	void SetType(ESlotType Type);

	// ���Ե��� �����ϱ� ���� �迭
	UPROPERTY(VisibleAnywhere, Category = "Inventory")
	TArray<TObjectPtr<class UPPSlot>> Slots;

	TObjectPtr<UTextBlock> TXT_Equipment;

	// ���� �κ��丮�� Ÿ��(����)
	ESlotType InventorySlotType;

private:
};

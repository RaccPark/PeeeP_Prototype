// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Inventory/PPCustomWidget.h"
#include "../../Inventory/ESlotType.h"
#include "PPInventoryWidget.generated.h"

/**
 * 
 */
UCLASS()
class PEEEP_PROTOTYPE_API UPPInventoryWidget : public UPPCustomWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

public:
	// �κ��丮 �ʱ�ȭ �Լ�
	void Init();
	// �κ��丮 ������ ���� ������Ʈ �Լ�
	void UpdateInventorySlot();
	
private:
	UFUNCTION()
	void SetPartsType	();

// Main
public:
	UPROPERTY(meta = (BindWidget = "true"))
	TObjectPtr<class UButton> BTN_MainButton;

// Header
public:
	UPROPERTY(meta = (BindWidget = "true"))
	TObjectPtr<class UButton> BTN_Parts;

// Tail
public:
	
private:
	// ���� �κ��丮�� Ÿ���� �����ϱ� ���� �Լ�
	void SetType(ESlotType Type);

	// ���Ե��� �����ϱ� ���� �迭
	UPROPERTY(VisibleAnywhere, Category = "Inventory")
	TArray<TObjectPtr<class UPPSlot>> Slots;

	// ���� �κ��丮�� Ÿ��(����)
	ESlotType InventorySlotType;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PPInventoryPartsItem.h"
#include "Inventory/ESlotType.h"
#include "../UI/Inventory/PPSlot.h"
#include "../UI/Inventory/PPQuickSlotWidget.h"
#include "PPInventoryComponent.generated.h"

// �κ��丮 ���� ���� ��������Ʈ
DECLARE_MULTICAST_DELEGATE(FOnChangedInventoryDelegate);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PEEEP_PROTOTYPE_API UPPInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPPInventoryComponent();

	virtual void InitializeComponent() override;

public:
	FOnChangedInventoryDelegate OnChangeInven;

	void ClearUsingItem();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// ����
	UPROPERTY(VisibleAnywhere, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	TArray<TObjectPtr<class UPPInventoryPartsItem>> PartsItems;
	// �Һ�
	UPROPERTY(VisibleAnywhere, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	TArray<TObjectPtr<class UPPInventoryPartsItem>> ConsumableItems;
	// ��Ÿ
	UPROPERTY(VisibleAnywhere, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	TArray<TObjectPtr<class UPPInventoryPartsItem>> OtherItems;

	// �ִ� �κ��丮 ���� ��
	UPROPERTY(EditAnywhere, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	int32 MaxInventorySlotNum;

	// ���� �� ĭ�� ���� ������ �������� ��(������ 1 ����)
	UPROPERTY(VisibleAnywhere, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	int32 MaxItemNum;

public:
	// Getter
	FORCEINLINE TArray<TObjectPtr<class UPPInventoryPartsItem>> GetPartsItems() { return PartsItems; }
	FORCEINLINE TArray<TObjectPtr<class UPPInventoryPartsItem>> GetConsumableItems() { return ConsumableItems; }
	FORCEINLINE TArray<TObjectPtr<class UPPInventoryPartsItem>> GetOtherItems() { return OtherItems; }

	// ������ �߰�
	bool AddItem(FName InItemName, int32 InItemQuantity, int32& OutItemQuantity);
	// ������ ���
	void UseItem(int32 InSlotIndex, ESlotType InventoryType);
	// ���� �ε��� ��� ������ ���
	void UseItemCurrentIndex(ESlotType InventoryType);
	// ������ ��ü
	void SwapItem(int32 InprevIndex, int32 InCurrentIndex);


	// �κ��丮 ����
	void SortItem();

protected:
	// �κ��丮 �ʱ�ȭ
	void InitInventory();
	// ������ ����
	void RemoveItem(int32 InSlotIndex, ESlotType InventoryType);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// ���� ���õ� ���� �ε���
	int32 CurrentSlotIndex;
	// ���� ������ ���� ���� �ε���
	int32 UsingSlotIndex;

public:
	void ModifyCurrentSlotIndex(int32 Value);

private:
	// ������ ����
	UPROPERTY()
	TObjectPtr <class UPPQuickSlotWidget> QuickSlotWidget;

	// ���Ե��� �����ϱ� ���� �迭
	UPROPERTY(VisibleAnywhere, Category = "Inventory")
	TArray<TObjectPtr<class UPPSlot>> Slots;

public:
	// �κ��丮 ������Ʈ �� ������ ���� ������ ���� �Լ�
	UFUNCTION()
	void SetQuickSlotWidget(UPPQuickSlotWidget* widget);
};

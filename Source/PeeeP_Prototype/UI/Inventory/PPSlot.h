// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Inventory/PPCustomWidget.h"
#include "../../Inventory/ESlotType.h"
#include "PPSlot.generated.h"

// ������Ʈ ��������Ʈ ����
DECLARE_DELEGATE(FOnUpdateSlotDelegate);

// ���� ����ü�� ����
USTRUCT(BlueprintType)
struct FUpdateSlotDelegateWrapper
{
	GENERATED_BODY()
	
	FUpdateSlotDelegateWrapper() {}
	FUpdateSlotDelegateWrapper(const FOnUpdateSlotDelegate& InSlotDelegate) : SlotDelegate(InSlotDelegate) { }

	FOnUpdateSlotDelegate SlotDelegate;
};

UCLASS()
class PEEEP_PROTOTYPE_API UPPSlot : public UPPCustomWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;
	
public:
	// ���� �ʱ�ȭ
	void Init();
	// ���� Ÿ�� ����
	void SetType(ESlotType Type);
	// ���� ������Ʈ
	void UpdateSlot();

public:
	// ���� ������ Ÿ��
	UPROPERTY(EditAnywhere, Category = "Slot")
	ESlotType SlotType;

	// ���Կ� ������ �̹���
	UPROPERTY(VisibleAnywhere, Category = "Slot")
	TObjectPtr<class UImage> IMG_Item;

	// ���Կ� ������ �������� ����
	UPROPERTY(VisibleAnywhere, Category = "Slot")
	TObjectPtr<class UTextBlock> TXT_Quantity;

	// ���� ������ �ε���
	UPROPERTY(EditAnywhere, Category = "Slot")
	int32 SlotIndex;

protected:
	// ���� ���� ������Ʈ �Լ�
	// �� ������Ʈ������ �� ���� �׷��� ���� ���� �� ����.
	void UpdatePartsSlot();

	// �� ĭ�� �����ϱ� ���� ���� �ؽ���
	UPROPERTY(EditAnywhere, Category = "Slot")
	TObjectPtr<class UTexture2D> DefaultTexture;

protected:
	// <���� Ÿ��, ���� ����ü> ������ Map ����
	UPROPERTY()
	TMap<ESlotType, FUpdateSlotDelegateWrapper> SlotUpdateActions;
	// ���� https://velog.io/@apth1023/UE5-%EC%95%84%EC%9D%B4%ED%85%9C-%EC%9D%B8%EB%B2%A4%ED%86%A0%EB%A6%AC-%EC%8B%9C%EC%8A%A4%ED%85%9C-3 ��� �̾���
};

// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Inventory/PPSlot.h"
#include "Inventory/PPInventoryPartsItem.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Interface/UI/PPInventoryInterface.h"
#include "Inventory/PPInventoryComponent.h"

void UPPSlot::NativeConstruct()
{
	TXT_Quantity = Cast<UTextBlock>(GetWidgetFromName(TEXT("TEXT_Quantity")));
}

void UPPSlot::Init()
{
	// ���� �Լ��� �����Ͽ� �ʿ� ����(����� ���� ���Ը�)
	SlotUpdateActions.Add(ESlotType::ST_None, FUpdateSlotDelegateWrapper(FOnUpdateSlotDelegate::CreateUObject(this, &UPPSlot::UpdatePartsSlot)));
	SlotUpdateActions.Add(ESlotType::ST_InventoryParts, FUpdateSlotDelegateWrapper(FOnUpdateSlotDelegate::CreateUObject(this, &UPPSlot::UpdatePartsSlot)));

	for (auto& item : SlotUpdateActions)
	{
		item.Value.SlotDelegate.ExecuteIfBound();
	}
}

void UPPSlot::SetType(ESlotType Type)
{
}

void UPPSlot::UpdateSlot()
{
	// ���� Ÿ�Կ� ���� ����Ǵ� �Լ� ȣ��
	SlotUpdateActions[SlotType].SlotDelegate.ExecuteIfBound();
}

void UPPSlot::UpdatePartsSlot()
{
	IPPInventoryInterface* InvPlayer = Cast<IPPInventoryInterface>(OwningActor);

	if (InvPlayer)
	{
		// �κ��丮(Parts)�� �����´�.
		TArray<UPPInventoryPartsItem*> InventoryItems = InvPlayer->GetInventoryComponent()->GetPartsItems();	// ?

		// ���� Slot�� �ε����� ��ȿ���� üũ�Ѵ�.
		if (InventoryItems.IsValidIndex(SlotIndex))
		{
			// �ش� ���Կ� �������� �����ϴ��� Ȯ��
			if (IsValid(InventoryItems[SlotIndex]))
			{
				// �����ϴ� ��� �������� �ؽ��Ŀ� ������ �ݿ�(������ ���� ǥ�� ����)
				IMG_Item->SetBrushFromTexture(InventoryItems[SlotIndex]->PartsData->ItemTexture);
				TXT_Quantity->SetText(FText::FromString(TEXT("")));
			}
			else
			{
				// �������� �ʴ� ��� �� ĭ
				IMG_Item->SetBrushFromTexture(DefaultTexture);
				TXT_Quantity->SetText(FText::FromString(TEXT("")));
			}
		}
	}
} 

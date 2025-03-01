// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Inventory/PPInventoryWidget.h"
#include "Components/Button.h"
#include "Blueprint/WidgetTree.h"
#include "UI/Inventory/PPSlot.h"

void UPPInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UPPInventoryWidget::Init()
{
	// �⺻ Ÿ�� ����(����)
	SetType(ESlotType::ST_InventoryParts);

	// ��ư Ŭ�� �̺�Ʈ�� �Լ� ����
	if (BTN_Parts)
	{
		BTN_Parts->OnClicked.AddDynamic(this, &UPPInventoryWidget::SetPartsType);
	}

	// ������ �����ϱ� ���� �迭 �ʱ�ȭ(�ϴ� 5ĭ)
	Slots.Init(nullptr, 5);

	TArray<UWidget*> Widgets;
	// ��� �������� ������ Widgets �迭�� ����
	WidgetTree->GetAllWidgets(Widgets);

	// �迭�� ��ȸ�Ͽ� Ŀ���� Slot�� ã��
	for (UWidget* Widget : Widgets)
	{
		UPPSlot* InvSlot = Cast<UPPSlot>(Widget);
		if (InvSlot)
		{
			// ������ �����ָ� ���� �����ַ� ����
			InvSlot->SetOwningActor(OwningActor);
			// ������ Ÿ���� ���� �κ��丮�� Ÿ������ ����
			InvSlot->SetType(InventorySlotType);
			// ���� �ʱ�ȭ
			InvSlot->Init();
			// �ش� ������ �ε��� ��ġ�� ������ ����
			Slots[InvSlot->SlotIndex] = InvSlot;
		}
	}
}

void UPPInventoryWidget::UpdateInventorySlot()
{
	// ������ ���� �κ��丮 Ÿ������ ������Ʈ
	for (const auto& InvSlot : Slots)
	{
		InvSlot->SetType(InventorySlotType);
		InvSlot->UpdateSlot();
	}
}

void UPPInventoryWidget::SetPartsType()
{
	SetType(ESlotType::ST_InventoryParts);
}

void UPPInventoryWidget::SetType(ESlotType Type)
{
	// ���� �κ��丮 Ÿ�� ����
	InventorySlotType = Type;
	UpdateInventorySlot();
}

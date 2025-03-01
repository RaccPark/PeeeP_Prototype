// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Inventory/PPQuickSlotWidget.h"
#include "Inventory/PPInventoryComponent.h"
#include "Blueprint/WidgetTree.h"

void UPPQuickSlotWidget::NativeConstruct()
{
	Super::NativeConstruct();

	TXT_Equipment = Cast<UTextBlock>(GetWidgetFromName(TEXT("TXT_Equipment")));
	TXT_Equipment->SetVisibility(ESlateVisibility::Hidden);
}

void UPPQuickSlotWidget::Init()
{
	// �⺻ Ÿ�� ����(����)
	SetType(ESlotType::ST_InventoryParts);

	// ������ �����ϱ� ���� �迭 �ʱ�ȭ(�ϴ� 6ĭ)
	Slots.Init(nullptr, 6);

	TArray<UWidget*> Widgets;
	// ��� �������� ������ Widgets �迭�� ����
	WidgetTree->GetAllWidgets(Widgets);

	// �迭�� ��ȸ�Ͽ� Ŀ���� Slot�� ã��
	// �ñ����� ��: �̷��� ã�ƿ��� UMG���� ������ �����Ѵ�� ������ �� ������?
	// �ϴ��� ������� �����.
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
	UPPInventoryComponent* InventoryComponent = Cast<UPPInventoryComponent>(OwningActor->GetComponentByClass(UPPInventoryComponent::StaticClass()));
	if (InventoryComponent != nullptr)
	{
		InventoryComponent->SetQuickSlotWidget(this);
	}

	for (auto& InvSlot : Slots)
	{
		InvSlot->SetVisibility(ESlateVisibility::Hidden);
	}
	Slots[0]->SetVisibility(ESlateVisibility::Visible);
}

void UPPQuickSlotWidget::UpdateQuickSlot()
{
	// ������ ���� �κ��丮 Ÿ������ ������Ʈ
	for (const auto& InvSlot : Slots)
	{
		InvSlot->SetType(InventorySlotType);
		InvSlot->UpdateSlot();
	}
}

void UPPQuickSlotWidget::SetQuickSlotWidget(UPPQuickSlotWidget* source)
{
	source = this;
}

void UPPQuickSlotWidget::SetEquipmentTextVisible(ESlateVisibility VisibleMode)
{
	TXT_Equipment->SetVisibility(VisibleMode);
}

TArray<TObjectPtr<class UPPSlot>> UPPQuickSlotWidget::GetSlots()
{
	return Slots;
}

void UPPQuickSlotWidget::SetType(ESlotType Type)
{
	// ���� �κ��丮 Ÿ�� ����
	InventorySlotType = Type;
	UpdateQuickSlot();
}



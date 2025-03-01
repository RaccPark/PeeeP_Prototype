// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PPKeyManualUI.h"
#include "Components/Image.h"
#include "Interface/UI/PPElectricHUDInterface.h"

void UPPKeyManualUI::NativeConstruct()
{
	Super::NativeConstruct();

	KeyManualImage_WASD = Cast<UImage>(GetWidgetFromName(TEXT("KeyManualImage_WASD")));					// Ű ���̵� �̹��� - WASD
	KeyManualImage_Jump = Cast<UImage>(GetWidgetFromName(TEXT("KeyManualImage_Jump")));					// Ű ���̵� �̹��� - Jump
	KeyManualImage_Charge = Cast<UImage>(GetWidgetFromName(TEXT("KeyManualImage_Charge")));				// Ű ���̵� �̹��� - Charge
	KeyManualImage_Discharge = Cast<UImage>(GetWidgetFromName(TEXT("KeyManualImage_Discharge")));		// Ű ���̵� �̹��� - Discharge
	KeyManualImage_Equip = Cast<UImage>(GetWidgetFromName(TEXT("KeyManualImage_Equip")));				// Ű ���̵� �̹��� - Equip
	KeyManualImage_Unequip = Cast<UImage>(GetWidgetFromName(TEXT("KeyManualImage_Unequip")));			// Ű ���̵� �̹��� - Unequip
	KeyManualImage_Grab01 = Cast<UImage>(GetWidgetFromName(TEXT("KeyManualImage_Grab01")));				// Ű ���̵� �̹��� - Grab Parts(Grab)
	KeyManualImage_Grab02 = Cast<UImage>(GetWidgetFromName(TEXT("KeyManualImage_Grab02")));				// Ű ���̵� �̹��� - Grab Parts(Release)


	KeyManualImage_WASD->SetVisibility(ESlateVisibility::Hidden);
	KeyManualImage_Jump->SetVisibility(ESlateVisibility::Hidden);
	KeyManualImage_Charge->SetVisibility(ESlateVisibility::Hidden);
	KeyManualImage_Discharge->SetVisibility(ESlateVisibility::Hidden);
	KeyManualImage_Equip->SetVisibility(ESlateVisibility::Hidden);
	KeyManualImage_Unequip->SetVisibility(ESlateVisibility::Hidden);
	KeyManualImage_Grab01->SetVisibility(ESlateVisibility::Hidden);
	KeyManualImage_Grab02->SetVisibility(ESlateVisibility::Hidden);

	// ��������Ʈ�� ���� �������̽�(�÷��̾�� ��ӵ�)
	IPPElectricHUDInterface* ElectricHUDInterface = Cast<IPPElectricHUDInterface>(GetOwningPlayerPawn());
	if (ElectricHUDInterface)
	{
		ElectricHUDInterface->ShowKeyManualDelegate.AddUObject(this, &UPPKeyManualUI::SetKeyManualImageVisible);
	}

}

void UPPKeyManualUI::SetAllKeyManualImageHidden()
{
	KeyManualImage_WASD->SetVisibility(ESlateVisibility::Hidden);
	KeyManualImage_Jump->SetVisibility(ESlateVisibility::Hidden);
	KeyManualImage_Charge->SetVisibility(ESlateVisibility::Hidden);
	KeyManualImage_Discharge->SetVisibility(ESlateVisibility::Hidden);
	KeyManualImage_Equip->SetVisibility(ESlateVisibility::Hidden);
	KeyManualImage_Unequip->SetVisibility(ESlateVisibility::Hidden);
	KeyManualImage_Grab01->SetVisibility(ESlateVisibility::Hidden);
	KeyManualImage_Grab02->SetVisibility(ESlateVisibility::Hidden);
}

/// <summary>
/// Ű ���̵� UI ǥ��, �Է��� index�� �ش��ϴ� �ϳ��� UI�� ǥ��
/// ///
/// 0: ��� ��Ȱ��ȭ
/// 1: �⺻ ����, 2: ����, 3: ���� ����, 4: ���� ����
/// 5: ���� ����, 6: ���� ����, 7: �׷� ����(�׷�), 8: �׷� ����(����)
/// </summary>
/// <param name="index">ǥ���� UI</param>
void UPPKeyManualUI::SetKeyManualImageVisible(uint32 index)
{
	SetAllKeyManualImageHidden();
	switch (index)
	{
	case 0:
		
	break;
	case 1:
	{
		KeyManualImage_WASD->SetVisibility(ESlateVisibility::Visible);
	}
	break;
	case 2:
	{
		KeyManualImage_Jump->SetVisibility(ESlateVisibility::Visible);
	}
	break;
	case 3:
	{
		KeyManualImage_Charge->SetVisibility(ESlateVisibility::Visible);
	}
	break;
	case 4:
	{
		KeyManualImage_Discharge->SetVisibility(ESlateVisibility::Visible);
	}
	break;
	case 5:
	{
		KeyManualImage_Equip->SetVisibility(ESlateVisibility::Visible);
	}
	break;
	case 6:
	{
		KeyManualImage_Unequip->SetVisibility(ESlateVisibility::Visible);
	}
	break;
	case 7:
	{
		KeyManualImage_Grab01->SetVisibility(ESlateVisibility::Visible);
	}
	break;
	case 8:
	{
		KeyManualImage_Grab02->SetVisibility(ESlateVisibility::Visible);
	}
	break;
	default:
		break;
	}
}

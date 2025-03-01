// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PPInGameUIMain.h"
#include "Components/ProgressBar.h"
#include "Interface/UI/PPElectricHUDInterface.h"

/// <summary>
/// Main ĵ������ WBP_InGameUIMain�� ���� �ΰ����� ���� UserWidget�� �����ϴ� ������� ä��
/// �� ��ҿ� �����ϱ� ���ؼ��� �ش� ��Ҹ� �����ִ� UserWidget�� ������ ���� �����ϴ� ������� ����
/// </summary>

void UPPInGameUIMain::NativeConstruct()
{
	Super::NativeConstruct();

	// Cast ����
	PlayerStatusWidget = Cast<UUserWidget>(GetWidgetFromName(TEXT("WBP_PlayerStatusWidget")));		// ���۹� �̹��� ����
	KeyManualWidget = Cast<UUserWidget>(GetWidgetFromName(TEXT("WBP_KeyManualWidget")));			// �÷��̼� ���� ����
	QuickSlotWidget = Cast<UPPQuickSlotWidget>(GetWidgetFromName(TEXT("WBP_QuickSlot")));			// ������ ����(�׽�Ʈ)

	// �� ��� �ʱ�ȭ ����
	QuickSlotWidget->SetOwningActor(OwningActor);
	QuickSlotWidget->Init();

	// Bind ����
}
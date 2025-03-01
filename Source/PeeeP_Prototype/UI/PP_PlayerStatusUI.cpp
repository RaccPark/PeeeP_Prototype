// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PP_PlayerStatusUI.h"
#include "Interface/UI/PPElectricHUDInterface.h"
#include "Components/ProgressBar.h"

void UPP_PlayerStatusUI::NativeConstruct()
{
	Super::NativeConstruct();

	// Cast ����
	BatteryProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("BatteryProgressBar")));

	// �� ��� �ʱ�ȭ ����
	BatteryProgressBar->SetPercent(0.0f);

	// Bind ����
	IPPElectricHUDInterface* ElectricHUDInterface = Cast<IPPElectricHUDInterface>(GetOwningPlayerPawn());
	if (ElectricHUDInterface)
	{
		ElectricHUDInterface->ElectircCapacityDelegate.AddUObject(this, &UPP_PlayerStatusUI::SetBatteryProgressBarPercent);
	}
}

void UPP_PlayerStatusUI::SetBatteryProgressBarPercent(float rate)
{
	if (!BatteryProgressBar)
	{
		UE_LOG(LogTemp, Log, TEXT("Failed to load BatteryProgerssBar!"));
		return;
	}

	BatteryProgressBar->SetPercent(rate);
}

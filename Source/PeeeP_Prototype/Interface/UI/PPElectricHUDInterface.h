// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PPElectricHUDInterface.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FUsingElectricDelegate, float)
DECLARE_MULTICAST_DELEGATE_TwoParams(FChargingLevelDelegate, int, float)
DECLARE_MULTICAST_DELEGATE_OneParam(FShowKeyManualDelegate, uint32)

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPPElectricHUDInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PEEEP_PROTOTYPE_API IPPElectricHUDInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	// ���ⷮ�� ��ȭ�� �� ����ϴ� ��������Ʈ
	FUsingElectricDelegate ElectircCapacityDelegate;

	// ������ �翡 ���� �������� ó���� �� ����ϴ� ��������Ʈ
	FChargingLevelDelegate ChargingLevelDelegate;

	// UI �̹��� ����
	FShowKeyManualDelegate ShowKeyManualDelegate;
};
